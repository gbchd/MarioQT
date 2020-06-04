#include "podoboo.h"

Podoboo::Podoboo()
{
    setCurrentTexture(loadTexture(":/resources/graphics/podoboo.png").scaled(0.875*BLOCSIZE,BLOCSIZE,Qt::KeepAspectRatio));
    setHitboxWidth(0.875*BLOCSIZE);
    setHitboxHeight(BLOCSIZE);
    setHitboxEntityWidth(0.875*BLOCSIZE);
    setHitboxEntityHeight(BLOCSIZE);

    amplitude = 10*BLOCSIZE;
    travelDuration = 2000;
    travelDistance = amplitude / travelDuration;
    goingDown = false;
}

Podoboo::Podoboo(QPointF initialPosition) : Podoboo()
{
    spawnPosition = initialPosition;
    moveTo(initialPosition);
}

void Podoboo::advance()
{
    if(!travelTimer.isValid()){
        travelTimer.start();
    }

    if(travelTimer.elapsed() > travelDuration){
        goingDown = !goingDown;
        travelTimer.restart();
        currentTexture = currentTexture.transformed(QTransform().scale(1,-1));
    }

    if(goingDown){
        moveTo(spawnPosition.x(), spawnPosition.y() + travelDistance * travelTimer.elapsed());
    }
    else{
        moveTo(spawnPosition.x(), spawnPosition.y() + amplitude - travelDistance * travelTimer.elapsed());
    }
}

void Podoboo::animate()
{

}
