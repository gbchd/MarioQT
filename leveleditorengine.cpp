#include "leveleditorengine.h"
#include "mainwindow.h"

LevelEditorEngine::LevelEditorEngine()
{
    mouseState = NOTPRESSED;
    selectedButton = NOBUTTON;
    objectToPaintOnMouse = nullptr;
    fakeMario = nullptr;
    levelEditorView = nullptr;
    levelEditorWidget = nullptr;
    castle = nullptr;
    flagpole = nullptr;
    tickrate = 1000/240;
}

void LevelEditorEngine::exportMapToJSon()
{
    if(fakeMario==nullptr){
        QMessageBox msgBox;
        msgBox.setText("You need to place mario to save a level.");
        msgBox.exec();
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(levelEditorWidget, "Sélectionner fichier JSON", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), "Fichiers JSON (*.json)");
    QFile myFile(filePath);

    if (myFile.open(QFile::ReadWrite)){

        QTextStream stream(&myFile);

        stream << "{\"name\":\""<<QFileInfo(myFile.fileName()).completeBaseName()<<"\","
                    "\"creator\":\"Map Editor\","
                    "\"date\":\""<<QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")<<"\","
                    "\"size\":{\"width\":400, \"height\":30},"
                    "\"player\":{\"x\":"<<fakeMario->getPosition().x()/32<<",\"y\":"<<fakeMario->getPosition().y()/32<<"},"
                    "\"inerts\":{";

        if(flagpole != nullptr){
            stream<<"\"block-1\":{\"type\":\"flagpole\",\"x\":"<<flagpole->getPosition().x()/32<<",\"y\":"<<flagpole->getPosition().y()/32<<",\"width\":1,\"height\":1}";
            if(inerts.length()>0){ stream<<","; }
        }

        for(int indice=0; indice<inerts.length(); indice++){
            if(indice>0){ stream<<","; }
            stream<<"\"block"<<indice<<"\":{\"type\":\""<<getTypeFromInert(inerts[indice])<<"\",";
            if(getTypeFromInert(inerts[indice]).compare("brick")==0){
                stream<<"\"isCoinBrick\":"<<dynamic_cast<Brick *>(inerts[indice])->getBrickState()<<",";
            }
            else if(getTypeFromInert(inerts[indice]).compare("box")==0){
                stream<<"\"content\":"<<dynamic_cast<Box *>(inerts[indice])->getBoxContent()<<",";
            }
            else if(getTypeFromInert(inerts[indice]).compare("scenery")==0){
                stream<<"\"sceneryType\":"<<dynamic_cast<Scenery *>(inerts[indice])->getObjectSceneryType()<<",";
            }
            else if(getTypeFromInert(inerts[indice]).compare("pipe")==0){
                stream<<"\"pipeType\":"<<dynamic_cast<Pipe *>(inerts[indice])->getTypePipe()<<",";
            }
            else if(getTypeFromInert(inerts[indice]).compare("trampoline")==0){
                stream<<"\"big\":"<<dynamic_cast<Trampoline *>(inerts[indice])->isTrampolineBig()<<",";
            }
            else if(getTypeFromInert(inerts[indice]).compare("movingplatform")==0){
                stream<<"\"big\":"<<dynamic_cast<MovingPlatform *>(inerts[indice])->isItABigMovingPlatform()<<",";
            }
            else if(getTypeFromInert(inerts[indice]).compare("lava")==0){
                stream<<"\"typeWave\":"<<dynamic_cast<Lava *>(inerts[indice])->isLavaTypeWave()<<",";
            }
            stream<<"\"x\":"<<inerts[indice]->getPosition().x()/32.0<<",\"y\":"<<inerts[indice]->getPosition().y()/32.0<<",\"width\":1,\"height\":1}";
        }
        stream<<"},\"entities\":{";
        for(int indice=0; indice<entities.length(); indice++){
            if(indice>0){ stream<<","; }
            stream<<"\"entity"<<indice<<"\":{\"type\":\""<<getTypeFromEntity(entities[indice])<<"\",\"x\":"<<entities[indice]->getPosition().x()<<",\"y\":"<<entities[indice]->getPosition().y()<<"}";
        }
        stream<<"}}";
        myFile.resize(myFile.pos());
        myFile.close();
    }
}

