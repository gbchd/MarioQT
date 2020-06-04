#ifndef COIN_H
#define COIN_H

#include "entity.h"
#include <QSoundEffect>

class Coin : public Entity
{
private:
    QPixmap textureList[4];
    int delayBetweenTwoFrames = 100; // in ms
    int frameNumber;
    QElapsedTimer timerAnimation;

    //=======attributes for coins from blocs=======
    bool coinSpawnedByBloc;
    int counterGameFramesUntilDeath;

    float bounceHeight = 2.2*BLOCSIZE;
    float bounceDuration = 20; // number of in-game frames
    float bounceSpeed = -2*bounceHeight/bounceDuration;
    float bounceGravity = 2*bounceHeight/(bounceDuration*bounceDuration);
    //=============================================

public:
    Coin(bool coinSpawnedByBloc);

    static QSoundEffect * sound;

    virtual void advance() override;
    virtual void animate() override;

    void collisionByDefaultHandler(ObjectModel *o) override;
    void collisionOnBottomHandler(ObjectModel *o) override;
    void collisionOnLeftHandler(ObjectModel * o) override;
    void collisionOnRightHandler(ObjectModel * o) override;
    void collisionOnTopHandler(ObjectModel * o) override;

    void handleCollisionWithObject(ObjectModel * o);
};

#endif // COIN_H
