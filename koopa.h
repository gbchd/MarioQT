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
    QPixmap texture_walk[2];            // walking animation (2 textures)
    QPixmap texture_shell;
    static const int walk_div = 10;

    void reactionNoMoreOnGround() override;

    void collisionOnLeftHandler(ObjectModel *o) override;
    void collisionOnRightHandler(ObjectModel *o) override;
    void collisionOnTopHandler(ObjectModel *o) override;

public:
    Koopa(Direction spawnDirection = RIGHT);

    // pure virtual methods that must be implemented
    std::string name(){ return "Goomba";};
    void advance() override;
    void animate() override;
    void hurt() override;
};

#endif // KOOPA_H
