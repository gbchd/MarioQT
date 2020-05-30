#ifndef COLLECTABLEITEM_H
#define COLLECTABLEITEM_H

#include "entity.h"

enum TypeItem {COINCOLLECTABLE, STARCOLLECTABLE, MUSHROOMCOLLECTABLE, FLOWERCOLLECTABLE};

class CollectableItem : public Entity
{
private:
    TypeItem typeItem;

    QPointF spawnerBlockPos;

    bool itemWasPickedUpByMario;

    int durationSpawnAnimation = 1100; // in ms
    QElapsedTimer spawnAnimationTimer;

public:
    CollectableItem(TypeItem t, QPointF spawnerBlockPos);
    bool wasItemPickedUpByMario() { return itemWasPickedUpByMario; }
    void setItemPickedUpByMario(bool b) { itemWasPickedUpByMario = b; }
    TypeItem getItemType() { return typeItem; }
    virtual void advance() override;
    virtual void animate() override;

    void collisionOnBottomHandler(ObjectModel *o) override;
    void collisionOnLeftHandler(ObjectModel * o) override;
    void collisionOnRightHandler(ObjectModel * o) override;
    void collisionOnTopHandler(ObjectModel * o) override;

    void handleCollisionWithObject(ObjectModel * o);
};

#endif // COLLECTABLEITEM_H
