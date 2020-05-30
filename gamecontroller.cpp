#include "gamecontroller.h"
#include "mainwindow.h"
#include "QDebug"

GameController::GameController(){
    mario = nullptr;
    gameview = nullptr;
    tickrate = 1000/60;
}

//DEPRECATED
GameController::GameController(GameView * gv)
{
    mario = nullptr;
    gameview = gv;

    //We setup the game engine : A timer that calls advance every 10ms
    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));

    engine.setTimerType(Qt::PreciseTimer);
    engine.setInterval(tickrate); // possible de le passer en dynamique

    generateMap();
    engine.start();
}

void GameController::advance() {
    for(Inert * inert : inerts){
        BillBlaster * billblaster = dynamic_cast<BillBlaster*>(inert);
        if(billblaster){
            billblasterHandler(billblaster);
        }

        Brick * brick = dynamic_cast<Brick*>(inert);
        if(brick){
            brickHandler(brick);
        }

        inert->animate();

        if(inert->isDeletable()){
            removeInert(inert);
        }
    }

    for(Entity * entity : entities){
        entity->advance();
        for(ObjectModel * o : objects){
            if(dynamic_cast<Entity *>(o) != entity && entity->isColliding(o)){
                // Possibilité de faire une liste d'objets qui collide et la trier dans par ordre de proximité avec l'entité
                entity->collisionHandler(o);
            }
        }
        entity->animate();

        if(entity->isDeletable()){
            if(dynamic_cast<Mario *>(entity)){
                removePlayer();
            }
            else{
                removeEntity(entity);
            }
        }

    }

    gameview->repaint();
}


void GameController::billblasterHandler(BillBlaster *billblaster){

    // We check if mario is not near the billblaster shooter
    if(mario != nullptr){
        if(qAbs(mario->getPosition().x()-billblaster->getPosition().x()) <= 2*BLOCSIZE && qAbs(mario->getPosition().y()-billblaster->getPosition().y()) <= 2*BLOCSIZE){
            billblaster->setShooting(false);
            billblaster->restartShootTimer();
        }
        else{
            billblaster->setShooting(true);
        }
        BulletBill * bulletBill = billblaster->shoot(mario->getPosition());
        if(bulletBill){
            addEntity(bulletBill);
        }
    }
}


void GameController::brickHandler(Brick *brick){
    BrickState brickState = brick->getBrickState();
    if(brickState==BREAKBRICK){
        QList<BrickDebris*> brickDebris = brick->doBreak();
        for(BrickDebris* debris : brickDebris){
            addEntity(debris);
        }
    }
    else if(brickState==GIVECOIN){
        addEntity(brick->spawnCoin());
    }
}


void GameController::update(CameraVisitor & visitor){
    if(mario!=nullptr){
        visitor.setPosition(mario->getPosition().x());
    }
    for(ObjectModel * object : objects){
        object->accept(visitor);
    }
}

void GameController::keyPressEventHandler(QKeyEvent *e){
    if(mario != nullptr){
        if(e->key() == Qt::Key_Q){
            if(!keyQueue.contains(Qt::Key_Q)){
                keyQueue.append(Qt::Key_Q);
            }
            updateDirection();
            if(!mario->isDead()){mario->setMoving(true);}
        }

        if(e->key() == Qt::Key_D){
            if(!keyQueue.contains(Qt::Key_D)){
                keyQueue.append(Qt::Key_D);
            }
            updateDirection();
            if(!mario->isDead()){mario->setMoving(true);}
        }

        if(e->key() == Qt::Key_Space){
            mario->jump();
        }

        if(e->key() == Qt::Key_Shift){
            mario->setRunning(true);
        }

        if(e->key() == Qt::Key_C){
            mario->startTransforming();
        }
    }

    if(e->key() == Qt::Key_T){
        gameview->switchHitboxes();
    }

    if(e->key() == Qt::Key_R){
        reset();
    }

    if(e->key() == Qt::Key_Escape){
        mainWindow->displayPauseMenu();
    }
}

void GameController::keyReleaseEventHandler(QKeyEvent *e){
    if(mario != nullptr){
        if(e->key() == Qt::Key_Q){
            keyQueue.removeOne(Qt::Key_Q);
            updateDirection();
        }

        if(e->key() == Qt::Key_D){
            keyQueue.removeOne(Qt::Key_D);
            updateDirection();
        }

        if(e->key() == Qt::Key_Shift){
            mario->setRunning(false);
        }

        if(e->key() == Qt::Key_Space){
            mario->releaseJump();
        }
    }
}

void GameController::updateDirection(){
    if(mario){
        if(keyQueue.isEmpty()){
            mario->setMoving(false);
            return;
        }
        if(keyQueue.last() == Qt::Key_Q){
            if(mario->getDirection() != LEFT){
               mario->setDirection(LEFT);
            }
        }
        if(keyQueue.last() == Qt::Key_D){
            if(mario->getDirection() != RIGHT){
               mario->setDirection(RIGHT);
            }
        }
    }
}

// Gestion des objets dans le controller (peut être le role du modèle?)
void GameController::setPlayer(Mario * m){
    if(mario != nullptr){
        removePlayer();
    }
    mario = m;
    entities.append(mario);
    objects.append(mario);
}
void GameController::addInert(Inert * i){
    inerts.append(i);
    objects.append(i);
}
void GameController::addEntity(Entity * e){
    entities.append(e);
    objects.append(e);
}

void GameController::removePlayer(){
    if(mario != nullptr){
        objects.removeOne(mario);
        entities.removeOne(mario);
        delete mario;
        mario = nullptr;
    }
}
void GameController::removeInert(Inert *i){
    objects.removeOne(i);
    inerts.removeOne(i);
    delete i;
}
void GameController::removeEntity(Entity *e){
    objects.removeOne(e);
    entities.removeOne(e);
    delete e;
}

void GameController::clean(){
    qDebug() << "Before :" << "Objects :" << objects.size() << " Inerts :" << inerts.size() << "Entities :" << entities.size();
    removePlayer();
    for(Entity * entity : entities){
        removeEntity(entity);
    }
    for(Inert * inert : inerts){
        removeInert(inert);
    }
    qDebug() << "After :" << "Objects :" << objects.size() << " Inerts :" << inerts.size() << "Entities :" << entities.size();
}

void GameController::generateMap(){
    //On crée les maps dans le controlleur
    Map * map = new Map(mapFilepath);
    gameview->setLevelSize(map->getWidth(), map->getHeight());
    qDebug() << map->getCreator() << map->getCreationDate();

    Mario * mario = new Mario();
    mario->moveTo(map->getPlayerSpawnX(), map->getPlayerSpawnY());

    // On ajoute les objets au controlleur
    clean();

    setPlayer(mario);
    QList<Inert *> mapInerts = map->getInerts();
    for(Inert * inert : mapInerts){
        addInert(inert);
    }
    QList<Entity *> mapEntities = map->getEntities();
    for(Entity * entity : mapEntities){
        addEntity(entity);
    }
}



void GameController::start(){
    //We setup the game engine : A timer that calls advance every 10ms
    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));

    qDebug() << "Tickrate" << tickrate;
    engine.setTimerType(Qt::PreciseTimer);
    engine.setInterval(tickrate); // possible de le passer en dynamique

    generateMap();
    engine.start();
}


void GameController::stop(){
    clean();
    engine.stop();
    QObject::disconnect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
}

void GameController::reset(){ 
    generateMap();
}
