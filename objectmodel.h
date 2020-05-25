#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include <QtGlobal>
#include <QPixmap>
#include <QBitmap>
#include <QColor>
#include <string>
#include "visitor.h"

//class Visitor;

class ObjectModel
{
protected:
    bool walkable;
    bool collidable;

    QPointF position;
    QRectF hitbox;

    QPixmap currentTexture;
    float opacity = 1;
    int zValue = 0;

    int BLOCSIZE = 32; //taille d'un bloc devrait le passer en constante globale
public:
    ObjectModel();
    virtual ~ObjectModel();

    float getOpacity(){ return opacity; }
    void setZValue(int z){ zValue = z; }
    int getZValue(){ return zValue; }
    void accept(Visitor &v){ v.visit(this); }

    bool isWalkable(){ return walkable; }
    bool isCollidable(){ return collidable; }

    QPointF getPosition(){ return position; }
    void setPositionX(float x){ position.setX(x); } //Prefer the moveTo method instead of this one
    void setPositionY(float y){ position.setY(y); } //Prefer the moveTo method instead of this one

    QRectF getHitbox(){ return hitbox; }
    void setHitboxWidth(float w){ hitbox.setWidth(w); }
    void setHitboxHeight(float h){ hitbox.setHeight(h); }
    void setHitboxX(float x){ hitbox.setX(x); } //Prefer the moveTo method instead of this one
    void setHitboxY(float y){ hitbox.setY(y); } //Prefer the moveTo method instead of this one

    void moveTo(QPointF newPosition); // Move the position and the hitbox
    void moveTo(float x, float y);

    QPixmap getCurrentTexture(){ return currentTexture; }
    void setCurrentTexture(QPixmap texture){ currentTexture = texture; }

    // Used to compute the next texture
    virtual void animate() = 0;

    static bool strends (std::string const &str, std::string const &end);
    static QPixmap loadTextureTransparent(const std::string & file, QColor mask_color = Qt::magenta);
    static QPixmap loadTexture(const std::string file, QColor mask_color = Qt::magenta);
};

#endif // OBJECTMODEL_H
