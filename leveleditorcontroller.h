#ifndef LEVELEDITORCONTROLLER_H
#define LEVELEDITORCONTROLLER_H

#include "leveleditorwidget.h"

class LevelEditorController
{
private:
    LevelEditorWidget * levelEditorWidget;

public:
    LevelEditorController();

    void setLevelEditorWidget(LevelEditorWidget * lew) { levelEditorWidget = lew; }
};

#endif // LEVELEDITORCONTROLLER_H
