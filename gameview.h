#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QKeyEvent>
#include <QList>
#include <QPainter>

#include "graphicvisitor.h"
#include "hitboxgraphicvisitor.h"
#include "objectmodel.h"

class GameController;

class GameView : public QWidget
{
private:
    GameController * gameController;
    QColor backgroundColor;

    QPointF cameraPosition;
    QSize levelSize;
    QSize windowSize;

    QPalette palette; //Used to paint the background
    bool showHitboxes;

    virtual void keyPressEvent(QKeyEvent * e) override;
    virtual void keyReleaseEvent(QKeyEvent * e) override;
    virtual void wheelEvent(QWheelEvent * e) override;
public:
    GameView();

    void setBackground(QColor color){backgroundColor=color;}
    void paintEvent(QPaintEvent *event) override;
    void setGameController(GameController * gc){gameController = gc;}

    QPointF getCameraPosition(){return cameraPosition;}

    QSize getWindowSize(){return windowSize;}
    void setWindowSize(QSize size){windowSize = size;}
    void setWindowSize(int x, int y){windowSize = QSize(x,y);}

    QSize getlevelSize(){return levelSize;}
    void setLevelSize(QSize size){levelSize = size;}
    void setLevelSize(int x, int y){levelSize = QSize(x,y);}

    void switchHitboxes(){showHitboxes = !showHitboxes;}
};

#endif // GAMEVIEW_H
