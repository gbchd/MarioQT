#ifndef PODOBOO_H
#define PODOBOO_H

#include "entity.h"

class Podoboo : public Entity
{
private:
    bool goingDown;

    QPointF spawnPosition;
    float amplitude; // The number of blocks it will travel before coming back
    int travelDuration; // (in ms) The time it will take the platform to go all the way down
    QElapsedTimer travelTimer;
    float travelDistance; // The distance it must travel at each frame

public:
    Podoboo();
    Podoboo(QPointF initialPosition);

    bool isPodobooGoingDown() { return goingDown; }

    void advance() override;
    void animate() override;
};

#endif // PODOBOO_H
