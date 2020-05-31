#include "enemy.h"
#include "koopa.h"

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

void Enemy::collisionByDefaultHandler(ObjectModel *o){
    Koopa * koopa = dynamic_cast<Koopa *>(o);
    if(koopa && koopa->isInShell() && koopa->isMoving()){
        die();
    }
}
