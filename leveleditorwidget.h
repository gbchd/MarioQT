#ifndef LEVELEDITORWIDGET_H
#define LEVELEDITORWIDGET_H

#include <QWidget>

class LevelEditorController;

class LevelEditorWidget : public QWidget
{
    Q_OBJECT

private:
    LevelEditorController * levelEditorController;

public:
    LevelEditorWidget();

    void setLevelEditorController(LevelEditorController * lec) { levelEditorController = lec; }

private slots:
};

#endif // LEVELEDITORWIDGET_H
