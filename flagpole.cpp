#include "flagpole.h"

#include "mario.h"

#include <QDebug>

Flagpole::Flagpole()
{
    currentTexture = loadTexture(":/resources/graphics/flagpole.png").scaled(BLOCSIZE, 11*BLOCSIZE);

    flag = new Inert();
    flag->setCurrentTexture(loadTexture(":/resources/graphics/flag.png").scaled(BLOCSIZE, BLOCSIZE));

    int hbwidth = BLOCSIZE/4;
    hitbox.setX((BLOCSIZE-hbwidth)/2);
    setHitboxWidth(hbwidth);
    hitbox.setHeight(11*BLOCSIZE);

    flagIsGoingDown = false;
}

void Flagpole::moveFlagOnPole()
{
    flag->moveTo(getHitbox().x()-flag->getCurrentTexture().width()+2, position.y()+BLOCSIZE/2);
}

void Flagpole::animate()
{
     if(flagIsGoingDown == true){
         flag->setPositionY(flag->getPosition().y() + 2);

         if(flag->getPosition().y() > getHitbox().y()+getHitbox().height()-2.2*BLOCSIZE){
             flagIsGoingDown = false;
         }
     }
}

void Flagpole::collisionOnLeftHandler(ObjectModel *o)
{
    Mario * mario = dynamic_cast<Mario *>(o);
    if(mario){
        flagIsGoingDown = true;
    }
}

void Flagpole::collisionOnRightHandler(ObjectModel *o)
{
    Mario * mario = dynamic_cast<Mario *>(o);
    if(mario){
        flagIsGoingDown = true;
    }
}

void Flagpole::collisionOnTopHandler(ObjectModel *o)
{
    Mario * mario = dynamic_cast<Mario *>(o);
    if(mario){
        flagIsGoingDown = true;
    }
}

void Flagpole::collisionOnBottomHandler(ObjectModel *o)
{
    Mario * mario = dynamic_cast<Mario *>(o);
    if(mario){
        flagIsGoingDown = true;
    }
}
