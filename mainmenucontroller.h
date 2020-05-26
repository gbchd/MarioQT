#ifndef MAINMENUCONTROLLER_H
#define MAINMENUCONTROLLER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QDir>

#include "mainmenuwidget.h"

class MainWindow;

class MainMenuController
{
private:
    MainMenuWidget * mainMenuWidget;

    MainWindow * mainWindow;

    QStringList maps;

public:
    MainMenuController();

    void setMainWindowPointer(MainWindow * mw){ mainWindow = mw; }

    /**
     * @brief getMap : Returns the name of the map.
     * @param filename
     * @return
     */
    QString getMapName(QString filename);

    /**
     * @brief readMapsDirectory : Fills the string list of maps
     * @param directoryPath
     */
    void readMapsDirectory(QString directoryPath);

    void setMainMenuWidget(MainMenuWidget * mmw);

    void launchGameOnMainWindow(QString filePath);
};

#endif // MAINMENUCONTROLLER_H
