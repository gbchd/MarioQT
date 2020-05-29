#include "leveleditorview.h"

#include "leveleditorengine.h"
#include <QDebug>

LevelEditorView::LevelEditorView()
{
    windowSize = QSize(1280,720);
    levelSize = QSize(10000, windowSize.height());
    cameraPosition = windowSize.width()/2;
    resize(windowSize);
    backgroundColor = QColor(100,175,255);
    palette.setColor(QPalette::Background, backgroundColor);
    setAutoFillBackground(true);
    setPalette(palette);
    showLevelGrid = false;
}

void LevelEditorView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        levelEditorEngine->setMouseState(LEFTCLICKPRESSED);
    }
    if (event->button() == Qt::RightButton) {
        levelEditorEngine->setMouseState(RIGHTCLICKPRESSED);
    }
}

void LevelEditorView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        levelEditorEngine->setMouseState(NOTPRESSED);
    }
}

void LevelEditorView::paintEvent(QPaintEvent *event)
{
    if(showLevelGrid){
        QPainter painter(this);
        painter.setPen(QColor(0,0,0));

        int block_size = 32;

        for(int i=block_size-(cameraPosition-windowSize.width()/2)%block_size; i < windowSize.width()*1.5; i += block_size){
            painter.drawLine(i, 0, i, windowSize.height());
        }

        for(int i=0; i < windowSize.height (); i += block_size){
            painter.drawLine(0, i, windowSize.width()*1.5, i);
        }
    }

    GraphicVisitor graphicVisitor(this); // possède un QPainter
    levelEditorEngine->update(graphicVisitor);
    graphicVisitor.paint();
}
