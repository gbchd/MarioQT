#ifndef FLAGPOLE_H
#define FLAGPOLE_H

#include "inert.h"

class Flagpole : public Inert
{
private:
    Inert * flag;
    bool flagIsGoingDown;

public:
    Flagpole();
    Inert * getFlag() { return flag; }
    void moveFlagOnPole();

    void animate() override;
    void collisionOnLeftHandler(ObjectModel *o) override;
    void collisionOnRightHandler(ObjectModel *o) override;
    void collisionOnTopHandler(ObjectModel *o) override;
    void collisionOnBottomHandler(ObjectModel *o) override;
};

#endif // FLAGPOLE_H
