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
