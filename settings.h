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

    QString jump;
    QString run;
    QString moveRight;
    QString moveLeft;
    QString shootFireBall;


public:
    Settings();
    void readConfig(QString filename);
    void changeConfig(QString jump, QString run, QString moveRight, QString moveLeft, QString shootFireBall);

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

    QString getJump() const;
    QString getRun() const;
    QString getMoveRight() const;
    QString getMoveLeft() const;
    QString getShootFireBall() const;
};

#endif // SETTINGS_H
