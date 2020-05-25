#ifndef HITBOXGRAPHICVISITOR_H
#define HITBOXGRAPHICVISITOR_H

#include <QPixmap>
#include <QPointF>
#include <QPainter>

#include "cameravisitor.h"
#include "objectmodel.h"

class GameView;

class HitboxGraphicVisitor : public CameraVisitor
{
private :
    QPainter painter;

public:
    HitboxGraphicVisitor(GameView * gv);
    void paint() override;
};

#endif // HITBOXGRAPHICVISITOR_H
