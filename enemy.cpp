#include "enemy.h"
#include "koopa.h"
#include "fireball.h"
#include "trampoline.h"

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
    Score::add(score);

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

    FireBall * fb = dynamic_cast<FireBall*>(o);
    if(fb){
        die();
    }

    Trampoline * trampoline = dynamic_cast<Trampoline*>(o);
    if(trampoline){
        if(trampoline->isTrampolineBig()){
            bounceWithVariableVelocity(-22);
        }
        else{
            bounceWithVariableVelocity(-18);
        }
    }
}
