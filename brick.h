#ifndef BRICK_H
#define BRICK_H

#include <QSoundEffect>
#include "inert.h"
#include "mario.h"
#include "brickdebris.h"
#include "coin.h"

enum BrickState {NOBRICKSTATE, BRICKWILLGIVECOINONNEXTHIT, USEDCOINBRICK, GIVECOIN, BREAKBRICK};

class Brick : public Inert
{
private:
    QElapsedTimer timerSinceCoinBlockHit;
    int timeToGetCoins = 3000; //in ms

    BrickState brickState;
    QElapsedTimer timerBounceAnimation;
    int animationDuration = 250; //in ms
    QPointF originalPosition;

    QPixmap usedBrickTexture;

public:
    Brick();
    void startBlockBounceAnimation();
    BrickState getBrickState(){ return brickState; }
    void setBrickState(BrickState bs){ brickState = bs; }

    QList<BrickDebris*> doBreak();
    Coin* spawnCoin();

    void animate() override;

    void playSound(QString soundPath);
    void collisionOnBottomHandler(ObjectModel * o) override;
};

#endif // BRICK_H
