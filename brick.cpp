#include "brick.h"

Brick::Brick()
{
    currentTexture = QPixmap(loadTexture(":/resources/graphics/blocs/brick.bmp").scaled(BLOCSIZE, BLOCSIZE));
    brickState = NOBRICKSTATE;
    usedBrickTexture = QPixmap(loadTexture(":/resources/graphics/blocs/box-used.bmp").scaled(BLOCSIZE, BLOCSIZE));
}

void Brick::startBlockBounceAnimation()
{
    setPositionY(getHitbox().y());
    if(!timerBounceAnimation.isValid()){
        timerBounceAnimation.start();
    }
    else{
        timerBounceAnimation.restart();
    }
}

void Brick::handleCollisionFromMario(bool isMarioBig)
{
    if(isMarioBig && brickState==NOBRICKSTATE){
        brickState = BREAKBRICK; // Will be handled in the gamecontroller later
    }
    else if(brickState==BRICKWILLGIVECOINONNEXTHIT){
        brickState = GIVECOIN; // Will be handled in the gamecontroller later
        if(!timerSinceCoinBlockHit.isValid()){ timerSinceCoinBlockHit.start(); }
        startBlockBounceAnimation();
    }
    else if(!isMarioBig){
        startBlockBounceAnimation();
    }
}

void Brick::animate()
{
    if(timerSinceCoinBlockHit.isValid() && timerSinceCoinBlockHit.elapsed() > timeToGetCoins){
        brickState = USEDCOINBRICK;
        currentTexture = usedBrickTexture;
        timerSinceCoinBlockHit.invalidate();
    }

    if(timerBounceAnimation.elapsed() < animationDuration){
        if(timerBounceAnimation.elapsed() < animationDuration/2){
            setPositionY(position.y()-1.5);
        }
        else{
            setPositionY(position.y()+1.5);
        }
    }
    else{
        setPositionY(getHitbox().y());
    }
}
