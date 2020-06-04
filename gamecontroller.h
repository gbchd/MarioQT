#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QTimer>
#include <QtMath>

#include "gameview.h"
#include "objectmodel.h"
#include "mario.h"
#include "inert.h"
#include "map.h"
#include "bulletbill.h"
#include "billblaster.h"
#include "cameravisitor.h"
#include "brickdebris.h"
#include "coin.h"
#include "collectableitem.h"
#include "fireball.h"
#include "score.h"

#include "settings.h"

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

    QElapsedTimer levelTimer;
    int levelMaxTime = 400*1000;

    HUD hud;

    Map * currentMap;

    // Possède des objets de type Inert et Entity
    Mario * mario;
    QList<Inert*> inerts;
    QList<Entity*> entities;

    QList<ObjectModel *> objects;

    void handleCollision(Entity * entity);
    void addObjectToCollidingList(QList<ObjectModel*>& collidingObjects, Entity* entity, ObjectModel*o);

    int BLOCSIZE = 32; //taille d'un bloc devrait le passer en constante globale

    // Key queue for smooth transitions for pro players
    QList<Qt::Key> keyQueue;
    void updateDirection();

    QString mapFilepath;
    void generateMap();

    void billblasterHandler(BillBlaster * billblaster);
    void brickHandler(Brick * brick);
    void boxHandler(Box * box);

    MainWindow * mainWindow;
    Settings * settings;

public:
    GameController();
    GameController(GameView * gv);
    void setGameView(GameView * gv){gameview = gv;}
    void setMapFilepath(QString filepath){mapFilepath = filepath;}
    //Set tickrate by giving the number of fps you want
    void setTickrate(float fps){tickrate = 1000/fps;}

    QPixmap& getHUD(){return hud.getScene();}
    void update(CameraVisitor & visitor);

    void keyPressEventHandler(QKeyEvent * e);
    void keyReleaseEventHandler(QKeyEvent * e);

    int getTimeBeforeReset(){return (levelMaxTime - levelTimer.elapsed())/1000;}

    void setPlayer(Mario * m);
    void addInert(Inert * i);
    void addEntity(Entity * e);

    QString getMapName(){return currentMap->getName();}

    void clean(); // Used to remove all objects
    void removePlayer();
    void removeInert(Inert * i);
    void removeEntity(Entity * e);

    void setMainWindowPointer(MainWindow * mw){ mainWindow = mw; };
    void setSettingsPointer(Settings * settings){this->settings = settings;};

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
