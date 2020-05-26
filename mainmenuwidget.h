#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class MainMenuController;
class MainWindow;

class MainMenuWidget : public QWidget
{
    Q_OBJECT

private:
    MainMenuController * mainMenuController;

    QListWidget listWidget;
    QPushButton playButton;
    QPushButton optionsButton;

    void applyStyleSheet();

public:
    MainMenuWidget();
    void addItemToWidgetList(QString text, QString address);
    void setMainMenuController(MainMenuController * mmc){ mainMenuController = mmc; }

private slots:
    void handlePlayButton();
    void handleOptionsButton();
};

#endif // MAINMENUWIDGET_H
