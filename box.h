#ifndef BOX_H
#define BOX_H

#include "inert.h"

enum BoxContent {NOTHING, MUSHROOM, FLOWER, COIN, STAR};

class Box : public Inert
{
private:
    QList<QPixmap> texture;

    BoxContent boxContent;

public:
    Box();
    void setBoxContent(BoxContent bc) { boxContent = bc; }
    BoxContent getBoxContent() { return boxContent; }
};

#endif // BOX_H
