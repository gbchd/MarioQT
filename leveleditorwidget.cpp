#include "leveleditorwidget.h"

#include "leveleditorcontroller.h"
#include "leveleditorview.h"

LevelEditorWidget::LevelEditorWidget()
{
    connect(&buttonSave, SIGNAL (clicked()), this, SLOT (handleButtonSave()));
    connect(&buttonMenu, SIGNAL (clicked()), this, SLOT (handleButtonMenu()));
    connect(&buttonQuit, SIGNAL (clicked()), this, SLOT (handleButtonQuit()));
    connect(&gridRadioButton, SIGNAL (toggled(bool)), this, SLOT (handleGridRadioButton()));

    connect(&buttonBrick, SIGNAL (clicked()), this, SLOT (handleButtonBrick()));
    connect(&buttonBlock, SIGNAL (clicked()), this, SLOT (handleButtonBlock()));
    connect(&buttonWall, SIGNAL (clicked()), this, SLOT (handleButtonWall()));
    connect(&buttonSecretBox, SIGNAL (clicked()), this, SLOT (handleButtonSecretBox()));
    connect(&buttonGoomba, SIGNAL (clicked()), this, SLOT (handleButtonGoomba()));
    connect(&buttonTurtle, SIGNAL (clicked()), this, SLOT (handleButtonTurtle()));
    connect(&buttonMario, SIGNAL (clicked()), this, SLOT (handleButtonMario()));

    mouseState = UNKNOWN;

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
    buttonQuit.setText("Quit");
    buttonQuit.setFixedSize(80, 20);
    menuVerticalLayout.addWidget(&buttonQuit);

    firstHorizontalLayout.addLayout(&objectButtonsHorizontalLayout);

    QPixmap brickIcon(":/resources/graphics/blocs/brick.bmp");
    QIcon brickButtonIcon(brickIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBrick.setIcon(brickButtonIcon);
    buttonBrick.setIconSize(QSize(buttonSize, buttonSize));
    buttonBrick.setFixedSize(buttonSize,buttonSize);

    QPixmap blockIcon(":/resources/graphics/blocs/block.png");
    QIcon blockButtonIcon(blockIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBlock.setIcon(blockButtonIcon);
    buttonBlock.setIconSize(QSize(buttonSize, buttonSize));
    buttonBlock.setFixedSize(buttonSize,buttonSize);

    QPixmap wallIcon(":/resources/graphics/blocs/wall.png");
    QIcon wallButtonIcon(brickIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonWall.setIcon(wallButtonIcon);
    buttonWall.setIconSize(QSize(buttonSize, buttonSize));
    buttonWall.setFixedSize(buttonSize,buttonSize);

    QPixmap secretBoxIcon(":/resources/graphics/blocs/secret-box.png");
    QIcon secretBoxButtonIcon(secretBoxIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonSecretBox.setIcon(secretBoxButtonIcon);
    buttonSecretBox.setIconSize(QSize(buttonSize, buttonSize));
    buttonSecretBox.setFixedSize(buttonSize,buttonSize);

    QPixmap goombaIcon(":/resources/graphics/mobs/goomba/goomba-0.png");
    QIcon goombaButtonIcon(goombaIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonGoomba.setIcon(goombaButtonIcon);
    buttonGoomba.setIconSize(QSize(buttonSize, buttonSize));
    buttonGoomba.setFixedSize(buttonSize,buttonSize);

    QPixmap turtleIcon(":/resources/graphics/mobs/turtle/turtle-walk-0.png");
    QIcon turtleButtonIcon(turtleIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonTurtle.setIcon(turtleButtonIcon);
    buttonTurtle.setIconSize(QSize(buttonSize, buttonSize));
    buttonTurtle.setFixedSize(buttonSize,buttonSize);

    QPixmap marioIcon(":/resources/graphics/characters/mario/mario-big-stand.png");
    QIcon marioButtonIcon(marioIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonMario.setIcon(marioButtonIcon);
    buttonMario.setIconSize(QSize(buttonSize, buttonSize));
    buttonMario.setFixedSize(buttonSize,buttonSize);

    objectButtonsHorizontalLayout.addWidget(&buttonBrick);
    objectButtonsHorizontalLayout.addWidget(&buttonBlock);
    objectButtonsHorizontalLayout.addWidget(&buttonWall);
    objectButtonsHorizontalLayout.addWidget(&buttonSecretBox);
    objectButtonsHorizontalLayout.addWidget(&buttonGoomba);
    objectButtonsHorizontalLayout.addWidget(&buttonTurtle);
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

void LevelEditorWidget::handleButtonSave() { levelEditorController->saveLevel(); }

void LevelEditorWidget::handleButtonMenu() { levelEditorController->goBackToMainMenu(); }

void LevelEditorWidget::handleButtonQuit() { levelEditorController->quit(); }

void LevelEditorWidget::handleGridRadioButton() { levelEditorView->setShowLevelGrid(gridRadioButton.isChecked()); }
