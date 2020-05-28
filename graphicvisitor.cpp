#include "graphicvisitor.h"

#include <QDebug>

#include "leveleditorview.h"
#include "gameview.h"
#include "mario.h"

GraphicVisitor::GraphicVisitor(GameView * gv):painter(gv)
{
    position = gv->getCameraPosition();
    halfWindowWidth = gv->getWindowSize().width()/2;
    levelWidth = gv->getlevelSize().width();
}

GraphicVisitor::GraphicVisitor(LevelEditorView * lev):painter(lev)
{
    position = lev->getCameraPosition();
    halfWindowWidth = lev->getWindowSize().width()/2;
    levelWidth = lev->getlevelSize().width();
}

void GraphicVisitor::paint(){
    for(int zValue = 0; zValue < objects.length(); zValue++){
        for(ObjectModel * o : objects[zValue]){
            painter.setOpacity(o->getOpacity());
            painter.drawPixmap(o->getPosition().x() - position, o->getPosition().y(), o->getCurrentTexture());
        }
    }
}
