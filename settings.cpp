#include "settings.h"

int Settings::getKeyJump() const
{
    return keyJump;
}

void Settings::setKeyJump(int value)
{
    keyJump = value;
}

int Settings::getKeyMoveRight() const
{
    return keyMoveRight;
}

void Settings::setKeyMoveRight(int value)
{
    keyMoveRight = value;
}

int Settings::getKeyMoveLeft() const
{
    return keyMoveLeft;
}

void Settings::setKeyMoveLeft(int value)
{
    keyMoveLeft = value;
}

int Settings::getKeyRun() const
{
    return keyRun;
}

void Settings::setKeyRun(int value)
{
    keyRun = value;
}

int Settings::getKeyShootFireBall() const
{
    return keyShootFireBall;
}

void Settings::setKeyShootFireBall(int value)
{
    keyShootFireBall = value;
}

int Settings::getKeyA() const
{
    return keyA;
}

void Settings::setKeyA(int value)
{
    keyA = value;
}

QString Settings::getJump() const
{
    return jump;
}

QString Settings::getRun() const
{
    return run;
}

QString Settings::getMoveRight() const
{
    return moveRight;
}

QString Settings::getMoveLeft() const
{
    return moveLeft;
}

QString Settings::getShootFireBall() const
{
    return shootFireBall;
}

Settings::Settings()
{
    keyJump = Qt::Key_Space;
    keyMoveLeft = Qt::Key_Q;
    keyMoveRight = Qt::Key_D;
    keyRun = Qt::Key_Shift;
    keyShootFireBall = Qt::Key_Shift;
    keyA = Qt::Key_A;
}

void Settings::readConfig(QString filename)
{
    QFile file_obj(filename);
    if(!file_obj.exists()){
        qDebug()<<"File does not exist"<<filename;
        exit(1);
    }
    if(!file_obj.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open "<<filename;
        exit(1);
    }

    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    QJsonDocument map = QJsonDocument::fromJson(json_bytes);
    QJsonObject jsonObject = map.object();

    jump = jsonObject["jump"].toString();
    run = jsonObject["run"].toString();
    moveRight = jsonObject["move-right"].toString();
    moveLeft = jsonObject["move-left"].toString();
    shootFireBall = jsonObject["shoot-fire-ball"].toString();

    changeConfig(jump, run, moveRight, moveLeft, shootFireBall);
}

void Settings::changeConfig(QString jump, QString run, QString moveRight, QString moveLeft, QString shootFireBall)
{
    QKeySequence ksJump = QKeySequence::fromString(jump);
    keyJump = ksJump[0];

    QKeySequence ksMoveRight = QKeySequence::fromString(moveRight);
    keyMoveRight = ksMoveRight[0];

    QKeySequence ksMoveLeft = QKeySequence::fromString(moveLeft);
    keyMoveLeft = ksMoveLeft[0];

    if (0 == run.compare("Shift", Qt::CaseInsensitive)) {
        keyRun = Qt::Key_Shift;
    }
    else {
         QKeySequence ksRun = QKeySequence::fromString(run);
         keyRun = ksRun[0];
    }

    if (0 == shootFireBall.compare("Shift", Qt::CaseInsensitive)) {
        keyShootFireBall = Qt::Key_Shift;
    }
    else {
        QKeySequence ksShootFireBall = QKeySequence::fromString(shootFireBall);
        keyShootFireBall = ksShootFireBall[0];
    }
}
