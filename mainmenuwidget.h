#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStandardPaths>
#include <QLabel>

class MainMenuController;

class MainMenuWidget : public QWidget
{
    Q_OBJECT

private:
    MainMenuController * mainMenuController;

    QListWidget listWidget;
    QPushButton playButton;
    QPushButton loadLevelButton;
    QPushButton optionsButton;
    QPushButton levelEditorButton;

    void applyStyleSheet();

public:
    MainMenuWidget();
    void addItemToWidgetList(QString text, QString address);
    void setMainMenuController(MainMenuController * mmc){ mainMenuController = mmc; }

private slots:
    void handlePlayButton();
    void handleOptionsButton();
    void handleLoadLevelButton();
    void handleLevelEditorButton();
};

#endif // MAINMENUWIDGET_H
