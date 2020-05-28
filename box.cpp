#include "box.h"

Box::Box()
{
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-0.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-1.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-2.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-3.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));

    setCurrentTexture(texture[0]);
}
