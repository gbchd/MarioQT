#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    parent();

    // We initialize the mainMenu's view and controller
    mainMenuController.setMainMenuWidget(&mainMenuWidget);
    mainMenuController.setMainWindowPointer(this);
    mainMenuWidget.setMainMenuController(&mainMenuController);

    // We initialize the game's view and controller
    gamecontroller.setGameView(&gameview);
    gameview.setGameController(&gamecontroller);

    // We initialize the levelEditor's view and controller
    //TODO

    // We fill the stackedWidget with the menu, the game and the levelEditor
    stackedWidget.addWidget(&mainMenuWidget);
    stackedWidget.addWidget(&gameview);

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
