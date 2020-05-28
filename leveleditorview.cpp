#include "leveleditorview.h"

#include "leveleditorengine.h"

LevelEditorView::LevelEditorView()
{
    showLevelGrid = false;
    windowSize = QSize(1280,720);
    levelSize = QSize(2*windowSize.width(),windowSize.height());
    resize(windowSize);
    backgroundColor = QColor(100,175,255);
    palette.setColor(QPalette::Background, backgroundColor);
    setAutoFillBackground(true);
    setPalette(palette);
}

void LevelEditorView::paintEvent(QPaintEvent *event)
{
    GraphicVisitor graphicVisitor(this); // possède un QPainter
    levelEditorEngine->update(graphicVisitor);
    graphicVisitor.paint();

    if(showLevelGrid){
        LevelGridVisitor levelGridVisitor(this);
        levelEditorEngine->update(levelGridVisitor);
        levelGridVisitor.paint();
    }

    cameraPosition = graphicVisitor.getPosition();
}
