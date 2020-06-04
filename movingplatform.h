#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

#include "inert.h"

class MovingPlatform : public Inert
{
private:
    bool bigMovingPlatform; // true = big, false = small
    QPointF spawnPosition;
    float amplitude; // The number of blocks it will travel before coming back
    int travelDuration; // (in ms) The time it will take the platform to go all the way down
    QElapsedTimer travelTimer;
    float travelDistance; // The distance it must travel at each frame

    bool goingDown;

public:
    MovingPlatform(bool b);

    bool isItABigMovingPlatform() { return bigMovingPlatform; };
    void setSpawnPosition(QPointF sp) { spawnPosition = sp; }
    bool isGoingDown() { return goingDown; }
    float getTravelDistance() { return travelDistance; }

    virtual void animate() override;
};

#endif // MOVINGPLATFORM_H
