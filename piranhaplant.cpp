#include "piranhaplant.h"

PiranhaPlant::PiranhaPlant()
{
    textures[0] = loadTexture(":/resources/graphics/mobs/piranha/piranha-0.png").scaled(1.3*16/24*BLOCSIZE, 1.3*BLOCSIZE, Qt::KeepAspectRatio);
    textures[1] = loadTexture(":/resources/graphics/mobs/piranha/piranha-1.png").scaled(1.3*16/24*BLOCSIZE, 1.3*BLOCSIZE, Qt::KeepAspectRatio);

    setHitboxWidth(1.3*16/24*BLOCSIZE);
    setHitboxHeight(1.3*BLOCSIZE);
    setHitboxEntityWidth(1.3*16/24*BLOCSIZE);
    setHitboxEntityHeight(1.3*BLOCSIZE);

    setCurrentTexture(textures[0]);
}

void PiranhaPlant::advance()
{

}

void PiranhaPlant::animate()
{

}
