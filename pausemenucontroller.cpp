
#include "pausemenucontroller.h"
#include "mainwindow.h"


PauseMenuController::PauseMenuController()
{

}

void PauseMenuController::launchMainMenu()
{
    mainWindow->goBackToMainMenu();
}
