#include "goomba.h"
#include "QDebug"

Goomba::Goomba(Direction spawnDirection)
{
    // set textures
    texture_walk.append(QPixmap(loadTexture(":/resources/graphics/mobs/goomba/goomba-0.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk.append(QPixmap(loadTexture(":/resources/graphics/mobs/goomba/goomba-1.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_dead = QPixmap(loadTexture(":/resources/graphics/mobs/goomba/goomba-dead.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);

    movingDirection = spawnDirection;

    // set texture and correct y-coordinate w.r.t. texture height
    setCurrentTexture(texture_walk[0]);

    moving = true;
    speed = 1;
    speedLimit = BLOCSIZE/2;

    timerWalk.start();

    velocity.setX(0);
    velocity.setY(0);

    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(BLOCSIZE);

    hitbox.moveTo(position);

    setHitboxEntityWidth(2*BLOCSIZE/3);
    setHitboxEntityHeight(2*BLOCSIZE/3);

    hitboxEntity.moveTo(position.x()+BLOCSIZE/2 - hitboxEntity.width()/2 , position.y() + BLOCSIZE - hitboxEntity.height());
}

void Goomba::advance(){
    groundHandler();
    if(dead && timeOfDeath.elapsed() >= delayBeforeDeletable){
        deletable = true;
    }
    if(!grounded){
        velocity.setY(velocity.y() + gravity);
    }
    else{
        velocity.setY(0);
    }
    updateVelocity();
    applyVelocityLimit();

    moveTo(position+velocity);
}

void Goomba::animate()
{
    if(dead)
    {
        setCurrentTexture(texture_dead);
    }
    else if(moving){
        doSimpleAnimation(texture_walk, timerWalk, durationWalkTexture, currentWalkTexture);
    }
}

void Goomba::reactionNoMoreOnGround(){
    /* Stay on ground object*/
    if(movingDirection == LEFT){
        movingDirection = RIGHT;
    }
    else{
        movingDirection = LEFT;
    }
}

void Goomba::collisionOnLeftHandler(ObjectModel *o){
    if(velocity.x() < 0){velocity.setX(0);}
    movingDirection = RIGHT;
    Mario * mario = dynamic_cast<Mario*>(o);
    if(mario!=nullptr){
        mario->hurt();
    }
}

void Goomba::collisionOnRightHandler(ObjectModel *o){
    if(velocity.x() > 0){velocity.setX(0);}
    movingDirection = LEFT;
    Mario * mario = dynamic_cast<Mario*>(o);
    if(mario!=nullptr){
        mario->hurt();
    }
}

void Goomba::collisionOnTopHandler(ObjectModel *o){
    if(dynamic_cast<Mario*>(o)){
        hurt();
    }
}

void Goomba::hurt(){
    die();
}

