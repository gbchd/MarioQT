#ifndef LEVELEDITORVIEW_H
#define LEVELEDITORVIEW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include "graphicvisitor.h"
#include "levelgridvisitor.h"

class LevelEditorEngine;

class LevelEditorView : public QWidget
{
private:
    LevelEditorEngine * levelEditorEngine;

    QColor backgroundColor;
    QPalette palette; //Used to paint the background

    int cameraPosition;
    QSize levelSize;
    QSize windowSize;

    bool showLevelGrid;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    LevelEditorView();

    void setBackground(QColor color){ backgroundColor = color; }
    void paintEvent(QPaintEvent *event) override;
    void setLevelEditorEngine(LevelEditorEngine * lee){ levelEditorEngine = lee; }

    void setShowLevelGrid(bool b){ showLevelGrid = b; }

    int getCameraPosition(){ return cameraPosition; }
    void setCameraPosition(int position){ cameraPosition = position; }
    QSize getWindowSize(){return windowSize;}
    QSize getlevelSize(){return levelSize;}
};

#endif // LEVELEDITORVIEW_H
