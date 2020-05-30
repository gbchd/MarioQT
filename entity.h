#ifndef ENTITY_H
#define ENTITY_H

#include "objectmodel.h"
#include "direction.h"
#include "inert.h"
#include <QElapsedTimer>

class Entity : public ObjectModel
{

protected:
    // === States ===
    bool phantom = false;
    bool dead = false;
    bool moving = false;
    bool sliding = false;
    bool running = false;
    bool collidableWithOtherEntities = true;

    bool grounded = false;
    ObjectModel * ground; // Ne dépent pas du destructeur de cet objet

    QPointF velocity = QPointF(0,0);
    float gravity = 2; // DEFAULT VALUE SHOULD BE RESET IN CHILD

    int speed = 1;
    int speedLimit = 5;
    Direction movingDirection;

    QRectF hitboxEntity;
    // ==============


    // === Animations ===
    int durationOfPhantom = 2000; // in ms
    QElapsedTimer timerPhantom;
    // ==================

    void updateVelocity();
    void applyVelocityLimit();
    void updatePosition();

    void groundHandler();
    virtual void reactionNoMoreOnGround();

    void setHitboxEntityWidth(float w){ hitboxEntity.setWidth(w); }
    void setHitboxEntityHeight(float h){ hitboxEntity.setHeight(h); }

    virtual void solveCollision(ObjectModel * o);

    void bounce();
    virtual void die(){}

public:
    Entity();
    virtual ~Entity();

    // Used to compute the next location
    virtual void advance() = 0;

    void setCurrentTexture(QPixmap texture) override;


    void moveTo(QPointF newPosition) override;
    void moveTo(float x, float y) override;


    QRectF getHitboxEntity(){ return hitboxEntity; }

    bool isDead(){return dead;}
    bool isCollidableWithOtherEntities(){return collidableWithOtherEntities;}

    bool isColliding(ObjectModel * o);
    void collisionHandler(ObjectModel * o);

    virtual void startPhantom();
    virtual void stopPhantom();

    void moveOnXBy(float x){ moveTo(position.x()+x,position.y()); }
    void moveOnYBy(float y){ moveTo(position.x(),position.y()+y); }

    void setMoving(bool state){ moving = state; }
    Direction getDirection(){ return movingDirection; }
    void setDirection(Direction direction){ movingDirection = direction; currentTexture = currentTexture.transformed(QTransform().scale(-1,1));}

    virtual void collisionOnLeftHandler(ObjectModel * o) override;
    virtual void collisionOnRightHandler(ObjectModel * o) override;
    virtual void collisionOnTopHandler(ObjectModel * o) override;
    virtual void collisionOnBottomHandler(ObjectModel * o) override;

};

#endif // ENTITY_H
