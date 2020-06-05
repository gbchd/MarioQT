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

    QHBoxLayout * hlayoutdefault = new QHBoxLayout();
    QHBoxLayout * hlayoutJump = new QHBoxLayout();
    QHBoxLayout * hlayoutRun = new QHBoxLayout();
    QHBoxLayout * hlayoutMoveRight = new QHBoxLayout();
    QHBoxLayout * hlayoutMoveLeft = new QHBoxLayout();
    QHBoxLayout * hlayoutShootFireBall = new QHBoxLayout();
    QHBoxLayout * hlayoutControlButton = new QHBoxLayout();

    defaultButton.setText("Default");
    hlayoutdefault->setAlignment(Qt::AlignLeft);
    hlayoutdefault->addWidget(&defaultButton);
    mainLayout->addLayout(hlayoutdefault);

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
    importButton.setText("IMPORT");
    exportButton.setText("EXPORT");
    hlayoutControlButton->addWidget(&menuButton);
    hlayoutControlButton->addWidget(&importButton);
    hlayoutControlButton->addWidget(&exportButton);
    mainLayout->addLayout(hlayoutControlButton);

    applyStyleSheet();

    //Connect the buttons to their slots
    connect(&menuButton, SIGNAL (clicked()), this, SLOT (handleMenuButton()));
    connect(&importButton, SIGNAL (clicked()), this, SLOT (handleImportButton()));
    connect(&exportButton, SIGNAL (clicked()), this, SLOT (handleExportButton()));
    connect(&keyJumpButton, SIGNAL (clicked()), this, SLOT (handleJumpButton()));
    connect(&keyRunButton, SIGNAL (clicked()), this, SLOT (handleRunButton()));
    connect(&keyMoveLeftButton, SIGNAL (clicked()), this, SLOT (handleMoveLeftButton()));
    connect(&keyMoveRightButton, SIGNAL (clicked()), this, SLOT (handleMoveRightButton()));
    connect(&keyShootFireBallButton, SIGNAL (clicked()), this, SLOT (handleShootFireBallButton()));
    connect(&defaultButton, SIGNAL (clicked()), this, SLOT (handleDefaultButton()));
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

QString OptionsMenuWidget::getTextKeyJumpButton()
{
    return keyJumpButton.text();
}

QString OptionsMenuWidget::getTextKeyRunButton()
{
    return keyRunButton.text();
}

QString OptionsMenuWidget::getTextKeyMoveRightButton()
{
    return keyMoveRightButton.text();
}

QString OptionsMenuWidget::getTextKeyMoveLeftButton()
{
    return keyMoveLeftButton.text();
}

QString OptionsMenuWidget::getTextKeyShootFireBall()
{
    return keyShootFireBallButton.text();
}

void OptionsMenuWidget::handleMenuButton()
{
    optionsMenuController->launchMainMenu();
}

void OptionsMenuWidget::handleImportButton()
{
    optionsMenuController->importConfigFromJSON(QFileDialog::getOpenFileName(this, tr("Select a JSON file."), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("JSON files (*.json)")));
}

void OptionsMenuWidget::handleExportButton()
{
    optionsMenuController->exportConfigInJSON();
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

void OptionsMenuWidget::handleDefaultButton()
{
    optionsMenuController->setToDefaultKeyConfig();
}
