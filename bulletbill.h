#ifndef BULLETBILL_H
#define BULLETBILL_H

#include "enemy.h"

class BulletBill : public Enemy
{
protected:
    virtual void collisionOnLeftHandler(ObjectModel * o) override;
    virtual void collisionOnRightHandler(ObjectModel * o) override;
    virtual void collisionOnTopHandler(ObjectModel * o) override;
    virtual void collisionOnBottomHandler(ObjectModel * o) override;

public:
    BulletBill();

    // pure virtual methods that must be implemented
    std::string name(){ return "BulletBill";};
    void advance() override;
    void animate() override;
    void hurt() override;

    void setUpLeftMovingBulletBill(QPointF billBlasterPos);
    void setUpRightMovingBulletBill(QPointF billBlasterPos);
};

#endif // BULLETBILL_H
