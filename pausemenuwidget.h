#ifndef PAUSEMENUWIDGET_H
#define PAUSEMENUWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class PauseMenuController;

class PauseMenuWidget : public QWidget
{
    Q_OBJECT
private:
    PauseMenuController * pauseMenuController;

    QPushButton continueButton;
    QPushButton menuButton;
    QPushButton retryButton;
    QPushButton quitButton;

    void applyStyleSheet();

public:
    PauseMenuWidget();
    void setPauseMenuController(PauseMenuController * pmc){ pauseMenuController = pmc; }

private slots:
    void handleContinueButton();
    void handleMenuButton();
    void handleRetryButton();
    void handleQuitButton();

};

#endif // PAUSEMENUWIDGET_H
