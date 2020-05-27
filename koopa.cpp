#include "koopa.h"
#include <QDebug>

Koopa::Koopa(Direction spawnDirection)
{
    // set textures
    texture_walk[0] = QPixmap(loadTexture(":/resources/graphics/mobs/turtle/turtle-walk-0.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);
    texture_walk[1] = QPixmap(loadTexture(":/resources/graphics/mobs/turtle/turtle-walk-1.png")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio);
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

    setHitboxWidth(2*BLOCSIZE/3);
    setHitboxHeight(2*BLOCSIZE/3);

    hitbox.moveTo(position.x()+BLOCSIZE/2 - hitbox.width()/2 , position.y() + BLOCSIZE - hitbox.height());

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
        setCurrentTexture(texture_walk[(walkCounter++/walk_div)%2]);
    }

    if(movingDirection == RIGHT)
            setCurrentTexture(currentTexture.transformed(QTransform().scale(-1,1)));
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
    }
}

void Koopa::collisionOnTopHandler(ObjectModel *o){
    qDebug() << "test1";
    Mario *mario = dynamic_cast<Mario*>(o);
    if(!shell){
        if(mario){
            hurt();
        }
    }
    else if(moving == true){
        qDebug() << "test";
        moving = false;
    }
    else{
        setDirection(inverse(mario->getDirection()));
        moving = true;
        speed = 2;
    }
}

void Koopa::hurt(){
    if(!shell){
        shell = true;
        speed = 2;
    }
}
