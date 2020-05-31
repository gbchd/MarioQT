#include "gamecontroller.h"
#include "mainwindow.h"
#include "QDebug"
#include <QtMath>


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

        Box * box = dynamic_cast<Box*>(inert);
        if(box){
            boxHandler(box);
        }

        inert->animate();

        if(inert->isDeletable()){
            removeInert(inert);
        }
    }

    for(Entity * entity : entities){
        entity->advance();

        handleCollision(entity);

        entity->animate();

        if(entity->isDeletable() || entity->getPosition().y() >= gameview->getlevelSize().height()){
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

void GameController::handleCollision(Entity *entity){
    // We create a list of colliding objects and we add all the objects which we are colliding with.
    // We sort this list by the distance between entity and the object colliding.
    QList<ObjectModel*> collidingObjects;
    for(ObjectModel * o : objects){
        if(dynamic_cast<Entity *>(o) != entity && entity->isColliding(o)){
            addObjectToCollidingList(collidingObjects, entity, o);
            //entity->collisionHandler(o);
        }
    }

    // We iterate through the list and we solve the collision one by one.
    // We check between each object if the collision has already been solved or not.
    for(ObjectModel* o : collidingObjects){
        if(entity->isColliding(o)){
            entity->collisionHandler(o);
        }
    }
}

void GameController::addObjectToCollidingList(QList<ObjectModel *> &collidingObjects, Entity* entity, ObjectModel *o){
    if(collidingObjects.size() == 0){
        collidingObjects.append(o);
    }
    else{
        bool added = false;
        for(int i = 0; i < collidingObjects.size(); i++){
            QPointF entityCenter = entity->getHitbox().center();
            QPointF objectInListCenter = collidingObjects.at(i)->getHitbox().center();
            QPointF newObjectCenter = o->getHitbox().center();
            float distObjectInList = qPow(entityCenter.x() - objectInListCenter.x(),2) + qPow(entityCenter.y() - objectInListCenter.y(),2);
            float distNewObject = qPow(entityCenter.x() - newObjectCenter.x(),2) + qPow(entityCenter.y() - newObjectCenter.y(),2);
            if(distNewObject < distObjectInList){
                collidingObjects.insert(i,o);
                added = true;
                break;
            }
        }
        if(!added){
            collidingObjects.append(o);
        }
    }
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

void GameController::boxHandler(Box *box){
    BoxContent boxContent = box->getBoxContent();
    if(box->doesBoxNeedToSpawnItem()){
        switch (boxContent) {
            case MUSHROOMBOX:{
                addEntity(box->spawnMushroom());
                break;
            }
            case FLOWERBOX:{
                addEntity(box->spawnFlower());
                break;
            }
            case COINBOX:{
                 addEntity(box->spawnCoin());
                 break;
            }
            case STARBOX:{
                addEntity(box->spawnStar());
                break;
            }
            case EMPTYBOX:
            default:
                break;
        }
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

    if(e->key() == Qt::Key_Shift){
        //entities.append(mario->shootFireBall());
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
    if(i != nullptr){
        objects.removeOne(i);
        inerts.removeOne(i);
        delete i;
        i = nullptr;
    }
}
void GameController::removeEntity(Entity *e){
    if(e != nullptr){
        objects.removeOne(e);
        entities.removeOne(e);
        delete e;
        e = nullptr;
    }
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
    //On crée lQes maps dans le controlleur
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
