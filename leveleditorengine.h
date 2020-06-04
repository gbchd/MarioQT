#ifndef LEVELEDITORENGINE_H
#define LEVELEDITORENGINE_H

#include <QTimer>
#include <QtMath>
#include <QPainter>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

#include "cameravisitor.h"
#include "objectmodel.h"
#include "inert.h"
#include "box.h"
#include "scenery.h"
#include "pipe.h"
#include "trampoline.h"
#include "flagpole.h"
#include "movingplatform.h"
#include "firebar.h"
#include "leveleditorview.h"
#include "leveleditorwidget.h"

class MainWindow;

class LevelEditorEngine : public QObject
{
    Q_OBJECT

private:
    // Timer for the tickrate of the game
    QTimer engine;
    float tickrate;

    int block_size = 32;

    // The game controlled by this controller
    LevelEditorView * levelEditorView;

    SelectedButton selectedButton;
    MouseState mouseState;
    ObjectModel * objectToPaintOnMouse;

    // The widget controlled by this controller
    LevelEditorWidget * levelEditorWidget;

    MainWindow * mainWindow;

    // Possède des objets de type Inert et Entity
    Mario * fakeMario;
    QList<Inert*> inerts;
    QList<Entity*> entities;
    QList<ObjectModel *> objects;
    Inert * castle; // Since there can be only one castle and it moves with the flag, we keep a pointer to it outside inerts.
    Inert * movingCastle; // The transparent castle to show where it will be.
    Flagpole * flagpole; // Since there can be only one flagpole, we keep a pointer to it outside inerts.
    Flagpole * movingFlagpole; // The transparent flagpole to show where it will be.
    MovingPlatform * movingMovingPlatform; // The transparent movingPlatform to show how it will move

public:
    LevelEditorEngine();
    void exportMapToJSon();
    QString getTypeFromInert(Inert * inert);
    QString getTypeFromEntity(Entity * entity);
    void setLevelEditorView(LevelEditorView * lev) { levelEditorView = lev; }
    void setLevelEditorWidget(LevelEditorWidget * lew) { levelEditorWidget = lew; }
    void setMainWindowPointer(MainWindow * mw){ mainWindow = mw; }
    void setMouseState(MouseState ms);
    void setSelectedButton(SelectedButton sb);
    void addObjectOnMousePosition();
    void deleteObjectAtPosition(int x, int y);
    void deleteSceneryObjectAtPosition(int x, int y);
    void update(CameraVisitor & visitor);
    void changeCameraPosition(int value);
    void start();

    int getLineFromMousePosition();
    int getColumnFromMousePosition();

    void saveLevel();
    void clearMap();
    void goBackToMainMenu();

public slots:
    void advance();
};

#endif // LEVELEDITORENGINE_H
