#include "piranhaplant.h"

#include "fireball.h"

PiranhaPlant::PiranhaPlant()
{
    textures[0] = loadTexture(":/resources/graphics/mobs/piranha/piranha-0.png").scaled(1.3*16/24*BLOCSIZE, 1.3*BLOCSIZE, Qt::KeepAspectRatio);
    textures[1] = loadTexture(":/resources/graphics/mobs/piranha/piranha-1.png").scaled(1.3*16/24*BLOCSIZE, 1.3*BLOCSIZE, Qt::KeepAspectRatio);

    setHitboxWidth(1.3*16/24*BLOCSIZE);
    setHitboxHeight(1.3*BLOCSIZE);
    setHitboxEntityWidth(1.3*16/24*BLOCSIZE);
    setHitboxEntityHeight(1.3*BLOCSIZE);

    setCurrentTexture(textures[0]);

    animationTimer.start();
    textureIndex = 0;

    amplitude = 2*BLOCSIZE;
    travelDuration = 2000;
    travelDistance = amplitude / travelDuration;

    collidable = true;
    solid = false;

    zValue = 1;

    piranhaPlantState = PIRANHAGOINGUP;
}

void PiranhaPlant::advance()
{
    if(!travelTimer.isValid()){
        travelTimer.start();
    }

    if(travelTimer.elapsed() > travelDuration){
        switch(piranhaPlantState){
        case PIRANHAGOINGDOWN:
            piranhaPlantState = PIRANHAWAITINGDOWN;
            break;
        case PIRANHAGOINGUP:
            piranhaPlantState = PIRANHAWAITINGUP;
            break;
        case PIRANHAWAITINGDOWN:
            piranhaPlantState = PIRANHAGOINGUP;
            break;
        case PIRANHAWAITINGUP:
            piranhaPlantState = PIRANHAGOINGDOWN;
            break;
        default:
            break;
        }

        travelTimer.restart();
    }
    else{
        switch(piranhaPlantState){
        case PIRANHAGOINGDOWN:
            moveTo(spawnPosition.x(), spawnPosition.y() + travelDistance * travelTimer.elapsed());
            break;
        case PIRANHAGOINGUP:
            moveTo(spawnPosition.x(), spawnPosition.y() + amplitude - travelDistance * travelTimer.elapsed());
            break;
        case PIRANHAWAITINGDOWN:
            break;
        case PIRANHAWAITINGUP:
            break;
        default:
            break;
        }
    }
}

void PiranhaPlant::animate()
{
    if(animationTimer.elapsed() > animationDelay){
        animationTimer.restart();
        if(textureIndex > 1){
            textureIndex = 0;
        }

        setCurrentTexture(textures[textureIndex]);

        textureIndex++;
    }
}

void PiranhaPlant::collisionByDefaultHandler(ObjectModel *o)
{
    if(dynamic_cast<FireBall *>(o)){
        deletable = true;
    }
}

void PiranhaPlant::collisionOnBottomHandler(ObjectModel *o)
{
    if(dynamic_cast<FireBall *>(o)){
        deletable = true;
    }
}

void PiranhaPlant::collisionOnLeftHandler(ObjectModel *o)
{
    if(dynamic_cast<FireBall *>(o)){
        deletable = true;
    }
}

void PiranhaPlant::collisionOnRightHandler(ObjectModel *o)
{
    if(dynamic_cast<FireBall *>(o)){
        deletable = true;
    }
}

void PiranhaPlant::collisionOnTopHandler(ObjectModel *o)
{
    if(dynamic_cast<FireBall *>(o)){
        deletable = true;
    }
}
