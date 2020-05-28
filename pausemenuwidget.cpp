#include "pausemenuwidget.h"

#include "pausemenucontroller.h"
#include "QDebug"

PauseMenuWidget::PauseMenuWidget()
{

    QVBoxLayout * layout = new QVBoxLayout(this);
    continueButton.setText("CONTINUE");
    menuButton.setText("GO BACK TO MENU");
    optionsButton.setText("OPTIONS");
    quitButton.setText("QUIT");

    layout->setAlignment(Qt::AlignHCenter);

    //listWidget style
    applyStyleSheet();

    //Add element in layout
    layout->addWidget(&continueButton);
    layout->addWidget(&menuButton);
    layout->addWidget(&optionsButton);
    layout->addWidget(&quitButton);

    //Connect the buttons to their slots
    connect(&continueButton, SIGNAL (clicked()), this, SLOT (handleContinueButton()));
    connect(&menuButton, SIGNAL (clicked()), this, SLOT (handleMenuButton()));
    connect(&optionsButton, SIGNAL (clicked()), this, SLOT (handleOptionsButton()));
    connect(&quitButton, SIGNAL (clicked()), this, SLOT (handleQuitButton()));
}

void PauseMenuWidget::applyStyleSheet()
{
    this->setStyleSheet("color: white;"
                        "background-color: black;"
                        "font-size: 20px;"
                        "font-weight : bold;");
}

void PauseMenuWidget::handleContinueButton()
{

}

void PauseMenuWidget::handleMenuButton()
{
    pauseMenuController->launchMainMenu();
}

void PauseMenuWidget::handleOptionsButton()
{

}

void PauseMenuWidget::handleQuitButton()
{
    pauseMenuController->quitApplication();
}
