#include "optionsmenuwidget.h"

#include "optionsmenucontroller.h"
#include "QDebug"

void OptionsMenuWidget::keyPressEvent(QKeyEvent *e)
{
    optionsMenuController->keyPressEventHandler(e);
}

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
    keyJumpButton.setObjectName("keyJumpButton");
    hlayoutJump->addWidget(jumpLabel);
    hlayoutJump->addWidget(&keyJumpButton);
    mainLayout->addLayout(hlayoutJump);

    QLabel * runLabel = new QLabel("Run : ");
    keyRunButton.setText("SHIFT");
    keyRunButton.setObjectName("keyRunButton");
    hlayoutRun->addWidget(runLabel);
    hlayoutRun->addWidget(&keyRunButton);
    mainLayout->addLayout(hlayoutRun);

    QLabel * moveRightLabel = new QLabel("Move right : ");
    keyMoveRightButton.setText("D");
    keyMoveRightButton.setObjectName("keyMoveRightButton");
    hlayoutMoveRight->addWidget(moveRightLabel);
    hlayoutMoveRight->addWidget(&keyMoveRightButton);
    mainLayout->addLayout(hlayoutMoveRight);

    QLabel * moveLeftLabel = new QLabel("Move left : ");
    keyMoveLeftButton.setText("Q");
    keyMoveLeftButton.setObjectName("keyMoveLeftButton");
    hlayoutMoveLeft->addWidget(moveLeftLabel);
    hlayoutMoveLeft->addWidget(&keyMoveLeftButton);
    mainLayout->addLayout(hlayoutMoveLeft);

    QLabel * shootFireBallLabel = new QLabel("Shoot fire ball : ");
    keyShootFireBallButton.setText("SHIFT");
    keyShootFireBallButton.setObjectName("keyShootFireBallButton");
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

    applyStyleSheet();

    //Connect the buttons to their slots
    connect(&menuButton, SIGNAL (clicked()), this, SLOT (handleMenuButton()));
    connect(&saveButton, SIGNAL (clicked()), this, SLOT (handleSaveButton()));
    connect(&exportButton, SIGNAL (clicked()), this, SLOT (handleExportButton()));
    connect(&keyJumpButton, SIGNAL (clicked()), this, SLOT (handleJumpButton()));
    connect(&keyRunButton, SIGNAL (clicked()), this, SLOT (handleRunButton()));
    connect(&keyMoveLeftButton, SIGNAL (clicked()), this, SLOT (handleMoveLeftButton()));
    connect(&keyMoveRightButton, SIGNAL (clicked()), this, SLOT (handleMoveRightButton()));
    connect(&keyShootFireBallButton, SIGNAL (clicked()), this, SLOT (handleShootFireBallButton()));
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

void OptionsMenuWidget::setTextKeyJumpButton(QString text)
{
    keyJumpButton.setText(text);
}

void OptionsMenuWidget::setTextKeyRunButton(QString text)
{
    keyRunButton.setText(text);
}

void OptionsMenuWidget::setTextKeyMoveRightButton(QString text)
{
    keyMoveRightButton.setText(text);
}

void OptionsMenuWidget::setTextKeyMoveLeftButton(QString text)
{
    keyMoveLeftButton.setText(text);
}

void OptionsMenuWidget::setTextKeyShootFireBallButton(QString text)
{
    keyShootFireBallButton.setText(text);
}

void OptionsMenuWidget::changeStyleSheetOfTheSelectedButton(QString keyButton)
{
    QString styleButton = "QPushButton {background-color: #BE2801;"
                           "color: white;"
                           "font-size: 20px;"
                           "font-weight : bold;}"
                           ""
                          "QPushButton#"+keyButton+"{background-color: blue;"
                          "color: white;"
                          "font-size: 20px;"
                          "font-weight : bold;}"
                           ""
                           "QLabel {"
                           "color: #BE2801;"
                           "font-size: 20px;"
                           "font-weight : bold;}"
                           ""
                           "QPushButton:hover {background-color: white;"
                           "color: #BE2801;"
                           "font-size: 20px;"
                           "font-weight : bold;}";
    setStyleSheet(styleButton);
}

void OptionsMenuWidget::handleMenuButton()
{
    optionsMenuController->launchMainMenu();
}

void OptionsMenuWidget::handleSaveButton()
{
    qDebug() << "SAVE";
}

void OptionsMenuWidget::handleExportButton()
{
    qDebug() << "export";
}

void OptionsMenuWidget::handleMoveRightButton()
{
    optionsMenuController->setSelectedButton(MOVERIGHT, "keyMoveRightButton");
}

void OptionsMenuWidget::handleMoveLeftButton()
{
    optionsMenuController->setSelectedButton(MOVELEFT, "keyMoveLeftButton");
}

void OptionsMenuWidget::handleJumpButton()
{
    optionsMenuController->setSelectedButton(JUMP, "keyJumpButton");
}

void OptionsMenuWidget::handleRunButton()
{
    optionsMenuController->setSelectedButton(RUN, "keyRunButton");
}

void OptionsMenuWidget::handleShootFireBallButton()
{
   optionsMenuController->setSelectedButton(SHOOTFIREBALL, "keyShootFireBallButton");
}
