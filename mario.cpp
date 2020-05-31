#include "mario.h"
#include <QDebug>
#include "enemy.h"
#include "koopa.h"
#include "brick.h"
#include "box.h"
#include "collectableitem.h"

Mario::Mario()
{
    //LoadTexture
    texture_walk[0].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-walk-0.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[0].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-walk-1.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[0].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-walk-2.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[1].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-big-walk-0.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[1].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-big-walk-1.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[1].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-big-walk-2.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio));

    texture_stand[0]   = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-stand.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_stand[1]   = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-big-stand.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_stand[2] = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-med-stand.bmp")).scaled(BLOCSIZE,1.5*BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_jump[0]    = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-jump.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_jump[1]    = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-big-jump.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_dead	   = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-fall.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);

    texture_small_to_big[0] = texture_stand[0];
    texture_small_to_big[1] = texture_stand[2];
    texture_small_to_big[2] = texture_stand[0];
    texture_small_to_big[3] = texture_stand[2];
    texture_small_to_big[4] = texture_stand[1];
    texture_small_to_big[5] = texture_stand[0];
    texture_small_to_big[6] = texture_stand[2];
    texture_small_to_big[7] = texture_stand[1];

    currentTexture = texture_stand[1];

    currentTransformingTexture = 0;

    //States
    setSmall();
    transformationType = 0;
    running = false;
    sliding = false;
    transforming = false;
    big = false;
    onFire = false;

    //Engine Value
    speed = 4;
    speedLimit = BLOCSIZE/2;
    gravity = defaultGravity;

    //Graphical value
    zValue = 5;
    timerWalk.start();
}

Mario::~Mario(){
    // delete les attributs alloués dynamiquement
}



void Mario::advance(){
    //Check if we are still touching the ground object
    groundHandler();

    if(phantom && timerPhantom.elapsed() >= durationOfPhantom){
        stopPhantom();
    }

    // Mettre en place la taille du niveau
    if(dead && position.y() > 25 * BLOCSIZE){
        deletable = true;
    }

    if(jumping && velocity.y() > 0){
        jumping = false;
    }
    if(!jumping){
        gravity = defaultGravity;
    }
    // ON MET A JOUR LES VECTEURS DE DEPLACEMENT
    if(!grounded){
        velocity.setY(velocity.y() + gravity);
    }
    else{
        velocity.setX(0);
    }

    updateVelocity();
    applyVelocityLimit();

    updatePosition();
}

void Mario::animate(){

    if(transforming){
        doTransforming();
    }
    else if(dead){
        setCurrentTexture(texture_dead);
    }
    else if(moving && grounded){
        if(running){
            doSimpleAnimation(texture_walk[big], timerWalk, durationRunningTexture, currentWalkTexture);
        }
        else{
            doSimpleAnimation(texture_walk[big], timerWalk, durationWalkTexture, currentWalkTexture);
        }
    }
    else if(!grounded){
        setCurrentTexture(texture_jump[big]);
    }
    else{
        setCurrentTexture(texture_stand[big]);
    }

}



void Mario::jump(){
    if(grounded){
        jumping = true;
        gravity = jumpGravity;
        velocity.setY(jumpInitialSpeed);
    }

}
void Mario::releaseJump(){
    if(jumping && velocity.y() < 0){
        jumping = false;
        gravity = jumpReleaseGravity;
    }
}

void Mario::hurt(){
    if(big){
        startPhantom();
        startTransforming();
    }
    else{
        die();
    }
}

void Mario::die(){
    collidable = false;
    dead = true;
    moving = false;
    gravity = deathJumpGravity;
    velocity.setY(deathJumpSpeed);
}

void Mario::setBig(){
    big = true;
    moveTo(position.x(), position.y() - BLOCSIZE);

    hitbox.moveTo(position);
    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(2*BLOCSIZE);

    hitboxEntity.moveTo(position.x() + BLOCSIZE/4, position.y() + BLOCSIZE/10);
    setHitboxEntityWidth(BLOCSIZE/2);
    setHitboxEntityHeight(2*BLOCSIZE - BLOCSIZE/10);
}

void Mario::setSmall(){
    big = false;
    moveTo(position.x(), position.y() + BLOCSIZE);

    hitbox.moveTo(position);
    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(BLOCSIZE);

    hitboxEntity.moveTo(position.x() + BLOCSIZE/4, position.y());
    setHitboxEntityWidth(BLOCSIZE/2);
    setHitboxEntityHeight(BLOCSIZE);
}

