#include "leveleditorengine.h"

LevelEditorEngine::LevelEditorEngine()
{
    mario = nullptr;
    levelEditorView = nullptr;
    tickrate = 1000/60;
}

void LevelEditorEngine::update(CameraVisitor & visitor){
    for(ObjectModel * object : objects){
        object->accept(visitor);
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
