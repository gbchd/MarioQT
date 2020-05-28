#ifndef BOX_H
#define BOX_H

#include "inert.h"

class Box : public Inert
{
private:
    QList<QPixmap> texture;
public:
    Box();
};

#endif // BOX_H
