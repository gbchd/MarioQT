#ifndef BRICKDEBRIS_H
#define BRICKDEBRIS_H

#include "entity.h"

class BrickDebris : public Entity
{
private:
    int lifeDuration = 2000; // in ms
    QElapsedTimer timerToDeletion;
public:
    BrickDebris(Direction direction);

    virtual void advance() override;
    virtual void animate() override;
};

#endif // BRICKDEBRIS_H
