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
    gamecontroller.setMainWindowPointer(this);
    gameview.setGameController(&gamecontroller);



    // We initialize the levelEditor's widget and controller
    levelEditorController.setLevelEditorWidget(&levelEditorWidget);
    levelEditorController.setMainWindowPointer(this);
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

    //Display the menu to the application start
    goBackToMainMenu();

    setCentralWidget(&stackedWidget);
}

void MainWindow::startGameOnMap(QString filePath)
{
    stackedWidget.setCurrentIndex(1);
    gamecontroller.setMapFilepath(filePath);
    gamecontroller.start();

    resize(1280, 720);
    centerOnScreen();
}

void MainWindow::displayPauseMenu()
{
    stackedWidget.setCurrentIndex(3);
}

void MainWindow::goBackToMainMenu()
{
    stackedWidget.setCurrentIndex(0);
    resize(500,500);
    centerOnScreen();
}

void MainWindow::launchLevelEditor()
{
    stackedWidget.setCurrentIndex(2);
    levelEditorWidget.initializeNewLevelEditor();
    resize(1920, 1080);
    centerOnScreen();
}

void MainWindow::centerOnScreen()
{
    QDesktopWidget wid;
    int width = frameGeometry().width();
    int height = frameGeometry().height();
    int screenWidth = wid.screen()->width();
    int screenHeight = wid.screen()->height();

    move((screenWidth/2)-(width/2),(screenHeight/2)-(height/2));
}
