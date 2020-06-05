#ifndef PIRANHAPLANT_H
#define PIRANHAPLANT_H

#include "enemy.h"

class PiranhaPlant : public Enemy
{
private:
    QPixmap textures[2];
    int animationDelay = 150; // in ms
    QElapsedTimer animationTimer;
    int textureIndex;

    enum PiranhaPlantState {NOPIRANHAPLANTSTATE, PIRANHAGOINGDOWN, PIRANHAGOINGUP, PIRANHAWAITINGDOWN, PIRANHAWAITINGUP};
    PiranhaPlantState piranhaPlantState;
    QPointF spawnPosition;
    float amplitude; // The number of blocks it will travel before coming back
    int travelDuration; // (in ms) The time it will take to go all the way down
    QElapsedTimer travelTimer;
    float travelDistance; // The distance it must travel at each frame

public:
    PiranhaPlant();

    void setSpawnPosition(QPointF sp) { spawnPosition = sp; }

    void advance() override;
    void animate() override;

    void collisionByDefaultHandler(ObjectModel *o) override;
    void collisionOnBottomHandler(ObjectModel *o) override;
    void collisionOnLeftHandler(ObjectModel * o) override;
    void collisionOnRightHandler(ObjectModel * o) override;
    void collisionOnTopHandler(ObjectModel * o) override;
};

#endif // PIRANHAPLANT_H
