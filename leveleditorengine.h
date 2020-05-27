#ifndef LEVELEDITORENGINE_H
#define LEVELEDITORENGINE_H

#include <QTimer>

#include "cameravisitor.h"
#include "objectmodel.h"
#include "leveleditorview.h"

class LevelEditorEngine : public QObject
{
    Q_OBJECT

private:
    //Timer for the tickrate of the game
    QTimer engine;
    float tickrate;

    //The view controlled by this controller
    LevelEditorView * levelEditorView;

    // Possède des objets de type Inert et Entity
    Mario * mario;
    QList<Inert*> inerts;
    QList<Entity*> entities;

    QList<ObjectModel *> objects;

public:
    LevelEditorEngine();
    void update(CameraVisitor & visitor);
    void advance();
    void start();
    void addInert(Inert * i);
    void addEntity(Entity * e);
};

#endif // LEVELEDITORENGINE_H
