#include "leveleditorengine.h"
#include "mainwindow.h"

LevelEditorEngine::LevelEditorEngine()
{
    mouseState = NOTPRESSED;
    selectedButton = NOBUTTON;
    objectToPaintOnMouse = nullptr;
    mario = nullptr;
    levelEditorView = nullptr;
    tickrate = 1000/60;
}

void LevelEditorEngine::update(CameraVisitor & visitor){
    int X = getColumnFromMousePosition()*block_size;
    int Y = getLineFromMousePosition()*block_size;

    if(mouseState == LEFTCLICKPRESSED){
        addObjectOnMousePosition();
    }

    if(mouseState == RIGHTCLICKPRESSED){
        deleteObjectAtPosition(X, Y);
    }

    for(ObjectModel * object : objects){
        object->accept(visitor);
    }

    if(objectToPaintOnMouse != nullptr){
        objectToPaintOnMouse->moveTo(X, Y);
        objectToPaintOnMouse->accept(visitor);
    }
}

void LevelEditorEngine::addObjectOnMousePosition()
{
    int X = getColumnFromMousePosition()*block_size;
    int Y = getLineFromMousePosition()*block_size;

    deleteObjectAtPosition(X, Y);

    switch(selectedButton){
        case BRICK: {
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/blocs/brick.bmp").scaled(block_size, block_size));
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case BLOCK: {
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/blocs/block.png").scaled(block_size, block_size));
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case WALL: {
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/blocs/wall.png").scaled(block_size, block_size));
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case SECRETBOX: {
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/blocs/secret-box.png").scaled(block_size, block_size));
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
        case MARIO: {
            mario = new Mario();
            mario->moveTo(X, Y);
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
        if(object->getPosition().x() == x && object->getPosition().y() == y){
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
        case BRICK: {
            objectToPaintOnMouse = new Inert();
            objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/blocs/brick.bmp").scaled(block_size, block_size)));
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case BLOCK: {
            objectToPaintOnMouse = new Inert();
            objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/blocs/block.png").scaled(block_size, block_size)));
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case WALL: {
            objectToPaintOnMouse = new Inert();
            objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/blocs/wall.png").scaled(block_size, block_size)));
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case SECRETBOX: {
            objectToPaintOnMouse = new Inert();
            objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/blocs/secret-box.png").scaled(block_size, block_size)));
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

void LevelEditorEngine::addInert(Inert * i){
    inerts.append(i);
    objects.append(i);
}

void LevelEditorEngine::addEntity(Entity * e){
    entities.append(e);
    objects.append(e);
}

int LevelEditorEngine::getLineFromMousePosition()
{
     return floor(levelEditorView->mapFromGlobal(QCursor::pos()).y()/block_size);
}

int LevelEditorEngine::getColumnFromMousePosition()
{
     return floor(levelEditorView->mapFromGlobal(QCursor::pos()).x()/block_size);
}

void LevelEditorEngine::saveLevel()
{

}

void LevelEditorEngine::quit()
{

}

void LevelEditorEngine::goBackToMainMenu()
{
    mainWindow->goBackToMainMenu();
}
