#ifndef LEVELEDITORWIDGET_H
#define LEVELEDITORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSlider>

class LevelEditorController;
class LevelEditorView;
class LevelEditorEngine;

class LevelEditorWidget : public QWidget
{
    Q_OBJECT

private:
    LevelEditorController * levelEditorController;
    LevelEditorView * levelEditorView;

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

    QGridLayout mainGridLayout;
    QHBoxLayout firstHorizontalLayout;
    QVBoxLayout menuVerticalLayout;
    //QWidget menuWidget;
    QHBoxLayout objectButtonsHorizontalLayout;
    QWidget gameDisplayContainerWidget;

public:
    LevelEditorWidget();

    void setLevelEditorController(LevelEditorController * lec) { levelEditorController = lec; }
    void setLevelEditorView(LevelEditorView * lev);

private slots:
    void handleButtonSave();
    void handleButtonMenu();
    void handleButtonQuit();
};

#endif // LEVELEDITORWIDGET_H
