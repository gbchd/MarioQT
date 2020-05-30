#include "collectableitem.h"

CollectableItem::CollectableItem(TypeItem t, QPointF spawnerBlockPos)
{
    typeItem = t;
    this->spawnerBlockPos = spawnerBlockPos;
    moveTo(spawnerBlockPos);
    gravity = 0;
    zValue = 0;
    moving = false;

    switch(typeItem){
    case COINCOLLECTABLE:
        currentTexture = loadTexture(":/resources/graphics/coin-1.png").scaled(BLOCSIZE*0.75, BLOCSIZE*0.75, Qt::KeepAspectRatio);
        break;
    case STARCOLLECTABLE:
        currentTexture = loadTexture(":/resources/graphics/star.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        spawnAnimationTimer.start();
        break;
    case MUSHROOMCOLLECTABLE:
        currentTexture = loadTexture(":/resources/graphics/mushroom-green.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        spawnAnimationTimer.start();
        break;
    case FLOWERCOLLECTABLE:
        currentTexture = loadTexture(":/resources/graphics/flower.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        spawnAnimationTimer.start();
        break;
    default:
        break;
    }
}

void CollectableItem::advance()
{

}
void CollectableItem::animate()
{
    if(spawnAnimationTimer.isValid()){
        if(spawnAnimationTimer.elapsed() < durationSpawnAnimation){
            moveTo(position.x(), spawnerBlockPos.y() - ((float)BLOCSIZE/(float)durationSpawnAnimation)*spawnAnimationTimer.elapsed());
        }
        else{
            spawnAnimationTimer.invalidate();
        }
    }
}
