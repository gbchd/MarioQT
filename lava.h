#ifndef LAVA_H
#define LAVA_H

#include "inert.h"

class Lava : public Inert
{
private:
    QPixmap textures[2];
    bool lavaWave;

public:
    Lava();
    Lava(bool typeWave);

    void setLavaTypeWave();
    bool isLavaTypeWave() { return lavaWave; }
};

#endif // LAVA_H
