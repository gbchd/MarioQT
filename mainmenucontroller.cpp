#include "mainmenucontroller.h"

#include "mainwindow.h"

MainMenuController::MainMenuController()
{
}

QString MainMenuController::getMapName(QString filename)
{
    QFile file_obj(filename);
    if(!file_obj.exists()){
        //qDebug()<<"File does not exist"<<filename;
        exit(1);
    }
    if(!file_obj.open(QIODevice::ReadOnly)){
        //qDebug()<<"Failed to open "<<filename;
        exit(1);
    }

    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    QJsonDocument map = QJsonDocument::fromJson(json_bytes);
    QJsonObject jsonObject = map.object();

    QString mapName = jsonObject["name"].toString();

    return mapName;
}

void MainMenuController::readMapsDirectory(QString directoryPath)
{
    QDir dir(directoryPath);
    if (!dir.exists())
        qWarning("Cannot find the directory");

    maps = dir.entryList(QStringList(),QDir::Files);
    foreach(QString jsonFileName, maps)
    {
        mainMenuWidget->addItemToWidgetList(getMapName(directoryPath+jsonFileName), directoryPath+jsonFileName);
    }
}

void MainMenuController::addLevelToList(QString levelPath)
{
    if(QFileInfo::exists(levelPath)){
        mainMenuWidget->addItemToWidgetList(getMapName(levelPath), levelPath);
    }
}

void MainMenuController::setMainMenuWidget(MainMenuWidget *mmw)
{
    mainMenuWidget = mmw;

    QString directoryPath = ":/resources/maps/";

    readMapsDirectory(directoryPath);
}

void MainMenuController::launchGameOnMainWindow(QString filePath)
{
    mainWindow->startGameOnMap(filePath);
}

void MainMenuController::launchLevelEditorOnMainWindow()
{
    mainWindow->launchLevelEditor();
}

void MainMenuController::launchOptionsMenuOnMainWindow()
{
    mainWindow->displayOptionsMenu();
}
