#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "mainmenuwidget.h"
#include "mainmenucontroller.h"
#include "gameview.h"
#include "gamecontroller.h"

class MainWindow : public QMainWindow
{
private:
    QStackedWidget stackedWidget;

    MainMenuController mainMenuController;
    MainMenuWidget mainMenuWidget;

    GameController gamecontroller;
    GameView gameview;

public:
    MainWindow();

    void startGameOnMap(QString filePath);

    void changeCentralWidget(QWidget *newWidget) { setCentralWidget(newWidget); }
};

#endif // MAINWINDOW_H
