#include "graphicvisitor.h"

#include "gameview.h"
#include "mario.h"
#include <QDebug>


GraphicVisitor::GraphicVisitor(GameView * gv):painter(gv)
{
    position = gv->getCameraPosition();
    halfWindowWidth = gv->getWindowSize().width()/2;
    levelWidth = gv->getlevelSize().width();
}


void GraphicVisitor::paint(){
    for(int zValue = 0; zValue < objects.length(); zValue++){
        for(ObjectModel * o : objects[zValue]){
            painter.setOpacity(o->getOpacity());
            painter.drawPixmap(o->getPosition() - position, o->getCurrentTexture());
        }
    }
}



