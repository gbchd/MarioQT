#ifndef BOX_H
#define BOX_H

#include "inert.h"
#include "collectableitem.h"
#include "mario.h"

enum BoxContent {EMPTYBOX, MUSHROOMBOX, FLOWERBOX, COINBOX, STARBOX, USEDBOX};

class Box : public Inert
{
private:
    QList<QPixmap> texture;

    BoxContent boxContent;
    bool used;

    bool needToSpawnItem;

    QElapsedTimer timerBounceAnimation;
    int animationDuration = 250; //in ms
    QPointF originalPosition;

public:
    Box();
    void setBoxContent(BoxContent bc) { boxContent = bc; }
    BoxContent getBoxContent() { return boxContent; }
    bool doesBoxNeedToSpawnItem() { return needToSpawnItem; }
    void setBoxNeedToSpawnItem(bool b) { needToSpawnItem = b; }
    bool isBoxUsed(){ return used; }
    void handleCollisionFromMario();
    void startBlockBounceAnimation();

    void collisionOnBottomHandler(ObjectModel *o) override;

    CollectableItem* spawnMushroom();
    CollectableItem* spawnFlower();
    CollectableItem* spawnCoin();
    CollectableItem* spawnStar();

    void animate() override;
};

#endif // BOX_H
