#include "hitboxgraphicvisitor.h"

#include "gameview.h"
#include "mario.h"


HitboxGraphicVisitor::HitboxGraphicVisitor(GameView * gv):painter(gv)
{
    halfWindowWidth = gv->getWindowSize().width()/2;
    levelWidth = gv->getlevelSize().width();
    position = gv->getCameraPosition();
}

void HitboxGraphicVisitor::paint(){
  for(int zValue = 0; zValue < objects.length(); zValue++){
        for(ObjectModel * o : objects[zValue]){
            QRectF hitbox = o->getHitbox();
            painter.setPen(QColor(255,0,0));
            hitbox.moveTo(hitbox.x() - position.x(), hitbox.y());
            painter.drawRect(hitbox);

            QRectF pos = QRectF(o->getPosition()-QPointF(3,3),o->getPosition()+QPointF(3,3));
            pos.moveTo(pos.x() - position.x(), pos.y());
            painter.fillRect(pos,QColor(0,255,0));
        }
    }
}
