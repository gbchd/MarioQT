#ifndef FIREBALL_H
#define FIREBALL_H

#include "entity.h"

class FireBall : public Entity
{
private:
    QPixmap textures[4];
    int animationDelay = 100; // in ms
    int textureNumber;

    int deathFrameCounter;
    QPixmap deathTextures[3];

    float bounceHeight = BLOCSIZE;
    float bounceDuration = 10; // in number of frames
    float bounceSpeed = -2*bounceHeight/bounceDuration;
    float bounceGravity = 2*bounceHeight/(bounceDuration*bounceDuration);

    QElapsedTimer animationTimer;

public:
    FireBall(Direction direction);

    virtual void advance() override;
    virtual void animate() override;
    virtual void die() override;

    virtual void collisionByDefaultHandler(ObjectModel *o) override;
    void collisionOnBottomHandler(ObjectModel *o) override;
    void collisionOnLeftHandler(ObjectModel * o) override;
    void collisionOnRightHandler(ObjectModel * o) override;
    void collisionOnTopHandler(ObjectModel * o) override;
};

#endif // FIREBALL_H
