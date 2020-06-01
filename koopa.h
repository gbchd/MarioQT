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
    int currentWalkTexture = 0;                         // walking animation (2 textures)

    //Used to prevent mario from taking damage immediatly after hitting the shell on the side
    //We don't use a timer here in case of low framerate
    int counterNonHurtfulFrame = 0;
    int maxNonHurtfulFrame = 10;
    void hurtfulFrameHandler();

    void collisionOnLeftHandler(ObjectModel *o) override;
    void collisionOnRightHandler(ObjectModel *o) override;
    void collisionOnTopHandler(ObjectModel *o) override;
    void collisionOnBottomHandler(ObjectModel *o) override;

public:
    Koopa(Direction spawnDirection = RIGHT);

    bool isInShell(){return shell;};
    bool isMoving(){return moving;};

    // pure virtual methods that must be implemented
    std::string name(){ return "Goomba";};
    void advance() override;
    void animate() override;
    void hurt() override;
};

#endif // KOOPA_H
