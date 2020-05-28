#ifndef LEVELEDITORWIDGET_H
#define LEVELEDITORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSlider>
#include <QRadioButton>

class LevelEditorController;
class LevelEditorView;
class LevelEditorEngine;

class LevelEditorWidget : public QWidget
{
    Q_OBJECT

public:
    enum MouseState {UNKNOWN, BRICK, BLOCK, WALL, SECRETBOX, GOOMBA, TURTLE, MARIO};

private:
    LevelEditorController * levelEditorController;
    LevelEditorView * levelEditorView;

    QPushButton buttonSave;
    QPushButton buttonMenu;
    QPushButton buttonQuit;

    MouseState mouseState;

    static const int buttonSize = 48;
    QPushButton buttonBrick;
    QPushButton buttonBlock;
    QPushButton buttonWall;
    QPushButton buttonSecretBox;
    QPushButton buttonGoomba;
    QPushButton buttonTurtle;
    QPushButton buttonMario;

    QRadioButton gridRadioButton;

    QGridLayout mainGridLayout;
    QHBoxLayout firstHorizontalLayout;
    QVBoxLayout menuVerticalLayout;
    QHBoxLayout objectButtonsHorizontalLayout;
    QWidget gameDisplayContainerWidget;

public:
    LevelEditorWidget();

    void setLevelEditorController(LevelEditorController * lec) { levelEditorController = lec; }
    void setLevelEditorView(LevelEditorView * lev);
    MouseState inline getMouseState() { return mouseState; }

private slots:
    void handleButtonSave();
    void handleButtonMenu();
    void handleButtonQuit();
    void handleGridRadioButton();

    void handleButtonBrick() { mouseState = BRICK; }
    void handleButtonBlock() { mouseState = BLOCK; }
    void handleButtonWall() { mouseState = WALL; }
    void handleButtonSecretBox() { mouseState = SECRETBOX; }
    void handleButtonGoomba() { mouseState = GOOMBA; }
    void handleButtonTurtle() { mouseState = TURTLE; }
    void handleButtonMario() { mouseState = MARIO; }
};

#endif // LEVELEDITORWIDGET_H
