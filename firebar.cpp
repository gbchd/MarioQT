#include "firebar.h"

#include "fireball.h"

#include <QDebug>

Firebar::Firebar()
{
    setCurrentTexture(loadTexture(":/resources/graphics/blocs/box-used.bmp").scaled(BLOCSIZE,BLOCSIZE));
    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(BLOCSIZE);

    rotationTimer.start();
}

void Firebar::setFireball(int indice, FireBall * fireball)
{
    fireballs[indice] = fireball;

    fireball->moveTo(position.x() + indice*fireball->getHitbox().width(), position.y() + (BLOCSIZE-fireball->getHitbox().height())/2);
}

void Firebar::animate()
{
    if(rotationTimer.elapsed() > rotationDuration){
        rotationTimer.restart();
    }
    currentAngle = 360 * rotationTimer.elapsed() / rotationDuration;

    for(int indice=0; indice<6; indice++){
        if(fireballs[indice]){
            fireballs[indice]->moveTo(position.x() + (BLOCSIZE-fireballs[indice]->getHitbox().width())/2 + indice*fireballs[indice]->getHitbox().width() * qCos(qDegreesToRadians(currentAngle)), position.y() + (BLOCSIZE-fireballs[indice]->getHitbox().height())/2 + indice*fireballs[indice]->getHitbox().width() * qSin(qDegreesToRadians(currentAngle)));
        }
    }
}
