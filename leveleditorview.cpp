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
        QPainter painter(this);
        painter.setPen(QColor(0,0,0));

        int block_size = 32;

        for(int i=0; i < windowSize.width(); i += block_size){
            painter.drawLine(i,0,i,windowSize.height());
        }

        for(int i=0; i < windowSize.height (); i += block_size){
            painter.drawLine(0,i,windowSize.width(),i);
        }
    }

    cameraPosition = graphicVisitor.getPosition();
}
