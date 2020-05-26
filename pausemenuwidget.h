#ifndef PAUSEMENUWIDGET_H
#define PAUSEMENUWIDGET_H

#include <QWidget>

class PauseMenuController;

class PauseMenuWidget : public QWidget
{
    Q_OBJECT
private:
    PauseMenuController * pauseMenuController;

public:
    PauseMenuWidget();
    void setPauseMenuController(PauseMenuController * pmc){ pauseMenuController = pmc; }

private slots:

};

#endif // PAUSEMENUWIDGET_H
