#ifndef COIN_H
#define COIN_H

#include "entity.h"

class Coin : public Entity
{
public:
    Coin();
    virtual void advance() override;
    virtual void animate() override;
};

#endif // COIN_H
