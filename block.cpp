#include "block.h"

Block::Block()
{
    currentTexture = QPixmap(loadTexture(":/resources/graphics/blocs/block.png").scaled(BLOCSIZE, BLOCSIZE));
}
