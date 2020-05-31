#include "pipe.h"

Pipe::Pipe(TypePipe t)
{
    typePipe = t;

    switch (typePipe) {
    case SMALLPIPEOBJECT:
        currentTexture = loadTexture(":/resources/graphics/pipe-small.png").scaled(2*BLOCSIZE, 2*BLOCSIZE);
        setHitboxWidth(2*BLOCSIZE);
        setHitboxHeight(2*BLOCSIZE);
        break;
    case MEDPIPEOBJECT:
        currentTexture = loadTexture(":/resources/graphics/pipe-med.png").scaled(2*BLOCSIZE, 3*BLOCSIZE);
        setHitboxWidth(2*BLOCSIZE);
        setHitboxHeight(3*BLOCSIZE);
        break;
    case BIGPIPEOBJECT:
        currentTexture = loadTexture(":/resources/graphics/pipe-big.png").scaled(2*BLOCSIZE, 4*BLOCSIZE);
        setHitboxWidth(2*BLOCSIZE);
        setHitboxHeight(4*BLOCSIZE);
        break;
    case NOPIPETYPE:
    default:
        break;
    }
}
