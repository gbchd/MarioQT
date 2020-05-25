#ifndef MARIO_H
#define MARIO_H

#include "entity.h"
#include "enemy.h"

class Mario : public Entity
{
private:
    // === Sprites ===
    QPixmap texture_walk[2][3]; // small/big walking animation (3 textures)
    QPixmap texture_stand[2]; // small/big stand texture
    QPixmap texture_jump[2]; // small/big jump texture
    QPixmap texture_dead; // Mario dies
    QPixmap texture_small_to_big[4]; // Mario small to big transformation
    // ================


    // === States ===
    bool big;
    int runningSpeed;
    bool onFire;
    // ==============

    void setBig();
    void setSmall();
    void collisionOnBottomHandler(ObjectModel *o) override;
    void collisionOnLeftHandler(ObjectModel * o) override;
    void collisionOnRightHandler(ObjectModel * o) override;
    void collisionOnTopHandler(ObjectModel * o) override;

    // === Jumping tools ===
    /**
      * Mario's jump is in three phases which are represented by three different gravities.
      * See https://youtu.be/hG9SzQxaCm8 for more informations.
      */

    bool jumping = false;
    int jumpHeight = 5*BLOCSIZE;

    // Theses floats are the number of frame / time to get to the summit of a jump
    // They are used to calculate the gravity
    float jumpUpDuration = 30;
    float jumpDownDuration = 20;

    // Default gravity for mario
    // Also used to change the trajectory of the ending of Mario's jump
    // (to give the same vibe as the original Super Mario snes game)
    float defaultGravity = 2*jumpHeight/(jumpDownDuration*jumpDownDuration);

    // Gravity of the beginning of the jump
    float jumpGravity = 2*jumpHeight/(jumpUpDuration*jumpUpDuration);

    // Gravity to speed up the change of velocity
    // This gives the user the impression of control of their jump
    // by pressing longer or not the jump
    float jumpReleaseGravity = 100;

    float jumpInitialSpeed = -2*jumpHeight/jumpUpDuration; // V0 = 2h/t

    int deathJumpHeight = 4*BLOCSIZE;
    float deathJumpDuration = 30;
    float deathJumpSpeed = -2*deathJumpHeight/30;
    float deathJumpGravity = 2*deathJumpHeight/(deathJumpDuration*deathJumpDuration);
    // ====================

public:
    Mario();
    ~Mario();

    void advance(QList<ObjectModel*> objects);
    virtual void advance() override;
    virtual void animate() override;


    void setRunning(bool r){ running = r; }
    void jump();
    void releaseJump();
    void hurt();
    void die() override;
};

#endif // MARIO_H
