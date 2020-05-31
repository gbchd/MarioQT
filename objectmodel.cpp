#include "objectmodel.h"

ObjectModel::ObjectModel()
{
    collidable = true;
    walkable   = false;
    zValue = 2;
}

ObjectModel::~ObjectModel(){
    // delete les attributs alloués dynamiquement
}

void ObjectModel::moveTo(QPointF newPosition){
    QPointF distanceBetweenPosAndHitbox;
    distanceBetweenPosAndHitbox.setX(hitbox.x() - position.x());
    distanceBetweenPosAndHitbox.setY(hitbox.y() - position.y());

    position = newPosition;
    hitbox.moveTo(position+distanceBetweenPosAndHitbox);
}

void ObjectModel::moveTo(float x, float y){
    hitbox.moveTo(x + hitbox.x() - position.x(), y + hitbox.y() - position.y());
    position.setX(x);
    position.setY(y);
}

void ObjectModel::doSimpleAnimation(QList<QPixmap> &textures, QElapsedTimer & timer, int delay, int & counter){
    if(timer.elapsed() > delay){
        counter ++;
        if(counter > textures.length()-1){
            counter = 0;
        }
        setCurrentTexture(textures.at(counter));
        timer.restart();
    }
}


QPixmap ObjectModel::loadTextureTransparent(const std::string & file, QColor mask_color)
{
    QPixmap pixmap(file.c_str());
    pixmap.setMask(pixmap.createMaskFromColor(mask_color));
    return pixmap;
}

QPixmap ObjectModel::loadTexture(const std::string file, QColor mask_color)
{
    if(strends(file, ".bmp"))
        return loadTextureTransparent(file, mask_color);
    else
        return QPixmap(file.c_str());
}

bool ObjectModel::strends(std::string const &str, std::string const &end)
{
    if (str.length() >= end.length())
        return (0 == str.compare (str.length() - end.length(), end.length(), end));
    else
        return false;
}

