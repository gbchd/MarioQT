#ifndef PIRANHAPLANT_H
#define PIRANHAPLANT_H

#include "enemy.h"

class PiranhaPlant : public Enemy
{
private:
    QPixmap textures[2];

public:
    PiranhaPlant();

    void advance() override;
    void animate() override;
};

#endif // PIRANHAPLANT_H
