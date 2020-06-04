#include "optionsmenucontroller.h"
#include "mainwindow.h"

OptionsMenuController::OptionsMenuController()
{

}

void OptionsMenuController::launchMainMenu()
{
    mainWindow->goBackToMainMenu();
}
