#include "leveleditorwidget.h"

#include "leveleditorview.h"
#include "leveleditorengine.h"

#include <QDebug>

LevelEditorWidget::LevelEditorWidget()
{
    levelEditorView = nullptr;
    levelEditorEngine = nullptr;

    connect(&buttonSave, SIGNAL (clicked()), this, SLOT (handleButtonSave()));
    connect(&buttonMenu, SIGNAL (clicked()), this, SLOT (handleButtonMenu()));
    connect(&buttonClear, SIGNAL (clicked()), this, SLOT (handleButtonClear()));
    connect(&gridRadioButton, SIGNAL (toggled(bool)), this, SLOT (handleGridRadioButton()));

    connect(&buttonBrick, SIGNAL (clicked()), this, SLOT (handleButtonBrick()));
    connect(&buttonCoinBrick, SIGNAL (clicked()), this, SLOT (handleButtonCoinBrick()));
    connect(&buttonBlock, SIGNAL (clicked()), this, SLOT (handleButtonBlock()));
    connect(&buttonWall, SIGNAL (clicked()), this, SLOT (handleButtonWall()));
    connect(&buttonSecretBoxMushroom, SIGNAL (clicked()), this, SLOT (handleButtonSecretBoxMushroom()));
    connect(&buttonSecretBoxFlower, SIGNAL (clicked()), this, SLOT (handleButtonSecretBoxFlower()));
    connect(&buttonSecretBoxStar, SIGNAL (clicked()), this, SLOT (handleButtonSecretBoxStar()));
    connect(&buttonSecretBoxCoin, SIGNAL (clicked()), this, SLOT (handleButtonSecretBoxCoin()));
    connect(&buttonSmallPipe, SIGNAL (clicked()), this, SLOT (handleButtonSmallPipe()));
    connect(&buttonMedPipe, SIGNAL (clicked()), this, SLOT (handleButtonMedPipe()));
    connect(&buttonBigPipe, SIGNAL (clicked()), this, SLOT (handleButtonBigPipe()));
    connect(&buttonBulletBlaster, SIGNAL (clicked()), this, SLOT (handleButtonBulletBlaster()));
    connect(&buttonFlagpole, SIGNAL (clicked()), this, SLOT (handleButtonFlagpole()));
    connect(&buttonCastle, SIGNAL (clicked()), this, SLOT (handleButtonCastle()));
    connect(&buttonGoomba, SIGNAL (clicked()), this, SLOT (handleButtonGoomba()));
    connect(&buttonTurtle, SIGNAL (clicked()), this, SLOT (handleButtonTurtle()));
    connect(&buttonFlyingTurtle, SIGNAL (clicked()), this, SLOT (handleButtonTurtleFlying()));
    connect(&buttonMario, SIGNAL (clicked()), this, SLOT (handleButtonMario()));

    connect(&slider, SIGNAL (valueChanged(int)), this, SLOT (handleSliderValueChange(int)));

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

    QPixmap brickIcon(":/resources/graphics/blocs/brick.bmp");
    QIcon brickButtonIcon(brickIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBrick.setIcon(brickButtonIcon);
    buttonBrick.setIconSize(QSize(buttonSize, buttonSize));
    buttonBrick.resize(buttonSize,buttonSize);

    QImage coinIcon(":/resources/graphics/coin-1.png");
    QImage brickImage(":/resources/graphics/blocs/brick.bmp");
    QPixmap brickWithCoin(buttonSize,buttonSize);
    QPainter p1(&brickWithCoin);
    p1.drawImage(QPoint(0, 0), brickImage.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    p1.drawImage(QPoint(buttonSize*0.1, buttonSize*0.1), coinIcon.scaled(buttonSize*0.8, buttonSize*0.8, Qt::KeepAspectRatio));
    p1.end();

    QIcon brickWithCoinButtonIcon(brickWithCoin);
    buttonCoinBrick.setIcon(brickWithCoinButtonIcon);
    buttonCoinBrick.setIconSize(QSize(buttonSize, buttonSize));
    buttonCoinBrick.resize(buttonSize,buttonSize);

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

    QImage secretBoxIcon(":/resources/graphics/blocs/box-used.bmp");

    QImage mushroomIcon(":/resources/graphics/mushroom-red.png");
    QPixmap boxWithMushroom(secretBoxIcon.size());
    QPainter p2(&boxWithMushroom);
    p2.drawImage(QPoint(0, 0), secretBoxIcon);
    p2.drawImage(QPoint(2, 2), mushroomIcon.scaled(secretBoxIcon.size()*0.7));
    p2.end();

    QIcon secretBoxMushroomButtonIcon(boxWithMushroom.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonSecretBoxMushroom.setIcon(secretBoxMushroomButtonIcon);
    buttonSecretBoxMushroom.setIconSize(QSize(buttonSize, buttonSize));
    buttonSecretBoxMushroom.resize(buttonSize,buttonSize);

    QImage flowerIcon(":/resources/graphics/flower.png");
    QPixmap boxWithFlower(buttonSize,buttonSize);
    QPainter p3(&boxWithFlower);
    p3.drawImage(QPoint(0, 0), secretBoxIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    p3.drawImage(QPoint(6, 6), flowerIcon.scaled(buttonSize/1.3, buttonSize/1.3, Qt::KeepAspectRatio));
    p3.end();

    QIcon secretBoxFlowerButtonIcon(boxWithFlower);
    buttonSecretBoxFlower.setIcon(secretBoxFlowerButtonIcon);
    buttonSecretBoxFlower.setIconSize(QSize(buttonSize, buttonSize));
    buttonSecretBoxFlower.resize(buttonSize,buttonSize);

    QImage starIcon(":/resources/graphics/star.png");
    QPixmap boxWithStar(buttonSize,buttonSize);
    QPainter p4(&boxWithStar);
    p4.drawImage(QPoint(0, 0), secretBoxIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    p4.drawImage(QPoint(6, 6), starIcon.scaled(buttonSize/1.3, buttonSize/1.3, Qt::KeepAspectRatio));
    p4.end();

    QIcon secretBoxStarButtonIcon(boxWithStar);
    buttonSecretBoxStar.setIcon(secretBoxStarButtonIcon);
    buttonSecretBoxStar.setIconSize(QSize(buttonSize, buttonSize));
    buttonSecretBoxStar.resize(buttonSize,buttonSize);

    QPixmap boxWithCoin(buttonSize,buttonSize);
    QPainter p5(&boxWithCoin);
    p5.drawImage(QPoint(0, 0), secretBoxIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    p5.drawImage(QPoint(6, 6), coinIcon.scaled(buttonSize/1.3, buttonSize/1.3, Qt::KeepAspectRatio));
    p5.end();

    QIcon secretBoxCoinButtonIcon(boxWithCoin);
    buttonSecretBoxCoin.setIcon(secretBoxCoinButtonIcon);
    buttonSecretBoxCoin.setIconSize(QSize(buttonSize, buttonSize));
    buttonSecretBoxCoin.resize(buttonSize,buttonSize);

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

    QPixmap bulletBlasterIcon(":/resources/graphics/bill-blaster.png");
    QIcon bulletBlasterButtonIcon(bulletBlasterIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBulletBlaster.setIcon(bulletBlasterButtonIcon);
    buttonBulletBlaster.setIconSize(QSize(buttonSize, buttonSize));
    buttonBulletBlaster.resize(buttonSize,buttonSize);

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

    buttonScrollArea.setWidgetResizable(true);
    buttonsWidget.setLayout(&objectButtonsHorizontalLayout);
    buttonScrollArea.setWidget(&buttonsWidget);

    objectButtonsHorizontalLayout.addWidget(&buttonMario);
    objectButtonsHorizontalLayout.addWidget(&buttonBrick);
    objectButtonsHorizontalLayout.addWidget(&buttonCoinBrick);
    objectButtonsHorizontalLayout.addWidget(&buttonBlock);
    objectButtonsHorizontalLayout.addWidget(&buttonWall);
    objectButtonsHorizontalLayout.addWidget(&buttonSecretBoxMushroom);
    objectButtonsHorizontalLayout.addWidget(&buttonSecretBoxFlower);
    objectButtonsHorizontalLayout.addWidget(&buttonSecretBoxStar);
    objectButtonsHorizontalLayout.addWidget(&buttonSecretBoxCoin);
    objectButtonsHorizontalLayout.addWidget(&buttonGoomba);
    objectButtonsHorizontalLayout.addWidget(&buttonTurtle);
    objectButtonsHorizontalLayout.addWidget(&buttonFlyingTurtle);
    objectButtonsHorizontalLayout.addWidget(&buttonSmallPipe);
    objectButtonsHorizontalLayout.addWidget(&buttonMedPipe);
    objectButtonsHorizontalLayout.addWidget(&buttonBigPipe);
    objectButtonsHorizontalLayout.addWidget(&buttonBulletBlaster);
    objectButtonsHorizontalLayout.addWidget(&buttonFlagpole);
    objectButtonsHorizontalLayout.addWidget(&buttonCastle);

    firstHorizontalLayout.addWidget(&buttonScrollArea);

    buttonScrollArea.setMaximumHeight(90);
    buttonScrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    gridRadioButton.setText("Grid");
    firstHorizontalLayout.addWidget(&gridRadioButton);

    gameDisplayContainerWidget.resize(1280, 720);

    slider.setOrientation(Qt::Horizontal);
    mainGridLayout.addWidget(&slider, 2, 0);
}

void LevelEditorWidget::setLevelEditorView(LevelEditorView *lev){
    levelEditorView = lev;
    slider.setMaximum(levelEditorView->getlevelSize().width() - levelEditorView->getWindowSize().width()/2);
    slider.setMinimum(0 + levelEditorView->getWindowSize().width()/2);
    mainGridLayout.addWidget(levelEditorView, 1, 0);
}

void LevelEditorWidget::handleButtonSave() { levelEditorEngine->saveLevel(); }

void LevelEditorWidget::handleButtonMenu() { levelEditorEngine->goBackToMainMenu(); }

void LevelEditorWidget::handleButtonClear() { levelEditorEngine->clearMap(); }

void LevelEditorWidget::handleGridRadioButton() { levelEditorView->setShowLevelGrid(gridRadioButton.isChecked()); }

void LevelEditorWidget::handleButtonBrick() { levelEditorEngine->setSelectedButton(BRICK); }

void LevelEditorWidget::handleButtonCoinBrick() { levelEditorEngine->setSelectedButton(COINBRICK); }

void LevelEditorWidget::handleButtonBlock() { levelEditorEngine->setSelectedButton(BLOCK); }

void LevelEditorWidget::handleButtonWall() { levelEditorEngine->setSelectedButton(WALL); }

void LevelEditorWidget::handleButtonSecretBoxMushroom() { levelEditorEngine->setSelectedButton(SECRETBOXMUSHROOM); }

void LevelEditorWidget::handleButtonSecretBoxFlower() { levelEditorEngine->setSelectedButton(SECRETBOXFLOWER); }

void LevelEditorWidget::handleButtonSecretBoxStar() { levelEditorEngine->setSelectedButton(SECRETBOXSTAR); }

void LevelEditorWidget::handleButtonSecretBoxCoin() { levelEditorEngine->setSelectedButton(SECRETBOXCOIN); }

void LevelEditorWidget::handleButtonSmallPipe() { levelEditorEngine->setSelectedButton(SMALLPIPE); }

void LevelEditorWidget::handleButtonMedPipe() { levelEditorEngine->setSelectedButton(MEDPIPE); }

void LevelEditorWidget::handleButtonBigPipe() { levelEditorEngine->setSelectedButton(BIGPIPE); }

void LevelEditorWidget::handleButtonBulletBlaster() { levelEditorEngine->setSelectedButton(BULLETBLASTER); }

void LevelEditorWidget::handleButtonFlagpole() { levelEditorEngine->setSelectedButton(FLAGPOLE); }

void LevelEditorWidget::handleButtonCastle() { levelEditorEngine->setSelectedButton(CASTLE); }

void LevelEditorWidget::handleButtonGoomba() { levelEditorEngine->setSelectedButton(GOOMBA); }

void LevelEditorWidget::handleButtonTurtle() { levelEditorEngine->setSelectedButton(TURTLE); }

void LevelEditorWidget::handleButtonTurtleFlying() { levelEditorEngine->setSelectedButton(FLYINGTURTLE); }

void LevelEditorWidget::handleButtonMario() { levelEditorEngine->setSelectedButton(MARIO); }

void LevelEditorWidget::handleSliderValueChange(int value) {
    if(levelEditorEngine != nullptr){
        levelEditorEngine->changeCameraPosition(value);
    }
}
