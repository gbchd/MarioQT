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

    int position;
    int halfWindowWidth;
    int levelWidth;

public:
    CameraVisitor();

    void visit(ObjectModel *o) override;
    virtual void paint()=0;

    void setup(int pos, int windowWidth, int levelWidth);
    int getPosition(){ return position; }
    void setPosition(int pos);
    void setWindowWidth(int windowWidth){ halfWindowWidth = windowWidth/2; }
    void setLevelWidth(int lvlWidth){ levelWidth = lvlWidth; }
};

#endif // CAMERAVISITOR_H
