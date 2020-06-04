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

Settings::Settings()
{
    keyJump = Qt::Key_Space;
    keyMoveLeft = Qt::Key_Q;
    keyMoveRight = Qt::Key_D;
    keyRun = Qt::Key_Shift;
    keyShootFireBall = Qt::Key_Shift;
    keyA = Qt::Key_A;
}

void Settings::readConfig()
{
    QString filename = "C:/Users/kanti/Desktop/MarioProjet/MarioQT/config/config.json";
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


    QString jump = jsonObject["jump"].toString();

    keyMoveLeft = QKeySequence::fromString("B")[0];


    qDebug() << "HERE";

}
