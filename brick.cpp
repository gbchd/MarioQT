#include "brick.h"

Brick::Brick()
{
    currentTexture = QPixmap(loadTexture(":/resources/graphics/blocs/brick.bmp").scaled(BLOCSIZE, BLOCSIZE));
}
