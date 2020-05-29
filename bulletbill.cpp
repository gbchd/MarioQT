#include "bulletbill.h"

#include "mario.h"

BulletBill::BulletBill()
{
    currentTexture = loadTexture(":/resources/graphics/bullet-bill.png").scaled(BLOCSIZE, BLOCSIZE);

    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(BLOCSIZE);

    setHitboxEntityWidth(2*BLOCSIZE/3);
    setHitboxEntityHeight(2*BLOCSIZE/3);

    moving = true;

    speed = 2;
    velocity.setX(0);
    velocity.setY(0);
}

void BulletBill::advance(){
    if(dead && timeOfDeath.elapsed() >= delayBeforeDeletable){
        deletable = true;
    }
    moveTo(position+velocity);
}

void BulletBill::animate(){
    // No animation for bullet bill
}

void BulletBill::hurt(){
    die();
}

void BulletBill::setUpLeftMovingBulletBill(QPointF billBlasterPos)
{
    currentTexture = currentTexture.transformed(QTransform().scale(-1, 1));
    setDirection(LEFT);
    velocity.setX(-speed);
    setPositionY(billBlasterPos.y());
    setPositionX(billBlasterPos.x()-BLOCSIZE);
    hitboxEntity.moveTo(position.x()+BLOCSIZE/2 - hitboxEntity.width()/2 , position.y() + BLOCSIZE - hitboxEntity.height());
    hitbox.moveTo(position);
}

void BulletBill::setUpRightMovingBulletBill(QPointF billBlasterPos)
{
    setDirection(RIGHT);
    velocity.setX(+speed);
    setPositionY(billBlasterPos.y());
    setPositionX(billBlasterPos.x()+BLOCSIZE);
    hitboxEntity.moveTo(position.x()+BLOCSIZE/2 - hitboxEntity.width()/2 , position.y() + BLOCSIZE - hitboxEntity.height());
    hitbox.moveTo(position);
}

void BulletBill::collisionOnLeftHandler(ObjectModel *o){
    Mario * mario = dynamic_cast<Mario*>(o);
    if(mario!=nullptr){
        mario->hurt();
    }
}

void BulletBill::collisionOnRightHandler(ObjectModel *o){
    Mario * mario = dynamic_cast<Mario*>(o);
    if(mario!=nullptr){
        mario->hurt();
    }
}

void BulletBill::collisionOnTopHandler(ObjectModel *o){
    if(dynamic_cast<Mario*>(o)){
        hurt();
    }
}

void BulletBill::collisionOnBottomHandler(ObjectModel *o){
    Mario * mario = dynamic_cast<Mario*>(o);
    if(mario!=nullptr){
        mario->hurt();
    }
}
