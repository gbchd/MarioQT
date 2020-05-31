#ifndef GOOMBA_H
#define GOOMBA_H

#include "enemy.h"
#include "mario.h"
#include "koopa.h"

class Goomba : public Enemy
{
protected:
    // textures
    QList<QPixmap> texture_walk; // walking animation (2 textures)

    int durationWalkTexture = 150; // in ms
    QElapsedTimer timerWalk;
    int currentWalkTexture = 0;

public:
    Goomba(Direction spawnDirection = RIGHT);

    // pure virtual methods that must be implemented
    std::string name(){ return "Goomba";};
    void advance() override;
    void animate() override;
    void hurt() override;

    void collisionOnLeftHandler(ObjectModel *o) override;
    void collisionOnRightHandler(ObjectModel *o) override;
    void collisionOnTopHandler(ObjectModel *o) override;
};

#endif // GOOMBA_H