QString LevelEditorEngine::getTypeFromInert(Inert *inert)
{
    if(dynamic_cast<Wall *>(inert)){
        return "wall";
    }
    else if(dynamic_cast<Block *>(inert)){
        return "block";
    }
    else if(dynamic_cast<Brick *>(inert)){
        return "brick";
    }
    else if(dynamic_cast<Box *>(inert)){
        return "box";
    }
    else if(dynamic_cast<BillBlaster *>(inert)){
        return "billBlaster";
    }
    else if(dynamic_cast<Scenery *>(inert)){
        return "scenery";
    }
    else if(dynamic_cast<Pipe *>(inert)){
        return "pipe";
    }
    else if(dynamic_cast<Trampoline *>(inert)){
        return "trampoline";
    }
    else if(dynamic_cast<Flagpole *>(inert)){
        return "flagpole";
    }
    else if(dynamic_cast<MovingPlatform *>(inert)){
        return "movingplatform";
    }
    else if(dynamic_cast<Firebar *>(inert)){
        return "firebar";
    }
    else if(dynamic_cast<Lava *>(inert)){
        return "lava";
    }
    else{
        return "unknown";
    }
}

QString LevelEditorEngine::getTypeFromEntity(Entity * entity)
{
    if(dynamic_cast<Goomba *>(entity)){
        return "goomba";
    }
    if(dynamic_cast<Koopa *>(entity)){
        return "koopa";
    }
    if(dynamic_cast<Coin *>(entity)){
        return "coin";
    }
    if(dynamic_cast<Podoboo *>(entity)){
        return "podoboo";
    }
    if(dynamic_cast<PiranhaPlant *>(entity)){
        return "piranhaplant";
    }
    else{
        return "unknown";
    }
}

void LevelEditorEngine::update(CameraVisitor & visitor){
    int X = getColumnFromMousePosition()*block_size;
    int Y = getLineFromMousePosition()*block_size;

    visitor.setPosition(levelEditorView->getCameraPosition());

    if(mouseState == LEFTCLICKPRESSED){
        addObjectOnMousePosition();
    }

    if(mouseState == RIGHTCLICKPRESSED){
        deleteObjectAtPosition(X, Y);
    }

    for(ObjectModel * object : objects){
        object->accept(visitor);

        Firebar * firebar = dynamic_cast<Firebar *>(object);
        if(firebar){
            // TODO DRAW ELLIPSE
        }
    }

    if(fakeMario != nullptr){
        fakeMario->accept(visitor);
    }

    if(objectToPaintOnMouse != nullptr){
        objectToPaintOnMouse->moveTo(X, Y);
        objectToPaintOnMouse->accept(visitor);
    }

    if(selectedButton == FLAGPOLE){
        movingFlagpole->moveTo(X, Y);
        movingFlagpole->accept(visitor);
        movingCastle->moveTo(X+5*block_size, Y+7*block_size);
        movingCastle->accept(visitor);
    }
    else if(selectedButton == SMALLMOVINGPLATFORM || selectedButton == LARGEMOVINGPLATFORM){
        movingMovingPlatform->moveTo(X, Y+10*block_size);
        movingMovingPlatform->accept(visitor);
    }
    else if(selectedButton == PODOBOO){
        movingPodoboo->moveTo(X, Y+10*block_size);
        movingPodoboo->accept(visitor);
    }
    else if(selectedButton == PIRANHAPLANT){
        objectToPaintOnMouse->moveTo(X + (2*block_size - 1.3*16/24*block_size)/2, Y + block_size - 1.3*block_size);
    }
    else if(selectedButton == LAVASCENERY){
        objectToPaintOnMouse->moveTo(X, Y + (block_size - 0.34375*block_size));
    }

    if(castle != nullptr){
        castle->accept(visitor);
    }

    if(flagpole != nullptr){
        flagpole->accept(visitor);
    }
}

void LevelEditorEngine::changeCameraPosition(int value)
{
     if(levelEditorView != nullptr){
         levelEditorView->setCameraPosition(value);
     }
}

