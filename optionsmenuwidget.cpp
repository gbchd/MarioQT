#include "optionsmenuwidget.h"

#include "optionsmenucontroller.h"
#include "QDebug"

OptionsMenuWidget::OptionsMenuWidget()
{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    QHBoxLayout * hlayoutJump = new QHBoxLayout();
    QHBoxLayout * hlayoutRun = new QHBoxLayout();
    QHBoxLayout * hlayoutMoveRight = new QHBoxLayout();
    QHBoxLayout * hlayoutMoveLeft = new QHBoxLayout();
    QHBoxLayout * hlayoutShootFireBall = new QHBoxLayout();
    QHBoxLayout * hlayoutControlButton = new QHBoxLayout();

    QLabel * jumpLabel = new QLabel("Jump : ");
    keyJumpButton.setText("SPACE");
    hlayoutJump->addWidget(jumpLabel);
    hlayoutJump->addWidget(&keyJumpButton);
    mainLayout->addLayout(hlayoutJump);

    QLabel * runLabel = new QLabel("Run : ");
    keyRunButton.setText("SHIFT");
    hlayoutRun->addWidget(runLabel);
    hlayoutRun->addWidget(&keyRunButton);
    mainLayout->addLayout(hlayoutRun);

    QLabel * moveRightLabel = new QLabel("Move right : ");
    keyMoveRightButton.setText("D");
    hlayoutMoveRight->addWidget(moveRightLabel);
    hlayoutMoveRight->addWidget(&keyMoveRightButton);
    mainLayout->addLayout(hlayoutMoveRight);

    QLabel * moveLeftLabel = new QLabel("Move left : ");
    keyMoveLeftButton.setText("Q");
    hlayoutMoveLeft->addWidget(moveLeftLabel);
    hlayoutMoveLeft->addWidget(&keyMoveLeftButton);
    mainLayout->addLayout(hlayoutMoveLeft);

    QLabel * shootFireBallLabel = new QLabel("Shoot fire ball : ");
    keyShootFireBallButton.setText("SHIFT");
    hlayoutShootFireBall->addWidget(shootFireBallLabel);
    hlayoutShootFireBall->addWidget(&keyShootFireBallButton);
    mainLayout->addLayout(hlayoutShootFireBall);

    menuButton.setText("GO BACK TO MENU");
    saveButton.setText("SAVE");
    exportButton.setText("EXPORT");
    hlayoutControlButton->addWidget(&menuButton);
    hlayoutControlButton->addWidget(&saveButton);
    hlayoutControlButton->addWidget(&exportButton);
    mainLayout->addLayout(hlayoutControlButton);

    //mainLayout->setAlignment(Qt::AlignHCenter);


    applyStyleSheet();


    //Connect the buttons to their slots
    connect(&menuButton, SIGNAL (clicked()), this, SLOT (handleMenuButton()));
}

void OptionsMenuWidget::applyStyleSheet()
{
    QString styleButton = "QPushButton {background-color: #BE2801;"
                          "color: white;"
                          "font-size: 20px;"
                          "font-weight : bold;}"
                          ""
                          "QPushButton:hover {background-color: white;"
                          "color: #BE2801;"
                          "font-size: 20px;"
                          "font-weight : bold;}"
                          ""
                          "QLabel {"
                          "color: #BE2801;"
                          "font-size: 20px;"
                          "font-weight : bold;}";


    setStyleSheet(styleButton);
}

void OptionsMenuWidget::handleMenuButton()
{
    optionsMenuController->launchMainMenu();
}
