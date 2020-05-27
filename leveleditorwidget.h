#ifndef LEVELEDITORWIDGET_H
#define LEVELEDITORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>

class LevelEditorController;

class LevelEditorWidget : public QWidget
{
    Q_OBJECT

private:
    LevelEditorController * levelEditorController;

    QPushButton buttonSave;
    QPushButton buttonMenu;
    QPushButton buttonQuit;

    static const int buttonSize = 48;
    QPushButton buttonBrick;
    QPushButton buttonBlock;
    QPushButton buttonWall;
    QPushButton buttonSecretBox;
    QPushButton buttonGoomba;
    QPushButton buttonTurtle;
    QPushButton buttonMario;

public:
    LevelEditorWidget();

    void setLevelEditorController(LevelEditorController * lec) { levelEditorController = lec; }

private slots:
    void handleButtonSave();
    void handleButtonMenu();
    void handleButtonQuit();
};

#endif // LEVELEDITORWIDGET_H
