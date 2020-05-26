#include "goomba.h"
#include "QDebug"

Goomba::Goomba(Direction spawnDirection)
{
    // set textures
        texture_walk[0] = QPixmap(loadTexture(":/resources/graphics/mobs/goomba/goomba-0.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);
        texture_walk[1] = QPixmap(loadTexture(":/resources/graphics/mobs/goomba/goomba-1.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);
        texture_dead = QPixmap(loadTexture(":/resources/graphics/mobs/goomba/goomba-dead.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);

    movingDirection = spawnDirection;

    // set texture and correct y-coordinate w.r.t. texture height
    setCurrentTexture(texture_walk[0]);

    moving = true;
    speed = 1;
    speedLimit = BLOCSIZE/2;
    velocity.setX(0);
    velocity.setY(0);

    setHitboxWidth(2*BLOCSIZE/3);
    setHitboxHeight(2*BLOCSIZE/3);

    hitbox.moveTo(position.x()+BLOCSIZE/2 - hitbox.width()/2 , position.y() + BLOCSIZE - hitbox.height());
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
        setCurrentTexture(texture_walk[(walkCounter++/walk_div)%2]);
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

