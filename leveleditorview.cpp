#include "leveleditorview.h"

#include "leveleditorengine.h"

LevelEditorView::LevelEditorView()
{
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
    cameraPosition = graphicVisitor.getPosition();
}
