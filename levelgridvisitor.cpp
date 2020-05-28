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

}
