#include "wall.h"

Wall::Wall()
{
    currentTexture = QPixmap(loadTexture(":/resources/graphics/blocs/wall.png").scaled(BLOCSIZE, BLOCSIZE));
}
