#ifndef LEVELEDITORWIDGET_H
#define LEVELEDITORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSlider>
#include <QRadioButton>

class LevelEditorView;
class LevelEditorEngine;

enum SelectedButton {NOBUTTON, BRICK, BLOCK, WALL, SECRETBOX, SMALLPIPE, MEDPIPE, BIGPIPE, FLAGPOLE, CASTLE, GOOMBA, TURTLE, FLYINGTURTLE, MARIO};
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
    QPushButton buttonBlock;
    QPushButton buttonWall;
    QPushButton buttonSecretBox;
    QPushButton buttonSmallPipe;
    QPushButton buttonMedPipe;
    QPushButton buttonBigPipe;
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
    void handleButtonBlock();
    void handleButtonWall();
    void handleButtonSecretBox();
    void handleButtonSmallPipe();
    void handleButtonMedPipe();
    void handleButtonBigPipe();
    void handleButtonFlagpole();
    void handleButtonCastle();
    void handleButtonGoomba();
    void handleButtonTurtle();
    void handleButtonTurtleFlying();
    void handleButtonMario();
};

#endif // LEVELEDITORWIDGET_H
