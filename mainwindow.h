#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QDesktopWidget>

#include "mainmenucontroller.h"
#include "mainmenuwidget.h"

#include "gamecontroller.h"
#include "gameview.h"

#include "leveleditorcontroller.h"
#include "leveleditorwidget.h"

#include "pausemenucontroller.h"
#include "pausemenuwidget.h"

class MainWindow : public QMainWindow
{
private:
    QStackedWidget stackedWidget;

    MainMenuController mainMenuController;
    MainMenuWidget mainMenuWidget;

    GameController gamecontroller;
    GameView gameview;

    LevelEditorController levelEditorController;
    LevelEditorWidget levelEditorWidget;

    PauseMenuController pauseMenuController;
    PauseMenuWidget pauseMenuWidget;

public:
    MainWindow();

    void startGameOnMap(QString filePath);

    void changeCentralWidget(QWidget *newWidget) { setCentralWidget(newWidget); }

    void displayPauseMenu();
    void goBackToMainMenu();
    void launchLevelEditor();

    void centerOnScreen();
};

#endif // MAINWINDOW_H
