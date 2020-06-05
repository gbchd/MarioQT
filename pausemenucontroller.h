#ifndef PAUSEMENUCONTROLLER_H
#define PAUSEMENUCONTROLLER_H

#include "pausemenuwidget.h"
#include <QCoreApplication>

class MainMenuController;
class MainWindow;

class PauseMenuController
{
private:
    PauseMenuWidget * pauseMenuWidget;
    MainWindow * mainWindow;

public:
    PauseMenuController();
    void setPauseMenuWidget(PauseMenuWidget * pmw){ pauseMenuWidget = pmw; }
    void setMainWindowPointer(MainWindow * mw){ mainWindow = mw; }
    void continueGame();
    void launchMainMenu();
    void quitApplication();
    void retryGame();
};

#endif // PAUSEMENUCONTROLLER_H
