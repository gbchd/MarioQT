#include "brickdebris.h"

BrickDebris::BrickDebris(Direction direction)
{
    currentTexture = loadTexture(":/resources/graphics/brick-debris.bmp").scaled(BLOCSIZE/2, BLOCSIZE/2);

    moving = true;
    running = false;
    collidable = false;
    deletable = false;
    lifeDuration = 500;

    speed = 2;
    gravity=0.3;

    switch(direction){
        case LEFT:{
            movingDirection = LEFT;
            velocity.setX(-1.5);
            velocity.setY(-4);
            break;}
        case UP:{
            movingDirection = LEFT;
            velocity.setX(-1.5);
            velocity.setY(-6);
            break;}
        case RIGHT:{
            movingDirection = RIGHT;
            velocity.setX(1.5);
            velocity.setY(-6);
            break;}
        case DOWN:{
            movingDirection = RIGHT;
            velocity.setX(1.5);
            velocity.setY(-4);
            break;}
        default:{
            velocity.setX(0);
            velocity.setY(0);
            break;}
    }

    timerToDeletion.start();
}

void BrickDebris::advance(){
    if(timerToDeletion.elapsed() > lifeDuration){
        deletable = true ;
    }

    velocity.setY(velocity.y() + gravity);

    moveTo(position+velocity);
}

void BrickDebris::animate()
{
// No animation for BrickDebris
}
