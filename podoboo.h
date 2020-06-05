#ifndef PODOBOO_H
#define PODOBOO_H

#include "entity.h"

class Podoboo : public Entity
{
private:
    QPixmap orignalTexture;

    float bounceHeight = 10*BLOCSIZE;
    float bounceDuration = 80; // number of in-game frames
    int bounceFrameCounter;
    float bounceSpeed = -2*bounceHeight/bounceDuration;
    float bounceGravity = 2*bounceHeight/(bounceDuration*bounceDuration);

public:
    Podoboo();
    Podoboo(QPointF initialPosition);

    void advance() override;
    void animate() override;
};

#endif // PODOBOO_H
