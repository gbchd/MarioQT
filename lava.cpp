#include "lava.h"

#include <QDebug>

Lava::Lava()
{
    textures[0] = loadTexture(":/resources/graphics/blocs/lava-0.png").scaled(BLOCSIZE/1, BLOCSIZE/1, Qt::KeepAspectRatio);
    textures[1] = loadTexture(":/resources/graphics/blocs/lava-1.png").scaled(BLOCSIZE/1, 11/32*BLOCSIZE/1, Qt::KeepAspectRatio);

    lavaWave = false;
    setCurrentTexture(textures[0]);

    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(BLOCSIZE);
}

Lava::Lava(bool typeWave)
{
    if(typeWave){
        setCurrentTexture(loadTexture(":/resources/graphics/blocs/lava-1.png").scaled(BLOCSIZE/1, 0.34375*BLOCSIZE, Qt::KeepAspectRatio));
        lavaWave = true;
        setHitboxHeight(0.34375*BLOCSIZE);
    }
    else{
        setCurrentTexture(loadTexture(":/resources/graphics/blocs/lava-0.png").scaled(BLOCSIZE/1, BLOCSIZE/1, Qt::KeepAspectRatio));
        lavaWave = false;
        setHitboxHeight(BLOCSIZE);
    }

    setHitboxWidth(BLOCSIZE);
}

void Lava::setLavaTypeWave()
{
    lavaWave = true;
    setCurrentTexture(textures[1]);
    setHitboxHeight(11/32*BLOCSIZE);
}
