#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    parent();

    // We initialize the mainMenu's widget and controller
    mainMenuController.setMainMenuWidget(&mainMenuWidget);
    mainMenuController.setMainWindowPointer(this);
    mainMenuWidget.setMainMenuController(&mainMenuController);

    // We initialize the game's widget and controller
    gamecontroller.setGameView(&gameview);
    gameview.setGameController(&gamecontroller);

    // We initialize the levelEditor's widget and controller
    levelEditorController.setLevelEditorWidget(&levelEditorWidget);
    levelEditorWidget.setLevelEditorController(&levelEditorController);

    // We initialize the pauseMenu's widget and controller
    pauseMenuController.setPauseMenuWidget(&pauseMenuWidget);
    pauseMenuController.setMainWindowPointer(this);
    pauseMenuWidget.setPauseMenuController(&pauseMenuController);

    // We fill the stackedWidget with the menu, the game and the levelEditor
    stackedWidget.addWidget(&mainMenuWidget);
    stackedWidget.addWidget(&gameview);
    stackedWidget.addWidget(&levelEditorWidget);
    stackedWidget.addWidget(&pauseMenuWidget);

    stackedWidget.setCurrentIndex(0);

    setCentralWidget(&stackedWidget);
}

void MainWindow::startGameOnMap(QString filePath)
{
    stackedWidget.setCurrentIndex(1);
    gamecontroller.setMapFilepath(filePath);
    gamecontroller.start();

    this->resize(1280, 720);
}
