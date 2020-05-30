#ifndef BRICK_H
#define BRICK_H

#include "inert.h"

enum BrickState {NOBRICKSTATE, BREAKBRICK, GIVECOIN};

class Brick : public Inert
{
private:
    bool coinBrick;
    QElapsedTimer timerSinceCoinBlockHit;
    int timeToGetCoins = 3000; //in ms

    BrickState brickState;
    QElapsedTimer timerBounceAnimation;
    int animationDuration = 250; //in ms
    QPointF originalPosition;

public:
    Brick();
    void setCoinBrick(bool b) { coinBrick = b; }
    bool getCoinBrick(){ return coinBrick; }
    void startBlockBounceAnimation();
    void handleCollisionFromMario(bool isMarioBig);
    BrickState getBrickState(){ return brickState; }
    void setBrickState(BrickState bs){ brickState = bs; }

    void animate() override;
};

#endif // BRICK_H
