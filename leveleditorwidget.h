#ifndef LEVELEDITORWIDGET_H
#define LEVELEDITORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSlider>
#include <QImage>
#include <QPainter>
#include <QRadioButton>

class LevelEditorView;
class LevelEditorEngine;

enum SelectedButton {NOBUTTON, BRICK, COINBRICK, BLOCK, WALL, SECRETBOXMUSHROOM, SECRETBOXFLOWER, SECRETBOXSTAR,SECRETBOXCOIN, SMALLPIPE, MEDPIPE, BIGPIPE, BULLETBLASTER, FLAGPOLE, CASTLE, GOOMBA, TURTLE, FLYINGTURTLE, MARIO};
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
    QPushButton buttonSmallPipe;
    QPushButton buttonMedPipe;
    QPushButton buttonBigPipe;
    QPushButton buttonBulletBlaster;
    QPushButton buttonFlagpole;
    QPushButton buttonCastle;
    QPushButton buttonGoomba;
    QPushButton buttonTurtle;
    QPushButton buttonFlyingTurtle;
    QPushButton buttonMario;

    QRadioButton gridRadioButton;

    QGridLayout mainGridLayout;
    QHBoxLayout firstHorizontalLayout;
    QVBoxLayout menuVerticalLayout;
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
    void handleButtonSmallPipe();
    void handleButtonMedPipe();
    void handleButtonBigPipe();
    void handleButtonBulletBlaster();
    void handleButtonFlagpole();
    void handleButtonCastle();
    void handleButtonGoomba();
    void handleButtonTurtle();
    void handleButtonTurtleFlying();
    void handleButtonMario();

    void handleSliderValueChange(int value);
};

#endif // LEVELEDITORWIDGET_H
