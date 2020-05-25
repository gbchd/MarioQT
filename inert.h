#ifndef INERT_H
#define INERT_H

#include "objectmodel.h"


class Inert : public ObjectModel
{
public:
    Inert();
    virtual ~Inert();

    // Used to compute the next texture
    virtual void animate();

};

#endif // INERT_H
