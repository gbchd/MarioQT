#ifndef LEVELEDITORCONTROLLER_H
#define LEVELEDITORCONTROLLER_H

#include "leveleditorwidget.h"

class MainWindow;

class LevelEditorController
{
private:
    LevelEditorWidget * levelEditorWidget;

    MainWindow * mainWindow;

public:
    LevelEditorController();

    void setLevelEditorWidget(LevelEditorWidget * lew) { levelEditorWidget = lew; }

    void setMainWindowPointer(MainWindow * mw){ mainWindow = mw; }

    void saveLevel();
    void quit();
    void goBackToMainMenu();
};

#endif // LEVELEDITORCONTROLLER_H
