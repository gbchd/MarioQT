#include "gameview.h"
#include <QDebug>
#include "gamecontroller.h"

GameView::GameView()
{
    showHitboxes = false;
    windowSize = QSize(1280,720);
    levelSize = QSize(2*windowSize.width(),windowSize.height());
    resize(windowSize);
    backgroundColor = QColor(100,175,255);
    palette.setColor(QPalette::Background, backgroundColor);
    setAutoFillBackground(true);
    setPalette(palette);
}



void GameView::paintEvent(QPaintEvent *event){ 
    GraphicVisitor graphicVisitor(this); // possède un QPainter
    gameController->update(graphicVisitor);
    graphicVisitor.paint();
    if(showHitboxes){
        HitboxGraphicVisitor hitboxGraphicVisitor(this);
        gameController->update(hitboxGraphicVisitor);
        hitboxGraphicVisitor.paint();
    }

    cameraPosition = graphicVisitor.getPosition();
}

// On déplace les controles dans le controller (logique)
void GameView::keyPressEvent(QKeyEvent * e)
{
    gameController->keyPressEventHandler(e);
}


void GameView::keyReleaseEvent(QKeyEvent * e)
{
    gameController->keyReleaseEventHandler(e);
}


