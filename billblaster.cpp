#include "billblaster.h"

BillBlaster::BillBlaster()
{
    currentTexture = loadTexture(":/resources/graphics/bill-blaster.png").scaled(BLOCSIZE,BLOCSIZE*2,Qt::IgnoreAspectRatio);
    shooting = false;
    shootTimer.start();
}

void BillBlaster::animate()
{
    if(shootTimer.elapsed() > shootDelay){
        shooting = true;
        shootTimer.restart();
    }
}

BulletBill* BillBlaster::shoot(QPointF marioPosition){
    if(shootTimer.elapsed() > shootDelay && shooting){
        BulletBill * bullet = new BulletBill();
        if(marioPosition.x() > position.x()){
            bullet->setUpRightMovingBulletBill(position);
        }
        else{
            bullet->setUpLeftMovingBulletBill(position);
        }
        shootTimer.restart();
        return bullet;
    }
    return nullptr;
}
