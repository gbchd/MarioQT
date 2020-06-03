#include "bulletbill.h"

#include "mario.h"

BulletBill::BulletBill()
{
    score = 200;

    currentTexture = loadTexture(":/resources/graphics/bullet-bill.png").scaled(BLOCSIZE, BLOCSIZE);

    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(BLOCSIZE);

    setHitboxEntityWidth(2*BLOCSIZE/3);
    setHitboxEntityHeight(2*BLOCSIZE/3);

    moving = true;

    speed = 2;
    speedLimit=4;
    velocity.setX(0);
    velocity.setY(0);
}

void BulletBill::advance(){
    if(dead && timeOfDeath.elapsed() >= delayBeforeDeletable){
        deletable = true;
    }
    else if(dead){
        velocity.setY(velocity.y()+gravity);
    }

    updateVelocity();
    applyVelocityLimit();
    moveTo(position+velocity);
}

void BulletBill::animate(){
    // No animation for bullet bill
}

void BulletBill::hurt(){
    die();
}

void BulletBill::die(){
    collidable = false;
    moving = false;
    dead = true;
    timeOfDeath.start();

    gravity=1;

    velocity.setX(0);
    velocity.setY(-5);
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
    hurt();
}

void BulletBill::collisionOnRightHandler(ObjectModel *o){
    hurt();
}

void BulletBill::collisionOnTopHandler(ObjectModel *o){
    if(dynamic_cast<Mario*>(o)){
        Score::add(score);
    }
    hurt();
}

void BulletBill::collisionOnBottomHandler(ObjectModel *o){
    hurt();
}
