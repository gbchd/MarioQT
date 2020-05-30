#include "brick.h"

#include <QDebug>

Brick::Brick()
{
    currentTexture = QPixmap(loadTexture(":/resources/graphics/blocs/brick.bmp").scaled(BLOCSIZE, BLOCSIZE));
    coinBrick = false;
    brickState = NOBRICKSTATE;
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
    if(isMarioBig && !coinBrick){
        qDebug() << "state = break";
        brickState = BREAKBRICK; // Will be handled in the gamecontroller later
    }
    else if(coinBrick){
        brickState = GIVECOIN; // Will be handled in the gamecontroller later
        if(!timerSinceCoinBlockHit.isValid()){ timerSinceCoinBlockHit.start(); }
        startBlockBounceAnimation();
    }
    else{
        startBlockBounceAnimation();
    }
}

void Brick::animate()
{
    if(timerSinceCoinBlockHit.isValid() && timerSinceCoinBlockHit.elapsed() > timeToGetCoins){
        brickState = NOBRICKSTATE;
        coinBrick = false;
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
