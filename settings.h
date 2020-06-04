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
#include <QKeySequence>


class Settings
{
private:
    int keyJump;
    int keyMoveRight;
    int keyMoveLeft;
    int keyRun;
    int keyShootFireBall;
    int keyA;


public:
    Settings();
    void readConfig();

    int getKeyJump() const;
    void setKeyJump(int value);
    int getKeyMoveRight() const;
    void setKeyMoveRight(int value);
    int getKeyMoveLeft() const;
    void setKeyMoveLeft(int value);
    int getKeyRun() const;
    void setKeyRun(int value);
    int getKeyShootFireBall() const;
    void setKeyShootFireBall(int value);
    int getKeyA() const;
    void setKeyA(int value);
};

#endif // SETTINGS_H
