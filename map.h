#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPainter>

#include "inert.h"
#include "entity.h"
#include "mario.h"
#include "goomba.h"
#include "koopa.h"
#include "wall.h"
#include "block.h"
#include "box.h"
#include "brick.h"
#include "billblaster.h"
#include "scenery.h"
#include "pipe.h"
#include "trampoline.h"
#include "flagpole.h"
#include "movingplatform.h"
#include "firebar.h"
#include "fireball.h"
#include "podoboo.h"
#include "piranhaplant.h"
#include "lava.h"
#include "objectmodel.h"

class Map
{
public:
    Map();
    Map(QString filename);

    QString getName(){return name;}
    QString getCreator(){return creator;}
    QDateTime getCreationDate(){return creationDate;}
    int getWidth() { return width; }
    int getHeight() { return height; }

    int getPlayerSpawnX(){return playerSpawnX;}
    int getPlayerSpawnY(){return playerSpawnY;}

    QList<Inert*> getInerts(){return inerts;}
    QList<Entity*> getEntities(){return entities;}

    int getNumberInherts(){return inerts.size();}
    Inert * getInert(int pos){return inerts.at(pos);}
    int getNumberEntities(){return entities.size();}
    Entity * getEntity(int pos){return entities.at(pos);}

private:

    void addInert(QJsonObject inertObject);
    void addEntity(QJsonObject entityObject);
    QPixmap paintSurface(int w, int h, QString texture);

    // Utilities

    int block_size;

    // Map attributes

    QString name;
    QString creator;
    QDateTime creationDate;
    int width;
    int height;

    int playerSpawnX;
    int playerSpawnY;

    QList<Inert*> inerts;
    QList<Entity*> entities;
};

#endif // MAP_H
