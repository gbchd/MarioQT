#include "cameravisitor.h"

CameraVisitor::CameraVisitor(){
    // On setup les différentes listes de zValue
    for(int i=0; i <= maxZValue; i++){
        objects.append(QList<ObjectModel*>());
    }
}


void CameraVisitor::setup(QPointF pos, int windowWidth, int levelWidth){
    setWindowWidth(windowWidth);
    setLevelWidth(levelWidth);
    setPosition(pos);
}

void CameraVisitor::visit(ObjectModel *o){
    int zValue = o->getZValue();
    if(zValue < 0){zValue=0;}
    if(zValue > maxZValue){zValue = maxZValue;}
    objects[zValue].append(o);
}

void CameraVisitor::setPosition(QPointF pos){
    if(pos.x() < halfWindowWidth){
        position.setX(0);
    }
    else if(pos.x() > levelWidth - halfWindowWidth){
        position.setX(levelWidth - halfWindowWidth);
    }
    else {
        position.setX(pos.x() - halfWindowWidth);
    }
}
