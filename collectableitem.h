#ifndef COLLECTABLEITEM_H
#define COLLECTABLEITEM_H

#include "entity.h"

enum TypeItem {COINCOLLECTABLE, STARCOLLECTABLE, MUSHROOMCOLLECTABLE, FLOWERCOLLECTABLE};

class CollectableItem : public Entity
{
private:
    TypeItem typeItem;

    QPointF spawnerBlockPos;

    int durationSpawnAnimation = 1100; // in ms
    QElapsedTimer spawnAnimationTimer;

public:
    CollectableItem(TypeItem t, QPointF spawnerBlockPos);
    virtual void advance() override;
    virtual void animate() override;
};

#endif // COLLECTABLEITEM_H
