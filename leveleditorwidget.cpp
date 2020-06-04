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
    connect(&buttonSmallMovingPlatform, SIGNAL (clicked()), this, SLOT (handleButtonSmallMovingPlatform()));
    connect(&buttonLargeMovingPlatform, SIGNAL (clicked()), this, SLOT (handleButtonLargeMovingPlatform()));
    connect(&buttonFireBar, SIGNAL (clicked()), this, SLOT (handleButtonFireBar()));
    connect(&buttonCoinItem, SIGNAL (clicked()), this, SLOT (handleButtonCoinItem()));
    connect(&buttonSmallPipe, SIGNAL (clicked()), this, SLOT (handleButtonSmallPipe()));
    connect(&buttonMedPipe, SIGNAL (clicked()), this, SLOT (handleButtonMedPipe()));
    connect(&buttonBigPipe, SIGNAL (clicked()), this, SLOT (handleButtonBigPipe()));
    connect(&buttonBulletBlaster, SIGNAL (clicked()), this, SLOT (handleButtonBulletBlaster()));
    connect(&buttonMedTrampoline, SIGNAL (clicked()), this, SLOT (handleButtonMedTrampoline()));
    connect(&buttonBigTrampoline, SIGNAL (clicked()), this, SLOT (handleButtonBigTrampoline()));
    connect(&buttonFlagpole, SIGNAL (clicked()), this, SLOT (handleButtonFlagpole()));
    connect(&buttonGoomba, SIGNAL (clicked()), this, SLOT (handleButtonGoomba()));
    connect(&buttonTurtle, SIGNAL (clicked()), this, SLOT (handleButtonTurtle()));
    connect(&buttonFlyingTurtle, SIGNAL (clicked()), this, SLOT (handleButtonTurtleFlying()));
    connect(&buttonMario, SIGNAL (clicked()), this, SLOT (handleButtonMario()));
    connect(&buttonSmallHill, SIGNAL (clicked()), this, SLOT (handleButtonSmallHill()));
    connect(&buttonBigHill, SIGNAL (clicked()), this, SLOT (handleButtonBigHill()));
    connect(&buttonSmallBush, SIGNAL (clicked()), this, SLOT (handleButtonSmallBush()));
    connect(&buttonMedBush, SIGNAL (clicked()), this, SLOT (handleButtonMedBush()));
    connect(&buttonBigBush, SIGNAL (clicked()), this, SLOT (handleButtonBigBush()));
    connect(&buttonSmallCloud, SIGNAL (clicked()), this, SLOT (handleButtonSmallCloud()));
    connect(&buttonMedCloud, SIGNAL (clicked()), this, SLOT (handleButtonMedCloud()));
    connect(&buttonBigCloud, SIGNAL (clicked()), this, SLOT (handleButtonBigCloud()));

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

    buttonBrick.setIcon(QPixmap(":/resources/graphics/blocs/brick.bmp").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBrick.setIconSize(QSize(buttonSize, buttonSize));
    buttonBrick.resize(buttonSize,buttonSize);

    QImage coinIcon(":/resources/graphics/items/coin-0.png");
    QImage brickImage(":/resources/graphics/blocs/brick.bmp");
    QPixmap brickWithCoin(buttonSize,buttonSize);
    QPainter p1(&brickWithCoin);
    p1.drawImage(QPoint(0, 0), brickImage.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    p1.drawImage(QPoint(14, 6), coinIcon.scaled(buttonSize/1.3, buttonSize/1.3, Qt::KeepAspectRatio));
    p1.end();

    buttonCoinBrick.setIcon(QIcon(brickWithCoin));
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

    QImage mushroomIcon(":/resources/graphics/items/mushroom-red.png");
    QPixmap boxWithMushroom(secretBoxIcon.size());
    QPainter p2(&boxWithMushroom);
    p2.drawImage(QPoint(0, 0), secretBoxIcon);
    p2.drawImage(QPoint(2, 2), mushroomIcon.scaled(secretBoxIcon.size()*0.7));
    p2.end();

    QIcon secretBoxMushroomButtonIcon(boxWithMushroom.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonSecretBoxMushroom.setIcon(secretBoxMushroomButtonIcon);
    buttonSecretBoxMushroom.setIconSize(QSize(buttonSize, buttonSize));
    buttonSecretBoxMushroom.resize(buttonSize,buttonSize);

    QImage flowerIcon(":/resources/graphics/items/fire-flower-0.png");
    QPixmap boxWithFlower(buttonSize,buttonSize);
    QPainter p3(&boxWithFlower);
    p3.drawImage(QPoint(0, 0), secretBoxIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    p3.drawImage(QPoint(6, 6), flowerIcon.scaled(buttonSize/1.3, buttonSize/1.3, Qt::KeepAspectRatio));
    p3.end();

    buttonSecretBoxFlower.setIcon(QIcon(boxWithFlower));
    buttonSecretBoxFlower.setIconSize(QSize(buttonSize, buttonSize));
    buttonSecretBoxFlower.resize(buttonSize,buttonSize);

    QImage starIcon(":/resources/graphics/items/starman-0.png");
    QPixmap boxWithStar(buttonSize,buttonSize);
    QPainter p4(&boxWithStar);
    p4.drawImage(QPoint(0, 0), secretBoxIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    p4.drawImage(QPoint(8, 5), starIcon.scaled(buttonSize/1.3, buttonSize/1.3, Qt::KeepAspectRatio));
    p4.end();

    QIcon secretBoxStarButtonIcon(boxWithStar);
    buttonSecretBoxStar.setIcon(secretBoxStarButtonIcon);
    buttonSecretBoxStar.setIconSize(QSize(buttonSize, buttonSize));
    buttonSecretBoxStar.resize(buttonSize,buttonSize);

    QPixmap boxWithCoin(buttonSize,buttonSize);
    QPainter p5(&boxWithCoin);
    p5.drawImage(QPoint(0, 0), secretBoxIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    p5.drawImage(QPoint(14, 6), coinIcon.scaled(buttonSize/1.3, buttonSize/1.3, Qt::KeepAspectRatio));
    p5.end();

    QIcon secretBoxCoinButtonIcon(boxWithCoin);
    buttonSecretBoxCoin.setIcon(secretBoxCoinButtonIcon);
    buttonSecretBoxCoin.setIconSize(QSize(buttonSize, buttonSize));
    buttonSecretBoxCoin.resize(buttonSize,buttonSize);

    buttonSmallMovingPlatform.setIcon(QPixmap(":/resources/graphics/moving-platform-1.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonSmallMovingPlatform.setIconSize(QSize(buttonSize, buttonSize));
    buttonSmallMovingPlatform.resize(buttonSize,buttonSize);

    buttonLargeMovingPlatform.setIcon(QPixmap(":/resources/graphics/moving-platform-3.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonLargeMovingPlatform.setIconSize(QSize(buttonSize, buttonSize));
    buttonLargeMovingPlatform.resize(buttonSize,buttonSize);

    buttonFireBar.setIcon(QPixmap(":/resources/graphics/firebar.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonFireBar.setIconSize(QSize(buttonSize, buttonSize));
    buttonFireBar.resize(buttonSize,buttonSize);

    buttonCoinItem.setIcon(QPixmap(":/resources/graphics/items/coin-0.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonCoinItem.setIconSize(QSize(buttonSize, buttonSize));
    buttonCoinItem.resize(buttonSize,buttonSize);

    buttonSmallPipe.setIcon(QPixmap(":/resources/graphics/pipe-small.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonSmallPipe.setIconSize(QSize(buttonSize, buttonSize));
    buttonSmallPipe.resize(buttonSize,buttonSize);

    buttonMedPipe.setIcon(QPixmap(":/resources/graphics/pipe-med.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonMedPipe.setIconSize(QSize(buttonSize, buttonSize));
    buttonMedPipe.resize(buttonSize,buttonSize);

    buttonBigPipe.setIcon(QPixmap(":/resources/graphics/pipe-big.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBigPipe.setIconSize(QSize(buttonSize, buttonSize));
    buttonBigPipe.resize(buttonSize,buttonSize);

    buttonBulletBlaster.setIcon(QPixmap(":/resources/graphics/bill-blaster.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBulletBlaster.setIconSize(QSize(buttonSize, buttonSize));
    buttonBulletBlaster.resize(buttonSize,buttonSize);

    buttonMedTrampoline.setIcon(QPixmap(":/resources/graphics/trampoline-1.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonMedTrampoline.setIconSize(QSize(buttonSize, buttonSize));
    buttonMedTrampoline.resize(buttonSize,buttonSize);

    buttonBigTrampoline.setIcon(QPixmap(":/resources/graphics/trampoline-2.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBigTrampoline.setIconSize(QSize(buttonSize, buttonSize));
    buttonBigTrampoline.resize(buttonSize,buttonSize);

    buttonFlagpole.setIcon(QPixmap(":/resources/graphics/castle.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonFlagpole.setIconSize(QSize(buttonSize, buttonSize));
    buttonFlagpole.resize(buttonSize,buttonSize);

    buttonGoomba.setIcon(QPixmap(":/resources/graphics/mobs/goomba/goomba-0.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonGoomba.setIconSize(QSize(buttonSize, buttonSize));
    buttonGoomba.resize(buttonSize,buttonSize);

    buttonTurtle.setIcon(QPixmap(":/resources/graphics/mobs/turtle/turtle-walk-0.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonTurtle.setIconSize(QSize(buttonSize, buttonSize));
    buttonTurtle.resize(buttonSize,buttonSize);

    buttonFlyingTurtle.setIcon(QPixmap(":/resources/graphics/mobs/turtle_fly/turtle-fly-0.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonFlyingTurtle.setIconSize(QSize(buttonSize, buttonSize));
    buttonFlyingTurtle.resize(buttonSize,buttonSize);

    buttonMario.setIcon(QPixmap(":/resources/graphics/characters/mario/mario-small-stand.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonMario.setIconSize(QSize(buttonSize, buttonSize));
    buttonMario.resize(buttonSize,buttonSize);

    buttonSmallHill.setIcon(QPixmap(":/resources/graphics/hill-small.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonSmallHill.setIconSize(QSize(buttonSize, buttonSize));
    buttonSmallHill.resize(buttonSize,buttonSize);

    buttonBigHill.setIcon(QPixmap(":/resources/graphics/hill-big.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBigHill.setIconSize(QSize(buttonSize, buttonSize));
    buttonBigHill.resize(buttonSize,buttonSize);

    buttonSmallBush.setIcon(QPixmap(":/resources/graphics/bush-small.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonSmallBush.setIconSize(QSize(buttonSize, buttonSize));
    buttonSmallBush.resize(buttonSize,buttonSize);

    buttonMedBush.setIcon(QPixmap(":/resources/graphics/bush-med.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonMedBush.setIconSize(QSize(buttonSize, buttonSize));
    buttonMedBush.resize(buttonSize,buttonSize);

    buttonBigBush.setIcon(QPixmap(":/resources/graphics/bush-big.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBigBush.setIconSize(QSize(buttonSize, buttonSize));
    buttonBigBush.resize(buttonSize,buttonSize);

    buttonSmallCloud.setIcon(QPixmap(":/resources/graphics/cloud-small.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonSmallCloud.setIconSize(QSize(buttonSize, buttonSize));
    buttonSmallCloud.resize(buttonSize,buttonSize);

    buttonMedCloud.setIcon(QPixmap(":/resources/graphics/cloud-med.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonMedCloud.setIconSize(QSize(buttonSize, buttonSize));
    buttonMedCloud.resize(buttonSize,buttonSize);

    buttonBigCloud.setIcon(QPixmap(":/resources/graphics/cloud-big.png").scaled(buttonSize, buttonSize, Qt::KeepAspectRatio));
    buttonBigCloud.setIconSize(QSize(buttonSize, buttonSize));
    buttonBigCloud.resize(buttonSize,buttonSize);


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
    objectButtonsHorizontalLayout.addWidget(&buttonSmallMovingPlatform);
    objectButtonsHorizontalLayout.addWidget(&buttonLargeMovingPlatform);
    objectButtonsHorizontalLayout.addWidget(&buttonFireBar);
    objectButtonsHorizontalLayout.addWidget(&buttonCoinItem);
    objectButtonsHorizontalLayout.addWidget(&buttonGoomba);
    objectButtonsHorizontalLayout.addWidget(&buttonTurtle);
    objectButtonsHorizontalLayout.addWidget(&buttonFlyingTurtle);
    objectButtonsHorizontalLayout.addWidget(&buttonSmallPipe);
    objectButtonsHorizontalLayout.addWidget(&buttonMedPipe);
    objectButtonsHorizontalLayout.addWidget(&buttonBigPipe);
    objectButtonsHorizontalLayout.addWidget(&buttonBulletBlaster);
    objectButtonsHorizontalLayout.addWidget(&buttonMedTrampoline);
    objectButtonsHorizontalLayout.addWidget(&buttonBigTrampoline);
    objectButtonsHorizontalLayout.addWidget(&buttonFlagpole);
    objectButtonsHorizontalLayout.addWidget(&buttonSmallHill);
    objectButtonsHorizontalLayout.addWidget(&buttonBigHill);
    objectButtonsHorizontalLayout.addWidget(&buttonSmallBush);
    objectButtonsHorizontalLayout.addWidget(&buttonMedBush);
    objectButtonsHorizontalLayout.addWidget(&buttonBigBush);
    objectButtonsHorizontalLayout.addWidget(&buttonSmallCloud);
    objectButtonsHorizontalLayout.addWidget(&buttonMedCloud);
    objectButtonsHorizontalLayout.addWidget(&buttonBigCloud);

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

void LevelEditorWidget::handleButtonSmallMovingPlatform() { levelEditorEngine->setSelectedButton(SMALLMOVINGPLATFORM); }

void LevelEditorWidget::handleButtonLargeMovingPlatform() { levelEditorEngine->setSelectedButton(LARGEMOVINGPLATFORM); }

void LevelEditorWidget::handleButtonFireBar() { levelEditorEngine->setSelectedButton(FIREBAR); }

void LevelEditorWidget::handleButtonCoinItem() { levelEditorEngine->setSelectedButton(COINITEM); }

void LevelEditorWidget::handleButtonSmallPipe() { levelEditorEngine->setSelectedButton(SMALLPIPE); }

void LevelEditorWidget::handleButtonMedPipe() { levelEditorEngine->setSelectedButton(MEDPIPE); }

void LevelEditorWidget::handleButtonBigPipe() { levelEditorEngine->setSelectedButton(BIGPIPE); }

void LevelEditorWidget::handleButtonBulletBlaster() { levelEditorEngine->setSelectedButton(BULLETBLASTER); }

void LevelEditorWidget::handleButtonMedTrampoline() { levelEditorEngine->setSelectedButton(MEDTRAMPOLINE); }

void LevelEditorWidget::handleButtonBigTrampoline() { levelEditorEngine->setSelectedButton(BIGTRAMPOLINE); }

void LevelEditorWidget::handleButtonFlagpole() { levelEditorEngine->setSelectedButton(FLAGPOLE); }

void LevelEditorWidget::handleButtonGoomba() { levelEditorEngine->setSelectedButton(GOOMBA); }

void LevelEditorWidget::handleButtonTurtle() { levelEditorEngine->setSelectedButton(TURTLE); }

void LevelEditorWidget::handleButtonTurtleFlying() { levelEditorEngine->setSelectedButton(FLYINGTURTLE); }

void LevelEditorWidget::handleButtonMario() { levelEditorEngine->setSelectedButton(MARIO); }

void LevelEditorWidget::handleButtonSmallHill() { levelEditorEngine->setSelectedButton(SMALLHILL); }

void LevelEditorWidget::handleButtonBigHill() { levelEditorEngine->setSelectedButton(BIGHILL); }

void LevelEditorWidget::handleButtonSmallBush() { levelEditorEngine->setSelectedButton(SMALLBUSH); }

void LevelEditorWidget::handleButtonMedBush() { levelEditorEngine->setSelectedButton(MEDBUSH); }

void LevelEditorWidget::handleButtonBigBush() { levelEditorEngine->setSelectedButton(BIGBUSH); }

void LevelEditorWidget::handleButtonSmallCloud() { levelEditorEngine->setSelectedButton(SMALLCLOUD); }

void LevelEditorWidget::handleButtonMedCloud() { levelEditorEngine->setSelectedButton(MEDCLOUD); }

void LevelEditorWidget::handleButtonBigCloud() { levelEditorEngine->setSelectedButton(BIGCLOUD); }

void LevelEditorWidget::handleSliderValueChange(int value) {
    if(levelEditorEngine != nullptr){
        levelEditorEngine->changeCameraPosition(value);
    }
}
