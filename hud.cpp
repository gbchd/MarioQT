#include "hud.h"
#include "gamecontroller.h"

HUD::HUD():scene(1280,360){
    scene.fill(Qt::transparent);

    coinTexture = QPixmap(":/resources/graphics/items/coin-0.png");

    //Load mario font
    int id = QFontDatabase::addApplicationFont(":/resources/fonts/mario_font.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(fontFamily);
    font.setPixelSize(fontSize);
}

HUD::HUD(int width, int height):scene(width, height){
    scene.fill(Qt::transparent);

    coinTexture = QPixmap(":/resources/graphics/items/coin-0.png").scaled(32/2,32);

    //Load mario font
    int id = QFontDatabase::addApplicationFont(":/resources/fonts/mario_font.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(fontFamily);
    font.setPixelSize(fontSize);

}

void HUD::init(){
    unit = scene.width()/21;

    scoreImage = QPixmap(unit*4,unit*2);
    coinsImage = QPixmap(unit*4,unit*2);
    mapImage = QPixmap(unit*4,unit*2);
    timerImage = QPixmap(unit*4,unit*2);

    score = 0;
    coins = 0;
    mapName = "";
    timer = 400;

    paintScore();
    paintCoins();
    paintMapName();
    paintTimer();
}

QPixmap& HUD::getScene(){
    refresh();
    return scene;
}

void HUD::refresh(){
    if(Score::getScore() != score){
        score = Score::getScore();
        paintScore();
        needToUpdate=true;
    }
    if(Score::getCoins() != coins){
        coins = Score::getCoins();
        paintCoins();
        needToUpdate=true;
    }
    if(newMapName.compare(mapName)!=0){
        mapName = newMapName;
        paintMapName();
        needToUpdate=true;
    }
    if(newTimer != timer){
        timer = newTimer;
        paintTimer();
        needToUpdate=true;
    }


    //Calculate all text zones.
    //Separated like this (number : space of unit):
    //  1    4     1    4     1    4     1     4    1    = 21
    //blank ZONE blank ZONE blank ZONE blank ZONE blank  = windowWidth


    if(needToUpdate){
        scene.fill(Qt::transparent);

        QPainter painter(&scene);

        int positionY = unit/2;

        painter.drawPixmap(unit, positionY, scoreImage);
        painter.drawPixmap(6*unit, positionY, coinsImage);
        painter.drawPixmap(11*unit, positionY, mapImage);
        painter.drawPixmap(16*unit, positionY, timerImage);

        needToUpdate = false;

        painter.end();
    }
}

void HUD::paintScore(){
    scoreImage.fill(Qt::transparent);

    QPainter painterScore(&scoreImage);
    painterScore.setFont(font);
    painterScore.setPen(Qt::white);

    QString scoreStringWithLeadingZeros = QString("%1").arg(score, 6, 10, QChar('0'));
    QString pointsText = "MARIO\n";
    pointsText.append(scoreStringWithLeadingZeros);
    painterScore.drawText(0,0,scoreImage.width(),scoreImage.height(),0,pointsText);

    painterScore.end();
}

void HUD::paintCoins(){
    coinsImage.fill(Qt::transparent);

    QPainter painterCoins(&coinsImage);
    painterCoins.setFont(font);
    painterCoins.setPen(Qt::white);

    QString coinsStringWithLeadingZeros = QString("%1").arg(coins, 2, 10, QChar('0'));
    QString coinsText = "\n  x"; //we leave spaces to be able to print the pixmap of the coin.
    coinsText.append(coinsStringWithLeadingZeros);
    painterCoins.drawText(0,0,coinsImage.width(),coinsImage.height(),0, coinsText);
    //Fixme : this is very bad : need to calculate the position not get it by approximation.
    painterCoins.drawPixmap(fontSize*1.3, fontSize+5, coinTexture.scaled(fontSize/2,fontSize));

    painterCoins.end();
}

void HUD::paintMapName(){
    mapImage.fill(Qt::transparent);

    QPainter painterMap(&mapImage);
    painterMap.setFont(font);
    painterMap.setPen(Qt::white);
    QRectF zone(0,0,mapImage.width(),mapImage.height());
    painterMap.drawText(zone, mapName);

    painterMap.end();
}

void HUD::paintTimer(){
    timerImage.fill(Qt::transparent);

    QPainter painterTimer(&timerImage);
    painterTimer.setFont(font);
    painterTimer.setPen(Qt::white);

    QString timerValue = QString("%1").arg(timer);
    QString timerText = "TIMER\n";
    timerText.append(timerValue);
    painterTimer.drawText(0,0,timerImage.width(),timerImage.height(),0, timerText);

    painterTimer.end();
}

