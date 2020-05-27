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


class Map
{
public:
    Map();
    Map(QString filename);

    QString getCreator(){return creator;}
    QDateTime getCreationDate(){return creationDate;}
    int getWidth();
    int getHeight();

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
