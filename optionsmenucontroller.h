#ifndef OPTIONSMENUCONTROLLER_H
#define OPTIONSMENUCONTROLLER_H

#include "optionsmenuwidget.h"
#include "settings.h"
#include "QKeySequence"

class MainMenuController;
class MainWindow;

class OptionsMenuController
{
private:
    OptionsMenuWidget * optionsMenuWidget;
    MainWindow * mainWindow;
    Settings * settings;
    LastClickedOptionButton lastClickedOptionButton;
public:
    OptionsMenuController();
    void setOptionsMenuWidget(OptionsMenuWidget * omw){ optionsMenuWidget = omw; }
    void setMainWindowPointer(MainWindow * mw){ mainWindow = mw; }
    void launchMainMenu();
    void keyPressEventHandler(QKeyEvent * e);
    void setSettingsPointer(Settings * settings){this->settings = settings;};
    void setSelectedButton(LastClickedOptionButton lcob, QString buttonEvent);
    void setToDefaultKeyConfig();
    void importConfigFromJSON(QString JSONPath);
    void exportConfigInJSON();

};

#endif // OPTIONSMENUCONTROLLER_H
