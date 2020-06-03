#include "coin.h"

#include "mario.h"

Coin::Coin(bool coinSpawnedByBloc)
{
    score = 200;

    textureList[0] = loadTexture(":/resources/graphics/items/coin-0.png").scaled(BLOCSIZE/1, BLOCSIZE/1, Qt::KeepAspectRatio);
    textureList[1] = loadTexture(":/resources/graphics/items/coin-1.png").scaled(BLOCSIZE/1, BLOCSIZE/1, Qt::KeepAspectRatio);
    textureList[2] = loadTexture(":/resources/graphics/items/coin-2.png").scaled(BLOCSIZE/1, BLOCSIZE/1, Qt::KeepAspectRatio);
    textureList[3] = loadTexture(":/resources/graphics/items/coin-3.png").scaled(BLOCSIZE/1, BLOCSIZE/1, Qt::KeepAspectRatio);
    currentTexture = textureList[0];
    frameNumber = 0;
    timerAnimation.start();

    this->coinSpawnedByBloc = coinSpawnedByBloc;

    if(coinSpawnedByBloc){
        gravity = bounceGravity;
        velocity.setY(bounceSpeed);
        counterGameFramesUntilDeath = 0;
        speedLimit = 100;
    }
    else{
        setHitboxEntityWidth(textureList[0].width());
        setHitboxEntityHeight(textureList[0].height());

        setHitboxWidth(textureList[0].width());
        setHitboxHeight(textureList[0].height());

        solid = false;
        gravity = 0;
        moving = false;
    }
}

void Coin::advance()
{
    if(coinSpawnedByBloc){
        velocity.setY(velocity.y() + gravity);

        moveTo(position+velocity);

        if(counterGameFramesUntilDeath > 40){
            Score::add(score);
            Score::addCoin();
            deletable = true;
        }
        else{
            counterGameFramesUntilDeath++;
        }
    }
}

void Coin::animate()
{
    if(timerAnimation.elapsed() > delayBetweenTwoFrames){
        timerAnimation.restart();
        if(frameNumber > 3){
            frameNumber = 0;
        }
        currentTexture = textureList[frameNumber];
        frameNumber++;


    }
}

void Coin::collisionByDefaultHandler(ObjectModel *o)
{
    handleCollisionWithObject(o);
}

void Coin::collisionOnBottomHandler(ObjectModel *o)
{
    handleCollisionWithObject(o);
}

void Coin::collisionOnLeftHandler(ObjectModel *o)
{
    handleCollisionWithObject(o);
}

void Coin::collisionOnRightHandler(ObjectModel *o)
{
    handleCollisionWithObject(o);
}

void Coin::collisionOnTopHandler(ObjectModel *o)
{
    handleCollisionWithObject(o);
}

void Coin::handleCollisionWithObject(ObjectModel *o)
{
    Mario * mario = dynamic_cast<Mario *>(o);
    if(mario != nullptr){
        Score::add(score);
        Score::addCoin();
        deletable = true;
    }
}
