#ifndef LEVELEDITORWIDGET_H
#define LEVELEDITORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSlider>
#include <QScrollArea>
#include <QImage>
#include <QPainter>
#include <QRadioButton>

class LevelEditorView;
class LevelEditorEngine;

enum SelectedButton {   NOBUTTON,
                        BRICK,
                        COINBRICK,
                        BLOCK,
                        WALL,
                        SECRETBOXMUSHROOM,
                        SECRETBOXFLOWER,
                        SECRETBOXSTAR,
                        SECRETBOXCOIN,
                        COINITEM,
                        SMALLPIPE,
                        MEDPIPE,
                        BIGPIPE,
                        BULLETBLASTER,
                        MEDTRAMPOLINE,
                        BIGTRAMPOLINE,
                        FLAGPOLE,
                        CASTLE,
                        GOOMBA,
                        TURTLE,
                        FLYINGTURTLE,
                        MARIO,
                        SMALLHILL,
                        BIGHILL,
                        SMALLBUSH,
                        MEDBUSH,
                        BIGBUSH,
                        SMALLCLOUD,
                        MEDCLOUD,
                        BIGCLOUD   };

enum MouseState {NOTPRESSED, LEFTCLICKPRESSED, RIGHTCLICKPRESSED};

class LevelEditorWidget : public QWidget
{
    Q_OBJECT

private:
    LevelEditorEngine * levelEditorEngine;
    LevelEditorView * levelEditorView;

    QPushButton buttonSave;
    QPushButton buttonMenu;
    QPushButton buttonClear;

    static const int buttonSize = 48;
    QPushButton buttonBrick;
    QPushButton buttonCoinBrick;
    QPushButton buttonBlock;
    QPushButton buttonWall;
    QPushButton buttonSecretBoxMushroom;
    QPushButton buttonSecretBoxFlower;
    QPushButton buttonSecretBoxStar;
    QPushButton buttonSecretBoxCoin;
    QPushButton buttonCoinItem;
    QPushButton buttonSmallPipe;
    QPushButton buttonMedPipe;
    QPushButton buttonBigPipe;
    QPushButton buttonBulletBlaster;
    QPushButton buttonMedTrampoline;
    QPushButton buttonBigTrampoline;
    QPushButton buttonFlagpole;
    QPushButton buttonCastle;
    QPushButton buttonGoomba;
    QPushButton buttonTurtle;
    QPushButton buttonFlyingTurtle;
    QPushButton buttonMario;
    QPushButton buttonSmallHill;
    QPushButton buttonBigHill;
    QPushButton buttonSmallBush;
    QPushButton buttonMedBush;
    QPushButton buttonBigBush;
    QPushButton buttonSmallCloud;
    QPushButton buttonMedCloud;
    QPushButton buttonBigCloud;

    QRadioButton gridRadioButton;

    QGridLayout mainGridLayout;
    QHBoxLayout firstHorizontalLayout;
    QVBoxLayout menuVerticalLayout;

    QWidget buttonsWidget;
    QScrollArea buttonScrollArea;
    QHBoxLayout objectButtonsHorizontalLayout;

    QWidget gameDisplayContainerWidget;

    QSlider slider;

public:
    LevelEditorWidget();

    void setLevelEditorEngine(LevelEditorEngine * lee) { levelEditorEngine = lee; }
    void setLevelEditorView(LevelEditorView * lev);

private slots:
    void handleButtonSave();
    void handleButtonMenu();
    void handleButtonClear();
    void handleGridRadioButton();

    void handleButtonBrick();
    void handleButtonCoinBrick();
    void handleButtonBlock();
    void handleButtonWall();
    void handleButtonSecretBoxMushroom();
    void handleButtonSecretBoxFlower();
    void handleButtonSecretBoxStar();
    void handleButtonSecretBoxCoin();
    void handleButtonCoinItem();
    void handleButtonSmallPipe();
    void handleButtonMedPipe();
    void handleButtonBigPipe();
    void handleButtonBulletBlaster();
    void handleButtonMedTrampoline();
    void handleButtonBigTrampoline();
    void handleButtonFlagpole();
    void handleButtonCastle();
    void handleButtonGoomba();
    void handleButtonTurtle();
    void handleButtonTurtleFlying();
    void handleButtonMario();
    void handleButtonSmallHill();
    void handleButtonBigHill();
    void handleButtonSmallBush();
    void handleButtonMedBush();
    void handleButtonBigBush();
    void handleButtonSmallCloud();
    void handleButtonMedCloud();
    void handleButtonBigCloud();

    void handleSliderValueChange(int value);
};

#endif // LEVELEDITORWIDGET_H
