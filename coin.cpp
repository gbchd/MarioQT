#include "coin.h"

Coin::Coin()
{
    currentTexture = loadTexture(":/resources/graphics/coin-1.png").scaled(BLOCSIZE/1.5, BLOCSIZE/1.5, Qt::KeepAspectRatio);
}

void Coin::advance()
{

}

void Coin::animate()
{

}
