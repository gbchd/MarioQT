#include "settings.h"



Qt::Key Settings::getKeyJump() const
{
    return keyJump;
}

Qt::Key Settings::getKeyMoveRight() const
{
    return keyMoveRight;
}

void Settings::setKeyMoveRight(const Qt::Key &value)
{
    keyMoveRight = value;
}

Qt::Key Settings::getKeyMoveLeft() const
{
    return keyMoveLeft;
}

void Settings::setKeyMoveLeft(const Qt::Key &value)
{
    keyMoveLeft = value;
}

void Settings::setKeyJump(const Qt::Key &value)
{
    keyJump = value;
}

Qt::Key Settings::getKeyRun() const
{
    return keyRun;
}

void Settings::setKeyRun(const Qt::Key &value)
{
    keyRun = value;
}

Qt::Key Settings::getKeyShootFireBall() const
{
    return keyShootFireBall;
}

void Settings::setKeyShootFireBall(const Qt::Key &value)
{
    keyShootFireBall = value;
}

Settings::Settings()
{
    keyJump = Qt::Key_Space;
    keyMoveLeft = Qt::Key_Q;
    keyMoveRight = Qt::Key_D;
    keyRun = Qt::Key_Shift;
    keyShootFireBall = Qt::Key_Shift;
}

void Settings::readConfig()
{
    QString filename = ":/config/config.json";
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

}
