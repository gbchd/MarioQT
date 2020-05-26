#include "gamecontroller.h"
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

    for(Entity * entity : entities){
        Mario * mario = dynamic_cast<Mario*>(entity);
        if(mario && mario->isDeletable()){
            removePlayer();
        }
        else if(entity->isDeletable()){
            removeEntity(entity);
        }
        else{
            entity->advance();
            for(ObjectModel * o : objects){
                if(dynamic_cast<Entity *>(o) != entity && entity->isColliding(o)){
                    entity->collisionHandler(o);
                }
            }
            entity->animate();
        }
    }
    gameview->repaint();
}

void GameController::update(CameraVisitor & visitor){
    for(ObjectModel * object : objects){
        object->accept(visitor);
    }
}

void GameController::keyPressEventHandler(QKeyEvent *e){
    // A faire
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
    }

    if(e->key() == Qt::Key_T){
        gameview->switchHitboxes();
    }
    if(e->key() == Qt::Key_R){
        reset();
    }
    if(e->key() == Qt::Key_C){
        mario->startTransforming();
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



// Here to test will be deleted later
void GameController::setUpTest(){

    //Create the mario player

    Mario * m = new Mario();
    m->moveTo(100,100);
    qDebug() << "Position :" << m->getPosition();
    qDebug() << "Hitbox :" << m->getHitbox();
    setPlayer(m);


    //Create some inerts

    Inert * i1 = new Inert();
    Inert * i2 = new Inert();

    i1->setCurrentTexture(ObjectModel::loadTexture(":/resources/graphics/blocs/block.png").scaled(32,32));
    i2->setCurrentTexture(ObjectModel::loadTexture(":/resources/graphics/blocs/block.png").scaled(32,32));

    i1->setHitboxWidth(32);
    i1->setHitboxHeight(32);
    i2->setHitboxWidth(32);
    i2->setHitboxHeight(32);

    i1->moveTo(QPointF(1000,100));
    i2->moveTo(QPointF(10,100));

    addInert(i1);
    addInert(i2);


    //Create some entities

}

void GameController::start(){
    //We setup the game engine : A timer that calls advance every 10ms
    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));

    engine.setTimerType(Qt::PreciseTimer);
    engine.setInterval(tickrate); // possible de le passer en dynamique

    generateMap();
    engine.start();
}

void GameController::reset(){
    generateMap();
}
