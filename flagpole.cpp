#include "flagpole.h"

Flagpole::Flagpole()
{
    currentTexture = loadTexture(":/resources/graphics/flagpole.png").scaled(BLOCSIZE, 11*BLOCSIZE);

    int hbwidth = BLOCSIZE/4;
    hitbox.setX((BLOCSIZE-hbwidth)/2);
    setHitboxWidth(hbwidth);

    hitbox.setHeight(11*BLOCSIZE);
}
