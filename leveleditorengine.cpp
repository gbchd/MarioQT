#include "leveleditorengine.h"
#include "mainwindow.h"

LevelEditorEngine::LevelEditorEngine()
{
    mouseState = NOSTATE;
    objectToPaintOnMouse = nullptr;
    mario = nullptr;
    levelEditorView = nullptr;
    tickrate = 1000/60;
}

void LevelEditorEngine::update(CameraVisitor & visitor){
    for(ObjectModel * object : objects){
        object->accept(visitor);
    }
    if(objectToPaintOnMouse != nullptr){
        objectToPaintOnMouse->moveTo(getColumnFromMousePosition()*block_size, getLineFromMousePosition()*block_size);
        objectToPaintOnMouse->accept(visitor);

    }

}

void LevelEditorEngine::setMouseState(MouseState ms)
{
    mouseState = ms;

    switch(mouseState){
        case BRICK: {
            objectToPaintOnMouse = new Inert();
            QImage texture(":/resources/graphics/blocs/wall.png");
            QPixmap pixmap = QPixmap(block_size, block_size);
            QPainter *paint = new QPainter(&pixmap);
            QPoint position(block_size, block_size);
            paint->drawImage(position, texture);
            objectToPaintOnMouse->setCurrentTexture(pixmap);
            break;
        }
        case BLOCK: {
            break;
        }
        case WALL: {
            break;
        }
        case SECRETBOX: {
            break;
        }
        case GOOMBA: {
            break;
        }
        case TURTLE: {
            break;
        }
        case MARIO: {
            break;
        }
        default: {
            break;
        }
    }
}

void LevelEditorEngine::advance() {
    for(Entity * entity : entities){

    }
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
