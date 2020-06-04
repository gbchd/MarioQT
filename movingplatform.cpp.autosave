#include "movingplatform.h"

MovingPlatform::MovingPlatform(bool b)
{
    bigMovingPlatform = b;
    amplitude = 10*BLOCSIZE;
    travelDuration = 3000;
    travelDistance = amplitude / travelDuration;
    goingDown = true;

    if(bigMovingPlatform){
        setCurrentTexture(loadTexture(":/resources/graphics/moving-platform-3.png").scaled(4*BLOCSIZE, 1*BLOCSIZE, Qt::KeepAspectRatio));
        setHitboxWidth(4*BLOCSIZE);
    }
    else{
        setCurrentTexture(loadTexture(":/resources/graphics/moving-platform-1.png").scaled(2*BLOCSIZE, 1*BLOCSIZE, Qt::KeepAspectRatio));
        setHitboxWidth(2*BLOCSIZE);
    }
    setHitboxHeight(2*BLOCSIZE/3);
}

void MovingPlatform::animate()
{
    if(!travelTimer.isValid()){
        travelTimer.start();
    }

    if(travelTimer.elapsed() > travelDuration){
        goingDown = !goingDown;
        travelTimer.restart();
    }

    if(goingDown){
        moveTo(spawnPosition.x(), spawnPosition.y() + travelDistance * travelTimer.elapsed());
    }
    else{
        moveTo(spawnPosition.x(), spawnPosition.y() + amplitude - travelDistance * travelTimer.elapsed());
    }
}
