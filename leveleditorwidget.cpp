#include "leveleditorwidget.h"

#include "leveleditorview.h"
#include "leveleditorengine.h"

LevelEditorWidget::LevelEditorWidget()
{
    connect(&buttonSave, SIGNAL (clicked()), this, SLOT (handleButtonSave()));
    connect(&buttonMenu, SIGNAL (clicked()), this, SLOT (handleButtonMenu()));
    connect(&buttonClear, SIGNAL (clicked()), this, SLOT (handleButtonClear()));
    connect(&gridRadioButton, SIGNAL (toggled(bool)), this, SLOT (handleGridRadioButton()));

    connect(&buttonBrick, SIGNAL (clicked()), this, SLOT (handleButtonBrick()));
    connect(&buttonBlock, SIGNAL (clicked()), this, SLOT (handleButtonBlock()));
    connect(&buttonWall, SIGNAL (clicked()), this, SLOT (handleButtonWall()));
    connect(&buttonSecretBox, SIGNAL (clicked()), this, SLOT (handleButtonSecretBox()));
    connect(&buttonGoomba, SIGNAL (clicked()), this, SLOT (handleButtonGoomba()));
    connect(&buttonTurtle, SIGNAL (clicked()), this, SLOT (handleButtonTurtle()));
    connect(&buttonMario, SIGNAL (clicked()), this, SLOT (handleButtonMario()));

    this->setLayout(&mainGridLayout);

    firstHorizontalLayout.setAlignment(Qt::AlignLeft);
    mainGridLayout.addLayout(&firstHorizontalLayout, 0, 0, Qt::AlignLeft);

    firstHorizontalLayout.addLayout(&menuVerticalLayout);
    menuVerticalLayout.setSpacing(0);
    buttonSave.setText("Save");
    buttonSave.setFixedSize(80, 20);
    menuVerticalLayout.addWidget(&buttonSave);
    buttonMenu.setText("Menu");
    buttonMenu.setFixedSize(80, 20);
    menuVerticalLayout.addWidget(&buttonMenu);
    buttonClear.setText("Clear");
    buttonClear.setFixedSize(80, 20);
    menuVerticalLayout.addWidget(&buttonClear);

    firstHorizontalLayout.addLayout(&objectButtonsHorizontalLayout);

    QPixmap brickIcon(":/resources/graphics/blocs/brick.bmp");
    QIcon brickButtonIcon(brickIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBrick.setIcon(brickButtonIcon);
    buttonBrick.setIconSize(QSize(buttonSize, buttonSize));
    buttonBrick.resize(buttonSize,buttonSize);

    QPixmap blockIcon(":/resources/graphics/blocs/block.png");
    QIcon blockButtonIcon(blockIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBlock.setIcon(blockButtonIcon);
    buttonBlock.setIconSize(QSize(buttonSize, buttonSize));
    buttonBlock.resize(buttonSize,buttonSize);

    QPixmap wallIcon(":/resources/graphics/blocs/wall.png");
    QIcon wallButtonIcon(wallIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonWall.setIcon(wallButtonIcon);
    buttonWall.setIconSize(QSize(buttonSize, buttonSize));
    buttonWall.resize(buttonSize,buttonSize);

    QPixmap secretBoxIcon(":/resources/graphics/blocs/secret-box.png");
    QIcon secretBoxButtonIcon(secretBoxIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonSecretBox.setIcon(secretBoxButtonIcon);
    buttonSecretBox.setIconSize(QSize(buttonSize, buttonSize));
    buttonSecretBox.resize(buttonSize,buttonSize);

    QPixmap smallPipeIcon(":/resources/graphics/pipe-small.png");
    QIcon smallPipeButtonIcon(smallPipeIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonSmallPipe.setIcon(smallPipeButtonIcon);
    buttonSmallPipe.setIconSize(QSize(buttonSize, buttonSize));
    buttonSmallPipe.resize(buttonSize,buttonSize);

    QPixmap medPipeIcon(":/resources/graphics/pipe-med.png");
    QIcon medPipeButtonIcon(medPipeIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonMedPipe.setIcon(medPipeIcon);
    buttonMedPipe.setIconSize(QSize(buttonSize, buttonSize));
    buttonMedPipe.resize(buttonSize,buttonSize);

    QPixmap bigPipeIcon(":/resources/graphics/pipe-big.png");
    QIcon bigPipeButtonIcon(bigPipeIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBigPipe.setIcon(bigPipeButtonIcon);
    buttonBigPipe.setIconSize(QSize(buttonSize, buttonSize));
    buttonBigPipe.resize(buttonSize,buttonSize);

    QPixmap flagpoleIcon(":/resources/graphics/flagpole.png");
    QIcon flagpoleButtonIcon(flagpoleIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonFlagpole.setIcon(flagpoleButtonIcon);
    buttonFlagpole.setIconSize(QSize(buttonSize, buttonSize));
    buttonFlagpole.resize(buttonSize,buttonSize);

    QPixmap castleIcon(":/resources/graphics/castle.png");
    QIcon castleButtonIcon(castleIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonCastle.setIcon(castleButtonIcon);
    buttonCastle.setIconSize(QSize(buttonSize, buttonSize));
    buttonCastle.resize(buttonSize,buttonSize);

    QPixmap goombaIcon(":/resources/graphics/mobs/goomba/goomba-0.png");
    QIcon goombaButtonIcon(goombaIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonGoomba.setIcon(goombaButtonIcon);
    buttonGoomba.setIconSize(QSize(buttonSize, buttonSize));
    buttonGoomba.resize(buttonSize,buttonSize);

    QPixmap turtleIcon(":/resources/graphics/mobs/turtle/turtle-walk-0.png");
    QIcon turtleButtonIcon(turtleIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonTurtle.setIcon(turtleButtonIcon);
    buttonTurtle.setIconSize(QSize(buttonSize, buttonSize));
    buttonTurtle.resize(buttonSize,buttonSize);

    QPixmap flyingTurtleIcon(":/resources/graphics/mobs/turtle_fly/turtle-fly-0.png");
    QIcon flyingTurtleButtonIcon(flyingTurtleIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonFlyingTurtle.setIcon(flyingTurtleButtonIcon);
    buttonFlyingTurtle.setIconSize(QSize(buttonSize, buttonSize));
    buttonFlyingTurtle.resize(buttonSize,buttonSize);

    QPixmap marioIcon(":/resources/graphics/characters/mario/mario-big-stand.png");
    QIcon marioButtonIcon(marioIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonMario.setIcon(marioButtonIcon);
    buttonMario.setIconSize(QSize(buttonSize, buttonSize));
    buttonMario.resize(buttonSize,buttonSize);

    objectButtonsHorizontalLayout.addWidget(&buttonBrick);
    objectButtonsHorizontalLayout.addWidget(&buttonBlock);
    objectButtonsHorizontalLayout.addWidget(&buttonWall);
    objectButtonsHorizontalLayout.addWidget(&buttonSecretBox);
    objectButtonsHorizontalLayout.addWidget(&buttonSmallPipe);
    objectButtonsHorizontalLayout.addWidget(&buttonMedPipe);
    objectButtonsHorizontalLayout.addWidget(&buttonBigPipe);
    objectButtonsHorizontalLayout.addWidget(&buttonFlagpole);
    objectButtonsHorizontalLayout.addWidget(&buttonCastle);
    objectButtonsHorizontalLayout.addWidget(&buttonGoomba);
    objectButtonsHorizontalLayout.addWidget(&buttonTurtle);
    objectButtonsHorizontalLayout.addWidget(&buttonFlyingTurtle);
    objectButtonsHorizontalLayout.addWidget(&buttonMario);

    gridRadioButton.setText("Grid");
    firstHorizontalLayout.addWidget(&gridRadioButton);

    gameDisplayContainerWidget.resize(1280, 720);

    QSlider * slider = new QSlider(Qt::Horizontal);
    mainGridLayout.addWidget(slider, 2, 0);
}

void LevelEditorWidget::setLevelEditorView(LevelEditorView *lev){
    levelEditorView = lev;
    mainGridLayout.addWidget(levelEditorView, 1, 0);
}

void LevelEditorWidget::handleButtonSave() { levelEditorEngine->saveLevel(); }

void LevelEditorWidget::handleButtonMenu() { levelEditorEngine->goBackToMainMenu(); }

void LevelEditorWidget::handleButtonClear() { levelEditorEngine->clearMap(); }

void LevelEditorWidget::handleGridRadioButton() { levelEditorView->setShowLevelGrid(gridRadioButton.isChecked()); }

void LevelEditorWidget::handleButtonBrick() { levelEditorEngine->setSelectedButton(BRICK); }

void LevelEditorWidget::handleButtonBlock() { levelEditorEngine->setSelectedButton(BLOCK); }

void LevelEditorWidget::handleButtonWall() { levelEditorEngine->setSelectedButton(WALL); }

void LevelEditorWidget::handleButtonSecretBox() { levelEditorEngine->setSelectedButton(SECRETBOX); }

void LevelEditorWidget::handleButtonSmallPipe() { levelEditorEngine->setSelectedButton(SMALLPIPE); }

void LevelEditorWidget::handleButtonMedPipe() { levelEditorEngine->setSelectedButton(MEDPIPE); }

void LevelEditorWidget::handleButtonBigPipe() { levelEditorEngine->setSelectedButton(BIGPIPE); }

void LevelEditorWidget::handleButtonFlagpole() { levelEditorEngine->setSelectedButton(FLAGPOLE); }

void LevelEditorWidget::handleButtonCastle() { levelEditorEngine->setSelectedButton(CASTLE); }

void LevelEditorWidget::handleButtonGoomba() { levelEditorEngine->setSelectedButton(GOOMBA); }

void LevelEditorWidget::handleButtonTurtle() { levelEditorEngine->setSelectedButton(TURTLE); }

void LevelEditorWidget::handleButtonTurtleFlying() { levelEditorEngine->setSelectedButton(FLYINGTURTLE); }

void LevelEditorWidget::handleButtonMario() { levelEditorEngine->setSelectedButton(MARIO); }
