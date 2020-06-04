#ifndef FIREBAR_H
#define FIREBAR_H

#include "inert.h"

#include <QtMath>

class FireBall;

class Firebar : public Inert
{
private:
    FireBall * fireballs[6]; // Firebar posses a reference to all the fireballs it controls

    int rotationDuration = 5000; // in ms
    float currentAngle = 0; // Varies from 0 to 360
    QElapsedTimer rotationTimer;
    float fireballwidth;

public:
    Firebar();
    void setFireball(int indice, FireBall * fireball);

    virtual void animate() override;
};

#endif // FIREBAR_H
