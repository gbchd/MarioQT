#include "gameview.h"
#include <QDebug>
#include <QFontDatabase>
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

    coinTexture = QPixmap(":/resources/graphics/items/coin-0.png");


    //Init font for hud
    //Load mario font
    int id = QFontDatabase::addApplicationFont(":/resources/fonts/mario_font.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(fontFamily);
    font.setPixelSize(fontSize);
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

    drawHUD();

    cameraPosition = graphicVisitor.getPosition();
}


//There is 4 rect composing the hud
void GameView::drawHUD(){

    QPainter painter(this);

    int fontWidth = fontSize/2;

    //Set painter color and font
    painter.setFont(font);
    painter.setPen(Qt::white);

    //Calculate all text zones.
    //Separated like this (number : space of unit):
    //  1    4     1    4     1    4     1     4    1    = 21
    //blank ZONE blank ZONE blank ZONE blank ZONE blank  = windowWidth

    int unit = windowSize.width()/21;
    int positionY = unit/2;

    int width = unit*4;
    int height = unit*2;

    QRectF pointsZone(unit,positionY,width,height);
    QRectF coinsZone(6*unit, positionY, width, height);
    QRectF mapZone(11*unit, positionY, width, height);
    QRectF timerZone(16*unit, positionY, width, height);           //not implemented yet


    //POINTS
    QString scoreStringWithLeadingZeros = QString("%1").arg(Score::getScore(), 6, 10, QChar('0'));
    QString pointsText = "MARIO\n";
    pointsText.append(scoreStringWithLeadingZeros);
    painter.drawText(pointsZone, pointsText);

    //COINS
    QString coinsStringWithLeadingZeros = QString("%1").arg(Score::getCoins(), 2, 10, QChar('0'));
    QString coinsText = "\n  x"; //we leave spaces to be able to print the pixmap of the coin.
    coinsText.append(coinsStringWithLeadingZeros);
    painter.drawText(coinsZone, coinsText);

    //Fixme : this is very bad : need to calculate the position not get it by approximation.
    painter.drawPixmap(6*unit + fontSize*1.3, positionY + fontSize + 5, coinTexture.scaled(fontSize/2,fontSize));

    // MAP
    QString mapText = gameController->getMapName();
    painter.drawText(mapZone, mapText);

    // TIMER
    QString timerValue = QString("%1").arg(gameController->getTimeBeforeReset());
    QString timerText = "TIMER\n";
    timerText.append(timerValue);
    painter.drawText(timerZone, timerText);

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

void GameView::wheelEvent(QWheelEvent * e)
{

}
