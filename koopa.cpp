#include "koopa.h"
#include <QDebug>

Koopa::Koopa(Direction spawnDirection)
{
    // set textures
    texture_walk.append(QPixmap(loadTexture(":/resources/graphics/mobs/turtle/turtle-walk-0.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture_walk.append(QPixmap(loadTexture(":/resources/graphics/mobs/turtle/turtle-walk-1.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
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

void Koopa::setCurrentTexture(QPixmap texture){
    if(movingDirection == RIGHT){
        texture = texture.transformed(QTransform().scale(-1,1));
    }
    ObjectModel::setCurrentTexture(texture);
}


void Koopa::reactionNoMoreOnGround(){
    if(!shell){
        /* Stay on ground object*/
        if(movingDirection == LEFT){
            movingDirection = RIGHT;
        }
        else{
            movingDirection = LEFT;
        }
    }
}

void Koopa::collisionOnLeftHandler(ObjectModel *o){
    if(velocity.x() < 0){velocity.setX(0);}
    movingDirection = RIGHT;
    if(moving){
        Mario * mario = dynamic_cast<Mario*>(o);
        if(mario!=nullptr){
            mario->hurt();
        }

        Enemy * enemy = dynamic_cast<Enemy*>(o);
        if(enemy!=nullptr && shell){
            enemy->hurt();
        }
    }
}

void Koopa::collisionOnRightHandler(ObjectModel *o){
    if(velocity.x() > 0){velocity.setX(0);}
    movingDirection = LEFT;
    if(moving){
        Mario * mario = dynamic_cast<Mario*>(o);
        if(mario!=nullptr){
            mario->hurt();
        }

        Enemy * enemy = dynamic_cast<Enemy*>(o);
        if(enemy!=nullptr && shell){
            enemy->hurt();
        }
    }
}

void Koopa::collisionOnTopHandler(ObjectModel *o){
    if(dynamic_cast<Mario*>(o) && !shell){
        hurt();
    }
}

void Koopa::hitShellTop(ObjectModel *o){
    Mario *mario = dynamic_cast<Mario*>(o);
    if(!shell){
        if(mario){
            hurt();
        }
    }
    else if(moving == true){
        moving = false;
    }
    else{
        setDirection(mario->getDirection());
        moving = true;
    }
}

void Koopa::hitShellSide(ObjectModel *o){
    Mario *mario = dynamic_cast<Mario*>(o);
    if(!shell || moving){
        if(mario){
            hurt();
        }
    }
    else{
        setDirection(mario->getDirection());
        moving = true;
    }
}

void Koopa::hurt(){
    if(!shell){
        shell = true;
        moving=false;
        speed = 3;
    }
}
