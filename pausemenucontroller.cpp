
#include "pausemenucontroller.h"
#include "mainwindow.h"


PauseMenuController::PauseMenuController()
{

}

void PauseMenuController::launchMainMenu()
{
    mainWindow->goBackToMainMenu();
}

void PauseMenuController::quitApplication()
{
    QCoreApplication::quit();
}

void PauseMenuController::continueGame(){
    mainWindow->goBackToGame();
}

void PauseMenuController::retryGame(){
    mainWindow->retryGame();
}
