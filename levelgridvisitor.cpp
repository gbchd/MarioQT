#include "levelgridvisitor.h"

#include "leveleditorview.h"

#include <qdebug.h>

LevelGridVisitor::LevelGridVisitor(LevelEditorView * lev):painter(lev)
{
    halfWindowWidth = lev->getWindowSize().width()/2;
    levelWidth = lev->getlevelSize().width();
    levelHeight = lev->getlevelSize().height();
    position = lev->getCameraPosition();
}

void LevelGridVisitor::paint()
{
    painter.setPen(QColor(0,0,0));

    for(int i=0; i < levelWidth; i += block_size){
        painter.drawLine(i,0,i,levelHeight);
    }

    for(int i=0; i < levelHeight; i += block_size){
        painter.drawLine(0,i,levelWidth,i);
    }
}
