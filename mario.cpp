#include "mario.h"
#include <QDebug>
#include "enemy.h"
#include "koopa.h"
#include "brick.h"
#include "box.h"
#include "collectableitem.h"
#include "trampoline.h"
#include "fireball.h"
#include "flagpole.h"

Mario::Mario()
{
    //LoadTexture
    texture_walk[0].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-walk-0.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[0].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-walk-1.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[0].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-walk-2.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[1].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-big-walk-0.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[1].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-big-walk-1.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[1].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-big-walk-2.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[2].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/fiery-mario-walk-1.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[2].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/fiery-mario-walk-2.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk[2].append(QPixmap(loadTexture(":/resources/graphics/characters/mario/fiery-mario-walk-3.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio));

    texture_fire = QPixmap(loadTexture(":/resources/graphics/characters/mario/fiery-mario-fireball.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio);

    texture_stand[0] = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-stand.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_stand[1] = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-med-stand.bmp")).scaled(BLOCSIZE,1.5*BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_stand[2] = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-big-stand.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_stand[3] = QPixmap(loadTexture(":/resources/graphics/characters/mario/fiery-mario-stand.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio);

    texture_hang[0] = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-hang-1.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_hang[1] = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-big-hang-1.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_hang[2] = QPixmap(loadTexture(":/resources/graphics/characters/mario/fiery-mario-hang-1.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);

    texture_jump[0]    = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-jump.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_jump[1]    = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-big-jump.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_jump[2]    = QPixmap(loadTexture(":/resources/graphics/characters/mario/fiery-mario-jump.png")).scaled(BLOCSIZE,2*BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_dead	   = QPixmap(loadTexture(":/resources/graphics/characters/mario/mario-small-fall.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);

    texture_transitions_animations[0] = texture_stand[0];
    texture_transitions_animations[1] = texture_stand[1];
    texture_transitions_animations[2] = texture_stand[0];
    texture_transitions_animations[3] = texture_stand[1];
    texture_transitions_animations[4] = texture_stand[0];
    texture_transitions_animations[5] = texture_stand[1];
    texture_transitions_animations[6] = texture_stand[2];
    texture_transitions_animations[7] = texture_stand[0];
    texture_transitions_animations[8] = texture_stand[1];
    texture_transitions_animations[9] = texture_stand[2];
    texture_transitions_animations[10] = texture_stand[2];
    texture_transitions_animations[11] = texture_stand[3];
    texture_transitions_animations[12] = texture_stand[2];
    texture_transitions_animations[13] = texture_stand[3];
    texture_transitions_animations[14] = texture_stand[2];
    texture_transitions_animations[15] = texture_stand[3];
    texture_transitions_animations[16] = texture_stand[2];
    texture_transitions_animations[17] = texture_stand[3];
    texture_transitions_animations[18] = texture_stand[2];
    texture_transitions_animations[19] = texture_stand[3];

    transformingDown = false;
    currentTransformingTexture = 0;

    setCurrentTexture(texture_stand[0]);

    //States
    setSmall();
    running = false;
    sliding = false;
    transforming = false;
    big = false;
    onFire = false;
    isInACinematic = false;

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
            if(onFire){ doSimpleAnimation(texture_walk[2], timerWalk, durationRunningTexture, currentWalkTexture); }
            else if(big){ doSimpleAnimation(texture_walk[1], timerWalk, durationRunningTexture, currentWalkTexture); }
            else{ doSimpleAnimation(texture_walk[0], timerWalk, durationRunningTexture, currentWalkTexture); }
        }
        else{
            if(onFire){ doSimpleAnimation(texture_walk[2], timerWalk, durationWalkTexture, currentWalkTexture); }
            else if(big){ doSimpleAnimation(texture_walk[1], timerWalk, durationWalkTexture, currentWalkTexture); }
            else { doSimpleAnimation(texture_walk[0], timerWalk, durationWalkTexture, currentWalkTexture); }
        }
    }
    else if(!grounded){
        if(onFire){ setCurrentTexture(texture_jump[2]); }
        else if(big){ setCurrentTexture(texture_jump[1]); }
        else{ setCurrentTexture(texture_jump[0]); }
    }
    else{
        if(onFire){ setCurrentTexture(texture_stand[3]); }
        else if(big){ setCurrentTexture(texture_stand[2]); }
        else { setCurrentTexture(texture_stand[0]); }
    }

    if(fireballShootingTimer.isValid()){
        if(fireballShootingTimer.elapsed()<durationFireTimer){
            if(getDirection()==RIGHT){
                currentTexture = texture_fire;
            }
            else{
                currentTexture = texture_fire.transformed(QTransform().scale(-1,1));
            }
        }
        else{
            fireballShootingTimer.invalidate();
        }
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
    if(!phantom){
        if(onFire == true){
            transformingDown = true;
            transforming = true;
            currentTransformingTexture = 19;
            timerTransformation.start();
        }
        else if(big == true){
            transformingDown = true;
            transforming = true;
            currentTransformingTexture = 8;
            timerTransformation.start();
        }
        else{
           die();
        }
    }
}

void Mario::die(){
    collidable = false;
    dead = true;
    moving = false;
    gravity = deathJumpGravity;
    velocity.setY(deathJumpSpeed);
}

void Mario::startTransforming()
{
    if(!big){
        transformingDown = false;
        transforming = true;
        currentTransformingTexture = 0;
        timerTransformation.start();
    }
    else if(!onFire){
        transformingDown = false;
        transforming = true;
        currentTransformingTexture = 10;
        timerTransformation.start();
    }
    else{
        transformingDown = true;
        transforming = true;
        currentTransformingTexture = 19;
        timerTransformation.start();
    }
}

FireBall * Mario::shootFireBall()
{
    if(!fireballShootingTimer.isValid()){
        fireballShootingTimer.start();
        FireBall * newFireball = new FireBall(getDirection());
        if(getDirection()==RIGHT){
            newFireball->moveTo(position.x()+BLOCSIZE, position.y()+3*BLOCSIZE/4);
        }
        else{
            newFireball->moveTo(position.x()-newFireball->getHitboxEntity().width(), position.y()+3*BLOCSIZE/4);
        }
        return newFireball;
    }
    else{
        return nullptr;
    }
}

void Mario::doTransforming(){
    if(timerTransformation.elapsed() >= durationOfTransformation){

        timerTransformation.restart();

        if(transformingDown==false){
            if(!big && currentTransformingTexture==10){
                big = true;
                transforming = false;
                timerTransformation.invalidate();
                return;
            }
            else if(!onFire && currentTransformingTexture==20){
                onFire = true;
                transforming = false;
                timerTransformation.invalidate();
                return;
            }
        }
        else if(transformingDown==true){
            if(onFire && currentTransformingTexture==9){
                onFire = false;
                transforming = false;
                timerTransformation.invalidate();
                startPhantom();
                return;
            }
            else if(big && currentTransformingTexture==-1){
                big = false;
                transforming = false;
                timerTransformation.invalidate();
                startPhantom();
                return;
            }
        }

        setCurrentTexture(texture_transitions_animations[currentTransformingTexture]);

        if(transformingDown==false){
            if(currentTransformingTexture==1 || currentTransformingTexture==3 || currentTransformingTexture==5 || currentTransformingTexture==8){
                setSmallToMed();
            }
            if(currentTransformingTexture==2 || currentTransformingTexture==4){
                setMedToSmall();
            }
            if(currentTransformingTexture==6 || currentTransformingTexture==9){
                setMedToBig();
            }
            if(currentTransformingTexture==7){
                setBigToSmall();
            }
            if(currentTransformingTexture==11 || currentTransformingTexture==13 || currentTransformingTexture==15 || currentTransformingTexture==17 || currentTransformingTexture==19){
                setBigToFiery();
            }
        }

        if(transformingDown==true){
            if(currentTransformingTexture==18 || currentTransformingTexture==16 || currentTransformingTexture==14 || currentTransformingTexture==12 || currentTransformingTexture==10){
                setFieryToBig();
            }
            if(currentTransformingTexture==8 || currentTransformingTexture==5){
                setBigToMed();
            }
            if(currentTransformingTexture==7 || currentTransformingTexture==4 || currentTransformingTexture==2 || currentTransformingTexture==0){
                setMedToSmall();
            }
            if(currentTransformingTexture==6){
                setSmallToBig();
            }
            if(currentTransformingTexture==3 || currentTransformingTexture==1){
                setSmallToMed();
            }
        }

        if(transformingDown==false){
            currentTransformingTexture++;
        }
        if(transformingDown==true){
            currentTransformingTexture--;
        }
    }
}

void Mario::setSmallToMed(){
    moveTo(position.x(), position.y() - BLOCSIZE/2);
    setHitboxWidth(BLOCSIZE);
    setHitboxHeight((1.5)*BLOCSIZE);
    setHitboxEntityWidth(BLOCSIZE/2);
    setHitboxEntityHeight((1.5)*BLOCSIZE - BLOCSIZE/10);
}
void Mario::setSmallToBig(){
    moveTo(position.x(), position.y() - BLOCSIZE);
    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(2*BLOCSIZE);
    setHitboxEntityWidth(BLOCSIZE/2);
    setHitboxEntityHeight(2*BLOCSIZE - BLOCSIZE/10);
}
void Mario::setMedToSmall(){
    moveTo(position.x(), position.y() + BLOCSIZE/2);
    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(BLOCSIZE);
    setHitboxEntityWidth(BLOCSIZE/2);
    setHitboxEntityHeight(BLOCSIZE);
}
void Mario::setMedToBig(){
    moveTo(position.x(), position.y() - BLOCSIZE/2);
    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(2*BLOCSIZE);
    setHitboxEntityWidth(BLOCSIZE/2);
    setHitboxEntityHeight(2*BLOCSIZE - BLOCSIZE/10);
}
void Mario::setBigToSmall(){
    moveTo(position.x(), position.y() + BLOCSIZE);
    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(BLOCSIZE);
    setHitboxEntityWidth(BLOCSIZE/2);
    setHitboxEntityHeight(BLOCSIZE);
}
void Mario::setBigToMed(){
    moveTo(position.x(), position.y() + BLOCSIZE/2);
    setHitboxWidth(BLOCSIZE);
    setHitboxHeight((1.5)*BLOCSIZE);
    setHitboxEntityWidth(BLOCSIZE/2);
    setHitboxEntityHeight((1.5)*BLOCSIZE - BLOCSIZE/10);
}
void Mario::setBigToFiery(){
    // Same hitbox and position
}
void Mario::setFieryToBig(){
    // Same hitbox and position
}

void Mario::setSmall(){
    big = false;
    onFire = false;

    hitbox.moveTo(position);
    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(BLOCSIZE);

    hitboxEntity.moveTo(position.x() + BLOCSIZE/4, position.y());
    setHitboxEntityWidth(BLOCSIZE/2);
    setHitboxEntityHeight(BLOCSIZE);
}

void Mario::handleFlagpoleCollision(Flagpole * flagpole)
{
    isInACinematic = true;
}

void Mario::collisionByDefaultHandler(ObjectModel *o){
    CollectableItem * collectableItem = dynamic_cast<CollectableItem *>(o);
    if(collectableItem != nullptr){
        handleCollectableItemCollision(collectableItem);
    }
    else{
        Koopa * koopa = dynamic_cast<Koopa*>(o);
        if(koopa && koopa->isInShell() && koopa->isMoving()){
            hurt();
        }
        else{
            Flagpole * fp = dynamic_cast<Flagpole *>(o);
            if(fp){
                handleFlagpoleCollision(fp);
            }
        }
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
        else{
            Flagpole * fp = dynamic_cast<Flagpole *>(o);
            if(fp){
                handleFlagpoleCollision(fp);
            }
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
        else{
            Flagpole * fp = dynamic_cast<Flagpole *>(o);
            if(fp){
                handleFlagpoleCollision(fp);
            }
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
        else{
            Flagpole * fp = dynamic_cast<Flagpole *>(o);
            if(fp){
                handleFlagpoleCollision(fp);
            }
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
        else{
            Trampoline * trampoline = dynamic_cast<Trampoline*>(o);
            if(trampoline){
                if(trampoline->isTrampolineBig()){
                    bounceWithVariableVelocity(-22);
                }
                else{
                    bounceWithVariableVelocity(-18);
                }
            }
            else{
                Flagpole * fp = dynamic_cast<Flagpole *>(o);
                if(fp){
                    handleFlagpoleCollision(fp);
                }
            }
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
                transformingDown = false;
                transforming = true;
                currentTransformingTexture = 0;
                timerTransformation.start();
            }
            break;}
        case FLOWERCOLLECTABLE:{
            if(!big){
                transformingDown = false;
                transforming = true;
                currentTransformingTexture = 0;
                timerTransformation.start();
            }
            else if(!onFire){
                transformingDown = false;
                transforming = true;
                currentTransformingTexture = 10;
                timerTransformation.start();
            }
            break;}
        default:
            break;
    }
}
