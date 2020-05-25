#include <QApplication>
#include <QDebug>
#include "gamecontroller.h"
#include "gameview.h"


#include "objectmodel.h"
#include "inert.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameController gamecontroller;
    GameView gameview;

    gamecontroller.setGameView(&gameview);
    gameview.setGameController(&gamecontroller);
    gamecontroller.setTickrate(60);

    int OS;
    #ifdef _WIN32 || _WIN64
    OS=0;
    #elif __APPLE__ || __MACH__
    OS=1;
    #endif

    if(OS==0){
        gamecontroller.setMapFilepath(":/resources/maps/alex.json");
        //"./maps/test.json"; // Relative path (A TESTER)
    }
    else if(OS==1){
        gamecontroller.setMapFilepath(":/resources/maps/alex.json");
        //"../../../../maps/test.json"; // Relative Path pour être dans le dossier build-Proj..... (Le dossier qui contient le .app)
    }
    else{
        qDebug() << "Not Supported OS";
        exit(1);
    }

    gamecontroller.start();
    gameview.show();

    return a.exec();
}
