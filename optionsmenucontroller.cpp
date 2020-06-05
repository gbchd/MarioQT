#include "optionsmenucontroller.h"
#include "mainwindow.h"

OptionsMenuController::OptionsMenuController()
{
    lastClickedOptionButton = NOBUTTONCLICKED;
}

void OptionsMenuController::launchMainMenu()
{
    mainWindow->goBackToMainMenu();
}

void OptionsMenuController::keyPressEventHandler(QKeyEvent *e)
{
    QKeySequence ks = QKeySequence(e->key());
    QString newKey = ks.toString();

    switch(lastClickedOptionButton){
            case JUMP: {
                optionsMenuWidget->setTextKeyJumpButton(newKey);
                settings->setKeyJump(e->key());
                break;
            }
            case MOVELEFT: {
                optionsMenuWidget->setTextKeyMoveLeftButton(newKey);
                settings->setKeyMoveLeft(e->key());
                break;
            }
            case MOVERIGHT: {
                optionsMenuWidget->setTextKeyMoveRightButton(newKey);
                settings->setKeyMoveRight(e->key());
                break;
            }
            case RUN: {
                optionsMenuWidget->setTextKeyRunButton(newKey);
                settings->setKeyRun(e->key());
                break;
            }
            case SHOOTFIREBALL: {
                optionsMenuWidget->setTextKeyShootFireBallButton(newKey);
                settings->setKeyShootFireBall(e->key());
                break;
            }
            default: {
                //DO NOTHING
                break;
            }
    }
    //Deselect the last button clicked
    lastClickedOptionButton = NOBUTTONCLICKED;
    //Go back to the original style sheet
    optionsMenuWidget->applyStyleSheet();
}

void OptionsMenuController::setSelectedButton(LastClickedOptionButton lcob, QString buttonEvent)
{
    optionsMenuWidget->changeStyleSheetOfTheSelectedButton(buttonEvent);
    lastClickedOptionButton = lcob;
}

void OptionsMenuController::setToDefaultKeyConfig()
{
    optionsMenuWidget->setTextKeyJumpButton("SPACE");
    settings->setKeyJump(Qt::Key_Space);

    optionsMenuWidget->setTextKeyRunButton("SHIFT");
    settings->setKeyRun(Qt::Key_Shift);

    optionsMenuWidget->setTextKeyMoveLeftButton("Q");
    settings->setKeyMoveLeft(Qt::Key_Q);

    optionsMenuWidget->setTextKeyMoveRightButton("D");
    settings->setKeyMoveRight(Qt::Key_D);

    optionsMenuWidget->setTextKeyShootFireBallButton("SHIFT");
    settings->setKeyShootFireBall(Qt::Key_Shift);

    optionsMenuWidget->applyStyleSheet();
    //Deselect the last button clicked
    lastClickedOptionButton = NOBUTTONCLICKED;
}


