#ifndef CAMERAVISITOR_H
#define CAMERAVISITOR_H

#include <QPointF>

#include "visitor.h"
#include "objectmodel.h"
#include "mario.h"

class CameraVisitor : public Visitor
{
protected:
    //Handle ZValue
    QList<QList<ObjectModel *>> objects;
    int maxZValue = 5;

    QPointF position;
    int halfWindowWidth;
    int levelWidth;

public:
    CameraVisitor();

    void visit(ObjectModel *o) override;
    virtual void paint()=0;

    void setup(QPointF pos, int windowWidth, int levelWidth);
    QPointF getPosition(){ return position; }
    void setPosition(QPointF pos);
    void setWindowWidth(int windowWidth){ halfWindowWidth = windowWidth/2; }
    void setLevelWidth(int lvlWidth){ levelWidth = lvlWidth; }
};

#endif // CAMERAVISITOR_H
