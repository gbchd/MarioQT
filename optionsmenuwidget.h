#ifndef OPTIONSMENUWIDGET_H
#define OPTIONSMENUWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class OptionsMenuController;

class OptionsMenuWidget : public QWidget
{
    Q_OBJECT
private:
    OptionsMenuController * optionsMenuController;

    QPushButton menuButton;
    QPushButton saveButton;
    QPushButton exportButton;
    QPushButton keyMoveRightButton;
    QPushButton keyMoveLeftButton;
    QPushButton keyRunButton;
    QPushButton keyJumpButton;
    QPushButton keyShootFireBallButton;
public:
    OptionsMenuWidget();
    void setOptionsMenuController(OptionsMenuController * omc){ optionsMenuController = omc; }
    void applyStyleSheet();
private slots:
    void handleMenuButton();
};

#endif // OPTIONSMENUWIDGET_H
