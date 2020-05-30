#include "box.h"

Box::Box()
{
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-0.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-1.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-2.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-used.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));

    setCurrentTexture(texture[0]);

    boxContent = EMPTYBOX;
    used = false;
    needToSpawnItem = false;
}

void Box::handleCollisionFromMario()
{
    if(used == false){
        setCurrentTexture(texture[3]);
        needToSpawnItem = true;
        used = true;
        startBlockBounceAnimation();
    }
}

void Box::startBlockBounceAnimation()
{
    if(!timerBounceAnimation.isValid()){
        timerBounceAnimation.start();
    }
    else{
        timerBounceAnimation.restart();
    }
}

void Box::animate()
{
    if(timerBounceAnimation.isValid() && timerBounceAnimation.elapsed() < animationDuration){
        if(timerBounceAnimation.elapsed() < animationDuration/2){
            setPositionY(position.y()-1.5);
        }
        else{
            setPositionY(position.y()+1.5);
        }
    }
    else{
        setPositionY(getHitbox().y());
    }
}
