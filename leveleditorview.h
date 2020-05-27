#ifndef LEVELEDITORVIEW_H
#define LEVELEDITORVIEW_H

#include <QWidget>
#include <QPainter>

#include "graphicvisitor.h"

class LevelEditorEngine;

class LevelEditorView : public QWidget
{
private:
    LevelEditorEngine * levelEditorEngine;

    QColor backgroundColor;
    QPalette palette; //Used to paint the background

    QPointF cameraPosition;
    QSize levelSize;
    QSize windowSize;

public:
    LevelEditorView();

    void setBackground(QColor color){ backgroundColor = color; }
    void paintEvent(QPaintEvent *event) override;
    void setLevelEditorEngine(LevelEditorEngine * lee){ levelEditorEngine = lee; }

    QPointF getCameraPosition(){ return cameraPosition; }
    QSize getWindowSize(){return windowSize;}
    QSize getlevelSize(){return levelSize;}
};

#endif // LEVELEDITORVIEW_H
