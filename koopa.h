#ifndef KOOPA_H
#define KOOPA_H

#include "enemy.h"
#include "mario.h"

class Koopa : public Enemy
{
protected:

    //State
    bool shell;

    // textures
    // textures
    QList<QPixmap> texture_walk;                        // walking animation (2 textures)
    QPixmap texture_shell;
    int durationWalkTexture = 100; // in ms
    QElapsedTimer timerWalk;
    int currentWalkTexture = 0;           // walking animation (2 textures)

    void reactionNoMoreOnGround() override;

    void collisionOnLeftHandler(ObjectModel *o) override;
    void collisionOnRightHandler(ObjectModel *o) override;
    void collisionOnTopHandler(ObjectModel *o) override;

    void setCurrentTexture(QPixmap texture) override;

public:
    Koopa(Direction spawnDirection = RIGHT);

    // pure virtual methods that must be implemented
    std::string name(){ return "Goomba";};
    void advance() override;
    void animate() override;
    void hurt() override;

    void hitOnTop(ObjectModel *o);
};

#endif // KOOPA_H
