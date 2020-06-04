#include "pausemenuwidget.h"

#include "pausemenucontroller.h"
#include "QDebug"

PauseMenuWidget::PauseMenuWidget()
{

    QVBoxLayout * layout = new QVBoxLayout(this);
    continueButton.setText("CONTINUE");
    menuButton.setText("GO BACK TO MENU");
    quitButton.setText("QUIT");

    layout->setAlignment(Qt::AlignHCenter);

    //listWidget style
    applyStyleSheet();

    //Add element in layout
    layout->addWidget(&continueButton);
    layout->addWidget(&menuButton);
    layout->addWidget(&quitButton);

    //Connect the buttons to their slots
    connect(&continueButton, SIGNAL (clicked()), this, SLOT (handleContinueButton()));
    connect(&menuButton, SIGNAL (clicked()), this, SLOT (handleMenuButton()));
    connect(&quitButton, SIGNAL (clicked()), this, SLOT (handleQuitButton()));
}

void PauseMenuWidget::applyStyleSheet()
{
    QString styleButton = "QPushButton {background-color: black;"
                          "color: white;"
                          "font-size: 20px;"
                          "font-weight : bold;}"
                          ""
                          "QPushButton:hover {background-color: white;"
                          "color: black;"
                          "font-size: 20px;"
                          "font-weight : bold;}";

    setStyleSheet(styleButton);
}

void PauseMenuWidget::handleContinueButton()
{

}

void PauseMenuWidget::handleMenuButton()
{
    pauseMenuController->launchMainMenu();
}

void PauseMenuWidget::handleQuitButton()
{
    pauseMenuController->quitApplication();
}
