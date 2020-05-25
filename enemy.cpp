#include "enemy.h"

Enemy::Enemy()
{
    walkable = false;
    collidable = true;
    phantom = false;
}

void Enemy::hurt(){
    //ouch
}

void Enemy::die(){
    collidable = false;
    dead = true;
    moving = false;
    moveTo(position.x(), position.y() + (BLOCSIZE-texture_dead.size().height()));
    timeOfDeath.start();
}
