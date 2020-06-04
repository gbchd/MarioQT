#include "gamecontroller.h"
#include "mainwindow.h"
#include "QDebug"
#include <QtMath>


GameController::GameController(){
    mario = nullptr;
    gameview = nullptr;
    tickrate = 1000/60;

    Score::init();
    Score::reset();
    currentMap = nullptr;
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
    if(levelTimer.elapsed() > levelMaxTime){
        reset();
    }
    if(mario && mario->isTransforming()){
        mario->animate();
        for(Inert * i : inerts){ i->animate(); }
        gameview->repaint();
        return;
    }

    for(int inertIt = 0; inertIt < inerts.size(); inertIt++){
        Inert * inert = inerts.at(inertIt);

        if(qAbs(gameview->getCameraPosition()-inert->getPosition().x()) < 1.25*gameview->getWindowSize().width()){
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

        }

        if(inert->isDeletable()){
            removeInert(inert);
            inertIt--;
        }
    }

    for(int entityIt = 0 ; entityIt <entities.size(); entityIt++ ){
        Entity * entity = entities.at(entityIt);

        if(qAbs(gameview->getCameraPosition()-entity->getPosition().x()) < 1.25*gameview->getWindowSize().width()){
            entity->advance();

            handleCollision(entity);

            entity->animate();
        }

        if(entity->isDeletable() || entity->getPosition().y() >= gameview->getlevelSize().height() || entity->getPosition().x()+entity->getHitbox().width() < 0|| entity->getPosition().x() >= gameview->getlevelSize().width()){
            if(dynamic_cast<Mario *>(entity)){
                removePlayer();
            }
            else{
                removeEntity(entity);
            }
            entityIt--;
        }
    }

    hud.setTimer(getTimeBeforeReset());
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
    if(brick != nullptr){
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
                if(mario->isBig()){
                    addEntity(box->spawnFlower());
                }
                else{
                    addEntity(box->spawnMushroom());
                }
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
    if(mario != nullptr && !mario->getIsInFlagpoleCinematic()){
        if(e->key() == settings->getKeyMoveLeft()){
            if(!keyQueue.contains(settings->getKeyMoveLeft())){
                keyQueue.append(settings->getKeyMoveLeft());
            }
            updateDirection();
            if(!mario->isDead()){mario->setMoving(true);}
        }

        if(e->key() == settings->getKeyMoveRight()){
            if(!keyQueue.contains(settings->getKeyMoveRight())){
                keyQueue.append(settings->getKeyMoveRight());
            }
            updateDirection();
            if(!mario->isDead()){mario->setMoving(true);}
        }

        if(e->key() == settings->getKeyJump()){
            mario->jump();
        }

        if(e->key() == settings->getKeyRun()){
            mario->setRunning(true);
        }

        if(e->key() == Qt::Key_C){
            mario->startTransforming();
        }

        if(e->key() == settings->getKeyShootFireBall()){
            if(mario->isOnFire()){
                FireBall * newFireBall = mario->shootFireBall();
                if(newFireBall){
                    addEntity(newFireBall);
                }
            }
        }
    }

    if(e->key() == Qt::Key_T){
        gameview->switchHitboxes();
    }

    if(e->key() == Qt::Key_R){
        reset();
    }


    QString letter = "A";
    if(e->key() == 65){

      qDebug() << QKeySequence::fromString(letter)[0] << endl;
    }

    if(e->key() == Qt::Key_Escape){
        mainWindow->displayPauseMenu();
    }
}

void GameController::keyReleaseEventHandler(QKeyEvent *e){
    if(mario != nullptr && !mario->getIsInFlagpoleCinematic()){
        if(e->key() == settings->getKeyMoveLeft()){
            keyQueue.removeOne(settings->getKeyMoveLeft());

            updateDirection();
        }

        if(e->key() == settings->getKeyMoveRight()){
            keyQueue.removeOne(settings->getKeyMoveRight());
            updateDirection();
        }

        if(e->key() == settings->getKeyRun()){
            mario->setRunning(false);
        }

        if(e->key() == settings->getKeyJump()){
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
        if(keyQueue.last() == settings->getKeyMoveLeft()){
            if(mario->getDirection() != LEFT){
               mario->setDirection(LEFT);
            }
        }
        if(keyQueue.last() == settings->getKeyMoveRight()){
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
        objects.removeAll(e);
        entities.removeAll(e);
        delete e;
        e = nullptr;
    }
}

void GameController::clean(){
    qDebug() << "Before :" << "Objects :" << objects.size() << " Inerts :" << inerts.size() << "Entities :" << entities.size();

    removePlayer();
    for(int i=0; i<entities.size();){
        Entity * entity = entities.at(i);
        removeEntity(entity);
    }
    for(int i=0; i<inerts.size();){
        Inert * inert = inerts.at(i);
        removeInert(inert);
    }

    if(currentMap != nullptr){
        delete currentMap;
        currentMap = nullptr;
    }

    qDebug() << "After :" << "Objects :" << objects.size() << " Inerts :" << inerts.size() << "Entities :" << entities.size();
}

void GameController::generateMap(){
    //On crée les maps dans le controlleur
    Map * map = new Map(mapFilepath);

    gameview->setLevelSize(map->getWidth(), map->getHeight());
    hud.setMapName(map->getName());

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

    currentMap = map;
}



void GameController::start(){
    //We setup the game engine : A timer that calls advance every 10ms
    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));

    Score::reset();

    hud.init();

    qDebug() << "Tickrate" << tickrate;
    engine.setTimerType(Qt::PreciseTimer);
    engine.setInterval(tickrate); // possible de le passer en dynamique

    generateMap();
    engine.start();

    levelTimer.start();
}


void GameController::stop(){
    clean();
    Score::reset();
    engine.stop();
    QObject::disconnect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
    levelTimer.invalidate();
}

void GameController::reset(){ 
    generateMap();

    levelTimer.restart();
}