void LevelEditorEngine::addObjectOnMousePosition()
{
    int X = getColumnFromMousePosition()*block_size;
    int Y = getLineFromMousePosition()*block_size;

    if(dynamic_cast<Scenery *>(objectToPaintOnMouse)){
        deleteSceneryObjectAtPosition(X, Y);
    }
    else{
        deleteObjectAtPosition(X, Y);
    }

    switch(selectedButton){
        case BRICK: {
            Brick * newBrick = new Brick();
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case COINBRICK: {
            Brick * newBrick = new Brick();
            newBrick->setBrickState(BRICKWILLGIVECOINONNEXTHIT);
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case BLOCK: {
            Block * newBlock = new Block();
            newBlock->moveTo(X, Y);
            inerts.append(newBlock);
            objects.append(newBlock);
            break;
        }
        case WALL: {
            Wall * newWall = new Wall();
            newWall->moveTo(X, Y);
            inerts.append(newWall);
            objects.append(newWall);
            break;
        }
        case SECRETBOXFLOWER: {
            Box * newBox = new Box();
            newBox->setBoxContent(FLOWERBOX);
            newBox->moveTo(X, Y);
            inerts.append(newBox);
            objects.append(newBox);
            break;
        }
        case SECRETBOXMUSHROOM: {
            Box * newBox = new Box();
            newBox->setBoxContent(MUSHROOMBOX);
            newBox->moveTo(X, Y);
            inerts.append(newBox);
            objects.append(newBox);
            break;
        }
        case SECRETBOXSTAR: {
            Box * newBox = new Box();
            newBox->setBoxContent(STARBOX);
            newBox->moveTo(X, Y);
            inerts.append(newBox);
            objects.append(newBox);
            break;
        }
        case SECRETBOXCOIN: {
            Box * newBox = new Box();
            newBox->setBoxContent(COINBOX);
            newBox->moveTo(X, Y);
            inerts.append(newBox);
            objects.append(newBox);
            break;
        }
        case SMALLMOVINGPLATFORM: {
            MovingPlatform * newMP = new MovingPlatform(false);
            newMP->moveTo(X, Y);
            inerts.append(newMP);
            objects.append(newMP);
            break;
        }
        case LARGEMOVINGPLATFORM: {
            MovingPlatform * newMP = new MovingPlatform(true);
            newMP->moveTo(X, Y);
            inerts.append(newMP);
            objects.append(newMP);
            break;
        }
        case FIREBAR: {
            Firebar * newFB = new Firebar();
            newFB->moveTo(X, Y);
            inerts.append(newFB);
            objects.append(newFB);
            break;
        }
        case COINITEM: {
            Coin * coin = new Coin(false);
            coin->moveTo(X, Y);
            entities.append(coin);
            objects.append(coin);
            break;
        }
        case SMALLPIPE: {
            Pipe * pipe = new Pipe(SMALLPIPEOBJECT);
            pipe->moveTo(X, Y);
            inerts.append(pipe);
            objects.append(pipe);
            break;
        }
        case MEDPIPE: {
            Pipe * pipe = new Pipe(MEDPIPEOBJECT);
            pipe->moveTo(X, Y);
            inerts.append(pipe);
            objects.append(pipe);
            break;
        }
        case BIGPIPE: {
            Pipe * pipe = new Pipe(BIGPIPEOBJECT);
            pipe->moveTo(X, Y);
            inerts.append(pipe);
            objects.append(pipe);
            break;
        }
        case BULLETBLASTER: {
            BillBlaster * newBillBlaster = new BillBlaster();
            newBillBlaster->moveTo(X, Y);
            inerts.append(newBillBlaster);
            objects.append(newBillBlaster);
            break;
        }
        case MEDTRAMPOLINE: {
            Trampoline * newTrampoline = new Trampoline(false);
            newTrampoline->moveTo(QPointF(X, Y));
            inerts.append(newTrampoline);
            objects.append(newTrampoline);
            break;
        }
        case BIGTRAMPOLINE: {
            Trampoline * newTrampoline = new Trampoline(true);
            newTrampoline->moveTo(QPointF(X, Y));
            inerts.append(newTrampoline);
            objects.append(newTrampoline);
            break;
        }
        case FLAGPOLE: {
            if(!inerts.contains(flagpole)){
                flagpole = new Flagpole();
            }
            flagpole->moveTo(X, Y);

            if(!inerts.contains(castle)){
                castle = new Inert();
                castle->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/castle.png").scaled(block_size*4, block_size*4)));
            }
            castle->moveTo(X+5*block_size, Y+7*block_size);
            break;
        }
        case GOOMBA: {
            Goomba * goomba = new Goomba();
            goomba->moveTo(X, Y);
            entities.append(goomba);
            objects.append(goomba);
            break;
        }
        case TURTLE: {
            Koopa * koopa = new Koopa();
            koopa->moveTo(X, Y);
            entities.append(koopa);
            objects.append(koopa);
            break;
        }
        case FLYINGTURTLE: {
            //TODO
            break;
        }
        case PODOBOO: {
            Podoboo * podoboo = new Podoboo();
            podoboo->moveTo(X, Y);
            entities.append(podoboo);
            objects.append(podoboo);
            break;
        }
        case PIRANHAPLANT: {
            PiranhaPlant *pp = new PiranhaPlant();
            pp->moveTo(X + (2*block_size - 1.3*16/24*block_size)/2, Y + block_size - 1.3*block_size);
            entities.append(pp);
            objects.append(pp);
            break;
        }
        case LAVABLOCK: {
            Lava * lava = new Lava(false);
            lava->moveTo(X, Y);
            inerts.append(lava);
            objects.append(lava);
            break;
        }
        case LAVASCENERY: {
            Lava * lava = new Lava(true);
            lava->moveTo(X, Y + (block_size - 0.34375*block_size));
            inerts.append(lava);
            objects.append(lava);
            break;
        }
        case MARIO: {
            fakeMario = new Mario();
            fakeMario->moveTo(X, Y);
            break;
        }
        case SMALLHILL: {
            Scenery * scenery = new Scenery(SMALLHILLOBJECT);
            scenery->moveTo(X, Y);
            inerts.append(scenery);
            objects.append(scenery);
            break;
        }
        case
            BIGHILL: {
            Scenery * scenery = new Scenery(BIGHILLOBJECT);
            scenery->moveTo(X, Y);
            inerts.append(scenery);
            objects.append(scenery);
            break;
        }
        case
            SMALLBUSH: {
            Scenery * scenery = new Scenery(SMALLBUSHOBJECT);
            scenery->moveTo(X, Y);
            inerts.append(scenery);
            objects.append(scenery);
            break;
        }
        case
            MEDBUSH: {
            Scenery * scenery = new Scenery(MEDBUSHOBJECT);
            scenery->moveTo(X, Y);
            inerts.append(scenery);
            objects.append(scenery);
            break;
        }
        case
            BIGBUSH: {
            Scenery * scenery = new Scenery(BIGBUSHOBJECT);
            scenery->moveTo(X, Y);
            inerts.append(scenery);
            objects.append(scenery);
            break;
        }
        case
            SMALLCLOUD: {
            Scenery * scenery = new Scenery(SMALLCLOUDOBJECT);
            scenery->moveTo(X, Y);
            inerts.append(scenery);
            objects.append(scenery);
            break;
        }
        case
            MEDCLOUD: {
            Scenery * scenery = new Scenery(MEDCLOUDOBJECT);
            scenery->moveTo(X, Y);
            inerts.append(scenery);
            objects.append(scenery);
            break;
        }
        case
            BIGCLOUD: {
            Scenery * scenery = new Scenery(BIGCLOUDOBJECT);
            scenery->moveTo(X, Y);
            inerts.append(scenery);
            objects.append(scenery);
            break;
        }
        default: {
            break;
        }
    }
}

void LevelEditorEngine::deleteObjectAtPosition(int x, int y)
{
    if(flagpole!=nullptr && flagpole->getPosition().x() == x && flagpole->getPosition().y() == y){
        delete flagpole;
        flagpole = nullptr;
    }

    if(castle!=nullptr && castle->getPosition().x() == x && castle->getPosition().y() == y){
        delete castle;
        castle = nullptr;
    }

    for(ObjectModel * object : objects){
        if((object->getPosition().x() == x && (object->getPosition().y() == y || object->getPosition().y()-block_size/2 == y))
                || (object->getPosition().x()==x && object->getPosition().y()-0.34375*block_size-10==y)
                || (x + (2*block_size - 1.3*16/24*block_size)/2 - object->getPosition().x()) < 0.001 && (x + (2*block_size - 1.3*16/24*block_size)/2 - object->getPosition().x()) > -0.001 && (y + block_size - 1.3*block_size - object->getPosition().y()) <0.001 && (y + block_size - 1.3*block_size - object->getPosition().y()) > -0.001){
            Mario * mario = dynamic_cast<Mario*>(object);
            if(mario){
                if(mario != nullptr){
                    objects.removeOne(mario);
                    entities.removeOne(mario);
                    delete mario;
                    mario = nullptr;
                }
            }
            else{
                Entity * entity = dynamic_cast<Entity*>(object);
                if(entity){
                    objects.removeOne(entity);
                    entities.removeOne(entity);
                    delete entity;
                }
                else{
                    Inert * inert = dynamic_cast<Inert*>(object);
                    if(inert){
                        objects.removeOne(inert);
                        inerts.removeOne(inert);
                        delete inert;
                    }
                }
            }
        }
    }
}

void LevelEditorEngine::deleteSceneryObjectAtPosition(int x, int y){
    for(Inert * inert : inerts){
        if(dynamic_cast<Scenery *>(inert)){
            if(inert->getPosition().x() == x && inert->getPosition().y() == y){
                objects.removeOne(inert);
                inerts.removeOne(inert);
                delete inert;
            }
        }
    }
}

void LevelEditorEngine::setMouseState(MouseState ms)
{
    mouseState = ms;
}

void LevelEditorEngine::setSelectedButton(SelectedButton sb){
    selectedButton = sb;

    if(objectToPaintOnMouse != nullptr){
        delete  objectToPaintOnMouse;
        objectToPaintOnMouse = nullptr;
    }

    switch(selectedButton){
        case BRICK:
        case COINBRICK: {
            objectToPaintOnMouse = new Brick();
            break;
        }
        case BLOCK: {
            objectToPaintOnMouse = new Block();
            break;
        }
        case WALL: {
            objectToPaintOnMouse = new Wall();
            break;
        }
        case SECRETBOXMUSHROOM:
        case SECRETBOXFLOWER:
        case SECRETBOXSTAR:
        case SECRETBOXCOIN: {
            objectToPaintOnMouse = new Inert();
            objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/blocs/secret-box.png").scaled(block_size, block_size)));
            break;
        }
        case SMALLMOVINGPLATFORM: {
            objectToPaintOnMouse = new MovingPlatform(false);
            movingMovingPlatform = new MovingPlatform(false);
            movingMovingPlatform->setOpacity(0.5);
            break;
        }
        case LARGEMOVINGPLATFORM: {
            objectToPaintOnMouse = new MovingPlatform(true);
            movingMovingPlatform = new MovingPlatform(true);
            movingMovingPlatform->setOpacity(0.5);
            break;
        }
        case FIREBAR: {
            objectToPaintOnMouse = new Firebar();
            break;
        }
        case COINITEM: {
            objectToPaintOnMouse = new Coin(false);
            break;
        }
        case SMALLPIPE: {
            objectToPaintOnMouse = new Pipe(SMALLPIPEOBJECT);
            break;
        }
        case MEDPIPE: {
            objectToPaintOnMouse = new Pipe(MEDPIPEOBJECT);
            break;
        }
        case BIGPIPE: {
            objectToPaintOnMouse = new Pipe(BIGPIPEOBJECT);
            break;
        }
        case BULLETBLASTER: {
            objectToPaintOnMouse = new Inert();
            objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/bill-blaster.png").scaled(block_size, block_size*2)));
            break;
        }
        case MEDTRAMPOLINE: {
            objectToPaintOnMouse = new Trampoline(false);
            break;
        }
        case BIGTRAMPOLINE: {
            objectToPaintOnMouse = new Trampoline(true);
            break;
        }
        case FLAGPOLE: {
            movingFlagpole = new Flagpole();

            movingCastle = new Inert();
            movingCastle->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/castle.png").scaled(block_size*4, block_size*4)));
            movingCastle->setOpacity(0.5);
            break;
        }
        case GOOMBA: {
            objectToPaintOnMouse = new Goomba();
            break;
        }
        case TURTLE: {
            objectToPaintOnMouse = new Koopa();
            break;
        }
        case FLYINGTURTLE: {
            //TODO
            break;
        }
        case PODOBOO: {
            objectToPaintOnMouse = new Podoboo();
            movingPodoboo = new Podoboo();
            movingPodoboo->setOpacity(0.5);
            break;
        }
        case PIRANHAPLANT: {
            objectToPaintOnMouse = new PiranhaPlant();
            break;
        }
        case LAVABLOCK: {
            objectToPaintOnMouse = new Lava(false);
            break;
        }
        case LAVASCENERY: {
            objectToPaintOnMouse = new Lava(true);
            break;
        }
        case MARIO: {
            objectToPaintOnMouse = new Mario();
            break;
        }
        case SMALLHILL: {
            objectToPaintOnMouse = new Scenery(SMALLHILLOBJECT);
            break;
        }
        case
            BIGHILL: {
            objectToPaintOnMouse = new Scenery(BIGHILLOBJECT);
            break;
        }
        case
            SMALLBUSH: {
            objectToPaintOnMouse = new Scenery(SMALLBUSHOBJECT);
            break;
        }
        case
            MEDBUSH: {
            objectToPaintOnMouse = new Scenery(MEDBUSHOBJECT);
            break;
        }
        case
            BIGBUSH: {
            objectToPaintOnMouse = new Scenery(BIGBUSHOBJECT);
            break;
        }
        case
            SMALLCLOUD: {
            objectToPaintOnMouse = new Scenery(SMALLCLOUDOBJECT);
            break;
        }
        case
            MEDCLOUD: {
            objectToPaintOnMouse = new Scenery(MEDCLOUDOBJECT);
            break;
        }
        case
            BIGCLOUD: {
            objectToPaintOnMouse = new Scenery(BIGCLOUDOBJECT);
            break;
        }
        default: {
            break;
        }
    }

    if(objectToPaintOnMouse){
        objectToPaintOnMouse->setOpacity(0.5);
    }
}

void LevelEditorEngine::advance() {
    //for(Entity * entity : entities){
    // The level editor doesn't have animations
    //}
    levelEditorView->repaint();
}

void LevelEditorEngine::start(){
    //We setup the game engine : A timer that calls advance every 10ms
    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));

    engine.setTimerType(Qt::PreciseTimer);
    engine.setInterval(tickrate); // possible de le passer en dynamique

    engine.start();
}

int LevelEditorEngine::getLineFromMousePosition()
{
     return floor(levelEditorView->mapFromGlobal(QCursor::pos()).y()/block_size);
}

int LevelEditorEngine::getColumnFromMousePosition()
{
     return floor( (levelEditorView->mapFromGlobal(QCursor::pos()).x() + levelEditorView->getCameraPosition() - levelEditorView->getWindowSize().width()/2) / block_size);
}

void LevelEditorEngine::saveLevel()
{
    exportMapToJSon();
}

void LevelEditorEngine::clearMap()
{
    for(Entity * entity : entities){
        objects.removeOne(entity);
        entities.removeOne(entity);
        delete entity;
    }

    for(Inert * inert : inerts){
        objects.removeOne(inert);
        inerts.removeOne(inert);
        delete inert;
    }

    if(fakeMario != nullptr){
        objects.removeOne(fakeMario);
        delete fakeMario;
        fakeMario = nullptr;
    }

    if(castle != nullptr){
        delete castle;
        castle = nullptr;
    }

    if(flagpole != nullptr){
        delete flagpole;
        flagpole = nullptr;
    }
}

void LevelEditorEngine::goBackToMainMenu()
{
    mainWindow->goBackToMainMenu();
}
