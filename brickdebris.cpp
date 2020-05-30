#include "brickdebris.h"

BrickDebris::BrickDebris(Direction direction)
{
    currentTexture = loadTexture(":/resources/graphics/brick-debris.bmp").scaled(BLOCSIZE/2, BLOCSIZE/2);

    moving = true;
    speed = 2;
    speedLimit=4;
    switch(direction){
    case LEFT:{
        velocity.setX(1);
        velocity.setY(-1);
        break;}
    case UP:{
        velocity.setX(-1);
        velocity.setY(-1);
        break;}
    case RIGHT:{
        velocity.setX(-1);
        velocity.setY(1);
        break;}
    case DOWN:{
        velocity.setX(1);
        velocity.setY(1);
        break;}
    default:
        velocity.setX(0);
        velocity.setY(0);
        break;
    }

    timerToDeletion.start();
}

void BrickDebris::advance(){
    if(timerToDeletion.elapsed() > lifeDuration){
        deletable = true;

    }
    moveTo(position+velocity);
}

void BrickDebris::animate()
{
// No animation for BrickDebris
}
