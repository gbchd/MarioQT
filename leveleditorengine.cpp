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
            stream<<"\"x\":"<<inerts[indice]->getPosition().x()/32<<",\"y\":"<<inerts[indice]->getPosition().y()/32<<",\"width\":1,\"height\":1}";
        }
        stream<<"},\"entities\":{";
        for(int indice=0; indice<entities.length(); indice++){
            if(indice>0){ stream<<","; }
            stream<<"\"entity"<<indice<<"\":{\"type\":\""<<getTypeFromEntity(entities[indice])<<"\",\"x\":"<<entities[indice]->getPosition().x()/32<<",\"y\":"<<entities[indice]->getPosition().y()/32<<"}";
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
    }

    if(fakeMario != nullptr){
        fakeMario->accept(visitor);
    }

    if(objectToPaintOnMouse != nullptr){
        objectToPaintOnMouse->moveTo(X, Y);
        objectToPaintOnMouse->accept(visitor);
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
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/flagpole.png").scaled(block_size, block_size*11));
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case CASTLE: {
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/castle.png").scaled(block_size*4, block_size*4));
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
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
    for(ObjectModel * object : objects){
        if(object->getPosition().x() == x && (object->getPosition().y() == y || object->getPosition().y()-block_size/2 == y)){
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
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case BLOCK: {
            objectToPaintOnMouse = new Block();
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case WALL: {
            objectToPaintOnMouse = new Wall();
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case SECRETBOXMUSHROOM:
        case SECRETBOXFLOWER:
        case SECRETBOXSTAR:
        case SECRETBOXCOIN: {
            objectToPaintOnMouse = new Inert();
            objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/blocs/secret-box.png").scaled(block_size, block_size)));
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case COINITEM: {
            objectToPaintOnMouse = new Coin(false);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case SMALLPIPE: {
            objectToPaintOnMouse = new Pipe(SMALLPIPEOBJECT);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case MEDPIPE: {
            objectToPaintOnMouse = new Pipe(MEDPIPEOBJECT);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case BIGPIPE: {
            objectToPaintOnMouse = new Pipe(BIGPIPEOBJECT);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case BULLETBLASTER: {
            objectToPaintOnMouse = new Inert();
            objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/bill-blaster.png").scaled(block_size, block_size*2)));
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case MEDTRAMPOLINE: {
            objectToPaintOnMouse = new Trampoline(false);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case BIGTRAMPOLINE: {
            objectToPaintOnMouse = new Trampoline(true);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case FLAGPOLE: {
            objectToPaintOnMouse = new Inert();
            objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/flagpole.png").scaled(block_size, block_size*11)));
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case CASTLE: {
            objectToPaintOnMouse = new Inert();
            objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/castle.png").scaled(block_size*4, block_size*4)));
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case GOOMBA: {
            objectToPaintOnMouse = new Goomba();
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case TURTLE: {
            objectToPaintOnMouse = new Koopa();
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case MARIO: {
            objectToPaintOnMouse = new Mario();
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case SMALLHILL: {
            objectToPaintOnMouse = new Scenery(SMALLHILLOBJECT);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case
            BIGHILL: {
            objectToPaintOnMouse = new Scenery(BIGHILLOBJECT);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case
            SMALLBUSH: {
            objectToPaintOnMouse = new Scenery(SMALLBUSHOBJECT);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case
            MEDBUSH: {
            objectToPaintOnMouse = new Scenery(MEDBUSHOBJECT);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case
            BIGBUSH: {
            objectToPaintOnMouse = new Scenery(BIGBUSHOBJECT);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case
            SMALLCLOUD: {
            objectToPaintOnMouse = new Scenery(SMALLCLOUDOBJECT);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case
            MEDCLOUD: {
            objectToPaintOnMouse = new Scenery(MEDCLOUDOBJECT);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case
            BIGCLOUD: {
            objectToPaintOnMouse = new Scenery(BIGCLOUDOBJECT);
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        default: {
            break;
        }
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
}

void LevelEditorEngine::goBackToMainMenu()
{
    mainWindow->goBackToMainMenu();
}
