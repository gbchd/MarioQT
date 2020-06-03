#include "koopa.h"
#include <QDebug>
#include "trampoline.h"

Koopa::Koopa(Direction spawnDirection)
{
    score = 100;

    // set textures
    texture_walk.append(QPixmap(loadTexture(":/resources/graphics/mobs/turtle/turtle-walk-0.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio).transformed(QTransform().scale(-1,1)));
    texture_walk.append(QPixmap(loadTexture(":/resources/graphics/mobs/turtle/turtle-walk-1.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio).transformed(QTransform().scale(-1,1)));
    texture_shell = QPixmap(loadTexture(":/resources/graphics/mobs/turtle/turtle-turtleback-0.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);

    movingDirection = spawnDirection;
    shell = false;

    // set texture and correct y-coordinate w.r.t. texture height
    setCurrentTexture(texture_walk[0]);

    moving = true;
    speed = 1;
    speedLimit = BLOCSIZE/2;
    velocity.setX(0);
    velocity.setY(0);

    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(BLOCSIZE);

    hitbox.moveTo(position.x(), position.y());

    setHitboxEntityWidth(2*BLOCSIZE/3);
    setHitboxEntityHeight(2*BLOCSIZE/3);

    hitboxEntity.moveTo(position.x()+BLOCSIZE/2 - hitboxEntity.width()/2 , position.y() + BLOCSIZE - hitboxEntity.height());

}

void Koopa::advance(){
    groundHandler();
    hurtfulFrameHandler();

    if(shell && moving){
        solid = false;
    }
    else{
        solid = true;
    }

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

void Koopa::animate()
{
    if(shell)
    {
        setCurrentTexture(texture_shell);

    }
    else if(dead)
    {
        setCurrentTexture(texture_dead);
    }
    else if(moving){
        doSimpleAnimation(texture_walk, timerWalk, durationWalkTexture, currentWalkTexture);
    }

}


void Koopa::hurtfulFrameHandler(){
    if(moving){
        if(counterNonHurtfulFrame < maxNonHurtfulFrame){
            counterNonHurtfulFrame++;
        }
        else{
            hurtful = true;
        }
    }
    else{
        counterNonHurtfulFrame = 0;
    }
}

void Koopa::collisionOnLeftHandler(ObjectModel *o){
    //Entity::collisionOnLeftHandler(o);
    movingDirection = RIGHT;
    if(shell){
        if(dynamic_cast<Mario*>(o) && !moving){
            moving = true;
        }
    }
}

void Koopa::collisionOnRightHandler(ObjectModel *o){
    //Entity::collisionOnRightHandler(o);
    movingDirection = LEFT;
    if(shell){
        if(dynamic_cast<Mario*>(o) && !moving){
            moving = true;
        }
    }
}

void Koopa::collisionOnTopHandler(ObjectModel *o){
    Entity::collisionOnTopHandler(o);
    if(dynamic_cast<Mario*>(o)){
        hurt();
    }
}

void Koopa::collisionOnBottomHandler(ObjectModel *o)
{
    Trampoline * trampoline = dynamic_cast<Trampoline*>(o);

    if(trampoline){
        if(trampoline->isTrampolineBig()){
            bounceWithVariableVelocity(-22);
        }
        else{
            bounceWithVariableVelocity(-18);
        }
    }
}


void Koopa::hurt(){
    if(!shell){
        Score::add(score);
        shell = true;
        moving=false;
        speed = 6;
    }
    else{
         moving = !moving;
    }
    hurtful = false;
}
