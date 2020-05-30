#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include <QElapsedTimer>

class Enemy : public Entity
{
protected:
    QPixmap texture_dead;

    bool hurtable;		// whether it can be hurt by Mario's feet
    bool hurtful;       // can hurt other (more specifically mario)

    QElapsedTimer timeOfDeath;
    int delayBeforeDeletable = 500; //in ms

public:
    Enemy();

    // getters
    bool isHurtable(){return hurtable;}
    bool isHurtful(){return hurtful;}
    virtual void die() override;
    virtual void hurt();
};

#endif // ENEMY_H
