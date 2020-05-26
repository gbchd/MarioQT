#include <QApplication>
#include <QDebug>
#include "gamecontroller.h"
#include "gameview.h"

#include "mainwindow.h"

#include "objectmodel.h"
#include "inert.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *mw = new MainWindow();
    mw->show();

    return a.exec();
}
