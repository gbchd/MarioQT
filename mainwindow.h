#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QDesktopWidget>

#include "mainmenucontroller.h"
#include "mainmenuwidget.h"

#include "gamecontroller.h"
#include "gameview.h"

#include "leveleditorwidget.h"
#include "leveleditorview.h"
#include "leveleditorengine.h"

#include "pausemenucontroller.h"
#include "pausemenuwidget.h"

#include "settings.h"

#include "optionsmenucontroller.h"
#include "optionsmenuwidget.h"

class MainWindow : public QMainWindow
{
private:
    QStackedWidget stackedWidget;

    MainMenuController mainMenuController;
    MainMenuWidget mainMenuWidget;

    GameController gamecontroller;
    GameView gameview;

    LevelEditorView levelEditorView;
    LevelEditorWidget levelEditorWidget;
    LevelEditorEngine levelEditorEngine;

    PauseMenuController pauseMenuController;
    PauseMenuWidget pauseMenuWidget;

    OptionsMenuController optionsMenuController;
    OptionsMenuWidget optionsMenuWidget;

    Settings settings;

public:
    MainWindow();

    void startGameOnMap(QString filePath);

    void changeCentralWidget(QWidget *newWidget) { setCentralWidget(newWidget); }

    void displayPauseMenu();
    void goBackToGame();
    void goBackToMainMenu();
    void launchLevelEditor();
    void displayOptionsMenu();
    void retryGame();

    void centerOnScreen();
};

#endif // MAINWINDOW_H
