#include "podoboo.h"

#include <QDebug>

Podoboo::Podoboo()
{
    orignalTexture = loadTexture(":/resources/graphics/podoboo.png").scaled(0.875*BLOCSIZE,BLOCSIZE,Qt::KeepAspectRatio);
    setCurrentTexture(orignalTexture.transformed(QTransform().scale(1,-1)));

    setHitboxWidth(0.875*BLOCSIZE);
    setHitboxHeight(BLOCSIZE);
    setHitboxEntityWidth(0.875*BLOCSIZE);
    setHitboxEntityHeight(BLOCSIZE);

    zValue = 2;

    collidable = false;
}

Podoboo::Podoboo(QPointF initialPosition) : Podoboo()
{
    spawnPosition = initialPosition + QPointF(0,bounceHeight);
    moveTo(initialPosition + QPointF(0,bounceHeight));
    bounceFrameCounter = 0;
    velocity.setY(bounceSpeed);
}

void Podoboo::advance()
{
    if(bounceFrameCounter > 2*bounceDuration){
        bounceFrameCounter = 0;
        velocity.setY(bounceSpeed);
        moveTo(spawnPosition);
        currentTexture = currentTexture.transformed(QTransform().scale(1,-1));
    }

    velocity.setY(velocity.y() + bounceGravity);

    moveTo(position+velocity);

    bounceFrameCounter++;
}

void Podoboo::animate()
{
    if(velocity.y() > 0){
        setCurrentTexture(orignalTexture.transformed(QTransform().scale(1,-1)));
    }
    else{
        setCurrentTexture(orignalTexture);
    }
}
