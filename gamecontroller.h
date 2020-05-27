#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QTimer>

#include "gameview.h"
#include "objectmodel.h"
#include "mario.h"
#include "inert.h"
#include "map.h"
#include "cameravisitor.h"

class MainWindow;

class GameController : public QObject
{
    Q_OBJECT

private:
    //Timer for the tickrate of the game
    QTimer engine;
    float tickrate;

    //The view controlled by this controller
    GameView * gameview;

    // Possède des objets de type Inert et Entity
    Mario * mario;
    QList<Inert*> inerts;
    QList<Entity*> entities;

    QList<ObjectModel *> objects;


    // Key queue for smooth transitions for pro players
    QList<Qt::Key> keyQueue;
    void updateDirection();

    QString mapFilepath;
    void generateMap();

    //Testing purpose
    void setUpTest();

    MainWindow * mainWindow;



public:
    GameController();
    GameController(GameView * gv);
    void setGameView(GameView * gv){gameview = gv;}
    void setMapFilepath(QString filepath){mapFilepath = filepath;}
    //Set tickrate by giving the number of fps you want
    void setTickrate(float fps){tickrate = 1000/fps;}

    void update(CameraVisitor & visitor);

    void keyPressEventHandler(QKeyEvent * e);
    void keyReleaseEventHandler(QKeyEvent * e);

    void setPlayer(Mario * m);
    void addInert(Inert * i);
    void addEntity(Entity * e);


    void clean(); // Used to remove all objects
    void removePlayer();
    void removeInert(Inert * i);
    void removeEntity(Entity * e);

    void setMainWindowPointer(MainWindow * mw){ mainWindow = mw; };

public slots:
    // This slot is called by the timer to advance the game to the next frame
    void advance();

    // Pause or resume game
    void togglePause(){}

    // Reset game
    void reset();

    // Start new game
    void start();

    void stop();

    // Game over
    void gameover(){}
};

#endif // GAMECONTROLLER_H
