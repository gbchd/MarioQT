#include "cameravisitor.h"

CameraVisitor::CameraVisitor(){
    // On setup les différentes listes de zValue
    for(int i=0; i <= maxZValue; i++){
        objects.append(QList<ObjectModel*>());
    }
}


void CameraVisitor::setup(int pos, int windowWidth, int levelWidth){
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

void CameraVisitor::setPosition(int pos){
    if(pos < halfWindowWidth){
        position = 0;
    }
    else if(pos > levelWidth - halfWindowWidth){
        position = levelWidth - halfWindowWidth;
    }
    else {
        position = pos - halfWindowWidth;
    }
}
