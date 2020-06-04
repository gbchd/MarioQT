#ifndef MARIO_H
#define MARIO_H

#include "entity.h"
#include <QArrayData>
#include <QColorTransform>
#include <QSoundEffect>

class CollectableItem;
class Coin;
class FireBall;
class Flagpole;

class Mario : public Entity
{
private:
    // === Sprites ===   
    QList<QPixmap> texture_walk[3]; // small/big/fire walking animation (3 textures)
    QPixmap texture_stand[4]; // small/big/fire stand texture
    QPixmap texture_jump[3]; // small/big/fire jump texture
    QPixmap texture_hang[3]; // small/big/fire hang texture
    QPixmap texture_fire;
    QPixmap texture_dead; // Mario dies
    QPixmap texture_transitions_animations[20]; // Mario small to big transformation
    // ================

    // === Animations ===
    bool changedDirection = false; // Detect when we change direction
    int durationWalkTexture = 150; // in ms
    int durationRunningTexture = 100; // in ms
    QElapsedTimer timerWalk;
    int currentWalkTexture = 0;
    int durationOfTransformation = 100; // in ms
    QElapsedTimer timerTransformation;
    int currentTransformingTexture;
    // ==================

    // === Attributes for animations ===
    bool isInFlagpoleCinematic; // If true, we don't listen to the key events to control mario
    enum FlagpoleCinematicState{NOFLAGPOLECINEMATICSTATE, HANGINGONFLAGPOLE, JUMPINGFORTHEGROUND, WALKINGTOTHEEXIT, ARRIVEDATCASTLE};
    FlagpoleCinematicState marioFlagpoleCinematicState;
    QPointF flagBottomPos;
    int durationBeforeJumpingFromPole = 400; // in ms;
    QElapsedTimer timerBeforeJumpingFromPole;
    // =================================

    // === States ===
    bool big;
    int runningSpeed;
    bool onFire;
    bool transforming;
    bool transformingDown;
    int durationFireTimer = 100; // in ms
    QElapsedTimer fireballShootingTimer;
    void doTransforming();
    void setSmallToMed();
    void setSmallToBig();
    void setMedToSmall();
    void setMedToBig();
    void setBigToSmall();
    void setBigToMed();
    void setBigToFiery();
    void setFieryToBig();
    void setSmall();
    // ==============

    // === Jumping tools ===
    /**
      * Mario's jump is in three phases which are represented by three different gravities.
      * See https://youtu.be/hG9SzQxaCm8 for more informations.
      */

    bool jumping = false;
    int jumpHeight = 4.2*BLOCSIZE;

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
    void handleFlagpoleCollision(Flagpole * flagpole);

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
    void startTransforming();
    bool isTransforming(){ return transforming; }
    Direction getDirection(){return movingDirection;};
    bool getIsInFlagpoleCinematic(){ return isInFlagpoleCinematic; }
    bool isBig(){ return big; }
    bool isOnFire(){ return onFire; }

    FireBall * shootFireBall();

    void collisionByDefaultHandler(ObjectModel *o) override;
    void collisionOnBottomHandler(ObjectModel *o) override;
    void collisionOnLeftHandler(ObjectModel * o) override;
    void collisionOnRightHandler(ObjectModel * o) override;
    void collisionOnTopHandler(ObjectModel * o) override;

    void playSound(QString soundPath);

    void handleCollectableItemCollision(CollectableItem * collectableItem);
};

#endif // MARIO_H
