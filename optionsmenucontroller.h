#ifndef OPTIONSMENUCONTROLLER_H
#define OPTIONSMENUCONTROLLER_H

#include "optionsmenuwidget.h"

class MainMenuController;
class MainWindow;

class OptionsMenuController
{
private:
    OptionsMenuWidget * optionsMenuWidget;
    MainWindow * mainWindow;
public:
    OptionsMenuController();
    void setOptionsMenuWidget(OptionsMenuWidget * omw){ optionsMenuWidget = omw; }
    void setMainWindowPointer(MainWindow * mw){ mainWindow = mw; }
    void launchMainMenu();
};

#endif // OPTIONSMENUCONTROLLER_H
