#ifndef BRICK_H
#define BRICK_H

#include "inert.h"

class Brick : public Inert
{
private:
    bool coinBrick;

public:
    Brick();
    void setCoinBrick(bool b) { coinBrick = b; }
    bool getCoinBrick(){ return coinBrick; }
};

#endif // BRICK_H
