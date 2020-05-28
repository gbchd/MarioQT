#ifndef LEVELGRIDVISITOR_H
#define LEVELGRIDVISITOR_H

#include <QPainter>

#include "cameravisitor.h"

class LevelEditorView;

class LevelGridVisitor : public CameraVisitor
{
private :
    QPainter painter;
    int block_size = 32;
    int levelHeight;

public:
    LevelGridVisitor(LevelEditorView * lev);
    void paint() override;
};

#endif // LEVELGRIDVISITOR_H