void Mario::doTransforming(){
    if(timerTransformation.elapsed() >= durationOfTransformation){
        if(!transformationType){
            currentTransformingTexture++;
        }
        else{
            currentTransformingTexture--;
        }

        timerTransformation.restart();
        if(currentTransformingTexture == 8 || currentTransformingTexture == -1) {
            stopTransforming();
        }
        else{
            setCurrentTexture(texture_small_to_big[currentTransformingTexture]);

            if(currentTransformingTexture == 0 || currentTransformingTexture == 2 || currentTransformingTexture == 5){
                setHitboxWidth(BLOCSIZE);
                setHitboxHeight(BLOCSIZE);
                setHitboxEntityWidth(BLOCSIZE/2);
                setHitboxEntityHeight(BLOCSIZE);

                if(currentTransformingTexture == 5 && !transformationType){
                    moveTo(position.x(), position.y() + BLOCSIZE);
                }
                else{
                    moveTo(position.x(), position.y() + BLOCSIZE/2);
                }
                big=false;
            }
            else if(currentTransformingTexture == 1 || currentTransformingTexture == 3 || currentTransformingTexture == 6){
                if(!transformationType){
                    moveTo(position.x(), position.y() - BLOCSIZE/2);
                }
                else{
                    moveTo(position.x(), position.y() + BLOCSIZE/2);
                }

                setHitboxWidth(BLOCSIZE);
                setHitboxHeight((1.5)*BLOCSIZE);
                setHitboxEntityWidth(BLOCSIZE/2);
                setHitboxEntityHeight((1.5)*BLOCSIZE - BLOCSIZE/10);
            }
            else if(currentTransformingTexture == 4 || currentTransformingTexture == 7){
                setHitboxWidth(BLOCSIZE);
                setHitboxHeight(2*BLOCSIZE);
                setHitboxEntityWidth(BLOCSIZE/2);
                setHitboxEntityHeight(2*BLOCSIZE - BLOCSIZE/10);

                if(currentTransformingTexture == 4 && transformationType){
                    moveTo(position.x(), position.y() - BLOCSIZE);
                }
                else{
                    moveTo(position.x(), position.y() - BLOCSIZE/2);
                }
                big=true;
            }
        }

    }
}

void Mario::startTransforming(){
    transforming=true;
    if(big == true){
        transformationType = 1;
        currentTransformingTexture = 7;
    }
    else{
        transformationType = 0;
        currentTransformingTexture = 0;
    }

    timerTransformation.start();
}

void Mario::stopTransforming(){
    transforming = false;
    timerTransformation.invalidate();
}

void Mario::collisionByDefaultHandler(ObjectModel *o){
    CollectableItem * collectableItem = dynamic_cast<CollectableItem *>(o);
    if(collectableItem != nullptr){
        handleCollectableItemCollision(collectableItem);
    }

    Koopa * koopa = dynamic_cast<Koopa*>(o);
    if(koopa && koopa->isInShell() && koopa->isMoving()){
        hurt();
    }
}

void Mario::collisionOnLeftHandler(ObjectModel *o){
    Entity::collisionOnLeftHandler(o);
    Enemy * enemy = dynamic_cast<Enemy *>(o);
    if(enemy != nullptr){
        if(enemy->isHurtful()){
            hurt();
        }
    }
    else{
        CollectableItem * collectableItem = dynamic_cast<CollectableItem *>(o);
        if(collectableItem != nullptr){
            handleCollectableItemCollision(collectableItem);
        }
    }
}

void Mario::collisionOnRightHandler(ObjectModel *o){
    Entity::collisionOnRightHandler(o);
    Enemy * enemy = dynamic_cast<Enemy *>(o);
    if(enemy != nullptr){
        if(enemy->isHurtful()){
            hurt();
        }
    }
    else{
        CollectableItem * collectableItem = dynamic_cast<CollectableItem *>(o);
        if(collectableItem != nullptr){
            handleCollectableItemCollision(collectableItem);
        }
    }
}

void Mario::collisionOnTopHandler(ObjectModel *o){
    Entity::collisionOnTopHandler(o);
    Enemy * enemy = dynamic_cast<Enemy *>(o);
    if(enemy != nullptr){
        if(enemy->isHurtful()){
            hurt();
        }
    }
    else{
        CollectableItem * collectableItem = dynamic_cast<CollectableItem *>(o);
        if(collectableItem != nullptr){
            handleCollectableItemCollision(collectableItem);
        }
    }
}

void Mario::collisionOnBottomHandler(ObjectModel *o){
    Entity::collisionOnBottomHandler(o);
    Enemy * enemy = dynamic_cast<Enemy *>(o);
    if(enemy != nullptr){
        bounce();
    }
    else{
        CollectableItem * collectableItem = dynamic_cast<CollectableItem *>(o);
        if(collectableItem != nullptr){
            handleCollectableItemCollision(collectableItem);
        }
    }
}

void Mario::handleCollectableItemCollision(CollectableItem * collectableItem)
{
    switch(collectableItem->getItemType()){
        case COINCOLLECTABLE:{
            // TODO COLLECT COIN
            break;}
        case STARCOLLECTABLE:{
            // TODO GO IN INVINCIBLE MODE
            break;}
        case MUSHROOMCOLLECTABLE:{
            if(!big && !onFire){
                startTransforming();
            }
            break;}
        case FLOWERCOLLECTABLE:{
            if(!onFire){
                // TODO TRANSFORM IN FIRE MODE
            }
            break;}
        default:
            break;
    }
}
