#ifndef SETTINGS_H
#define SETTINGS_H

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
#include "objectmodel.h"

class Settings
{
private:
    Qt::Key keyJump;
    Qt::Key keyMoveRight;
    Qt::Key keyMoveLeft;


public:
    Settings();
    void readConfig();

    //Getters and setters
    Qt::Key getKeyJump() const;
    void setKeyJump(const Qt::Key &value);
    Qt::Key getKeyMoveRight() const;
    void setKeyMoveRight(const Qt::Key &value);
    Qt::Key getKeyMoveLeft() const;
    void setKeyMoveLeft(const Qt::Key &value);

};

#endif // SETTINGS_H
