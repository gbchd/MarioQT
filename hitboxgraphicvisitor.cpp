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
            Entity * entity = dynamic_cast<Entity *>(o);
            if(entity){
                QRectF hitboxEntity = entity->getHitboxEntity();
                painter.setPen(QColor(0,255,0));
                hitboxEntity.moveTo(hitboxEntity.x() - position, hitboxEntity.y());
                painter.drawRect(hitboxEntity);
            }


            QRectF hitbox = o->getHitbox();
            painter.setPen(QColor(255,0,0));
            hitbox.moveTo(hitbox.x() - position, hitbox.y());
            painter.drawRect(hitbox);

            QRectF pos = QRectF(o->getPosition()-QPointF(3,3),o->getPosition()+QPointF(3,3));
            pos.moveTo(pos.x() - position, pos.y());
            painter.fillRect(pos,QColor(0,255,0));
        }
    }
}
