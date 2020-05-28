#ifndef LEVELEDITORENGINE_H
#define LEVELEDITORENGINE_H

#include <QTimer>
#include <QtMath>
#include <QPainter>

#include "cameravisitor.h"
#include "objectmodel.h"
#include "inert.h"
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
    Mario * cameraMario;
    Mario * fakeMario;
    QList<Inert*> inerts;
    QList<Entity*> entities;
    QList<ObjectModel *> objects;

public:
    LevelEditorEngine();
    void setLevelEditorView(LevelEditorView * lev) { levelEditorView = lev; }
    void setLevelEditorWidget(LevelEditorWidget * lew) { levelEditorWidget = lew; }
    void setMainWindowPointer(MainWindow * mw){ mainWindow = mw; }
    void setMouseState(MouseState ms);
    void setSelectedButton(SelectedButton sb);
    void addObjectOnMousePosition();
    void deleteObjectAtPosition(int x, int y);
    void update(CameraVisitor & visitor);
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
