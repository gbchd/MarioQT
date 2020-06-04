#ifndef HUD_H
#define HUD_H

#include <QPixmap>
#include <QPainter>
#include <QFontDatabase>
#include "score.h"


class GameController;

class HUD
{
private:
    //Fixme : do it without having a pointer on the gameController
    GameController * gameController;

    bool needToUpdate=true;

    QPixmap scene;

    QPixmap scoreImage;
    QPixmap coinsImage;
    QPixmap mapImage;
    QPixmap timerImage;

    QPixmap coinTexture;
    QFont font;
    int fontSize = 24;
    int unit;

    int score;
    int coins;
    QString mapName;
    int timer;

    QString newMapName;
    int newTimer;

    void refresh();

    void paintScore();
    void paintCoins();
    void paintMapName();
    void paintTimer();

public:
    HUD();
    HUD(int width, int height);
    void init();
    void setGC(GameController * gc){gameController = gc;}
    void setMapName(QString name){newMapName = name;}
    void setTimer(int t){newTimer = t;}
    QPixmap& getScene();
};

#endif // HUD_H
