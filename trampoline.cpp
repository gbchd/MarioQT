#include "trampoline.h"

#include "mario.h"

#include <QDebug>

Trampoline::Trampoline(bool big)
{
    bigTrampoline = big;
    textureNumber = 0;

    textures[0] = QPixmap(loadTexture(":/resources/graphics/trampoline-0.png").scaled(BLOCSIZE, BLOCSIZE/2));
    textures[1] = QPixmap(loadTexture(":/resources/graphics/trampoline-1.png").scaled(BLOCSIZE, BLOCSIZE));
    textures[2] = QPixmap(loadTexture(":/resources/graphics/trampoline-2.png").scaled(BLOCSIZE, 3*BLOCSIZE/2));

    bigTrampolineSequence[0] = textures[1];
    bigTrampolineSequence[1] = textures[0];
    bigTrampolineSequence[2] = textures[1];
    bigTrampolineSequence[3] = textures[2];

    medTrampolineSequence[0] = textures[0];
    medTrampolineSequence[1] = textures[1];

    if(bigTrampoline){
        currentTexture = textures[2];
        animationDelay = 60;
    }
    else{
        animationDelay = 100;
        currentTexture = textures[1];
    }
}

void Trampoline::animate(){
    if(animationTimer.isValid() && animationTimer.elapsed() > animationDelay){
        animationTimer.restart();

        if(bigTrampoline){
            setCurrentTexture(bigTrampolineSequence[textureNumber]);
            if(textureNumber==0){ fromBigToMed(); }
            else if(textureNumber==1){ fromMedToSmall(); }
            else if(textureNumber==2){ fromSmallToMed(); }
            else if(textureNumber==3){ fromMedToBig(); }
        }
        else{
            setCurrentTexture(medTrampolineSequence[textureNumber]);
            if(textureNumber==0){ fromMedToSmall(); }
            if(textureNumber==1){ fromSmallToMed(); }
        }

        textureNumber++;

        if((bigTrampoline && textureNumber>3) || (!bigTrampoline && textureNumber>1)){
            animationTimer.invalidate();
            moveTo(spawnPos);
        }
    }
}

void Trampoline::fromSmallToMed()
{
    setHitboxHeight(2*BLOCSIZE/2);
    ObjectModel::moveTo(position.x(), position.y()-BLOCSIZE/2);
}

void Trampoline::fromMedToBig()
{
    setHitboxHeight(3*BLOCSIZE/2);
    ObjectModel::moveTo(position.x(), position.y()-BLOCSIZE/2);
}

void Trampoline::fromBigToMed()
{
    setHitboxHeight(2*BLOCSIZE/2);
    ObjectModel::moveTo(position.x(), position.y()+BLOCSIZE/2);
}

void Trampoline::fromMedToSmall()
{
    setHitboxHeight(1*BLOCSIZE/2);
    ObjectModel::moveTo(position.x(), position.y()+BLOCSIZE/2);
}

void Trampoline::collisionOnTopHandler(ObjectModel *o)
{
    Entity * entity = dynamic_cast<Entity *>(o);
    if(entity){
        if(animationTimer.isValid()){
            animationTimer.restart();
            if(bigTrampoline && textureNumber > 0){ animationDelay = 120; }
            else if( textureNumber > 0){ animationDelay = 120; }
        }
        else{
            animationTimer.start();
            textureNumber = 0;
            if(bigTrampoline){ animationDelay = 60; }
            else{ animationDelay = 100; }
        }
    }
}

void Trampoline::moveTo(QPointF newPosition)
{
    spawnPos = newPosition;
    if(bigTrampoline){
        ObjectModel::moveTo(QPointF(newPosition.x(), newPosition.y()+BLOCSIZE/2));
    }
    else{
        ObjectModel::moveTo(newPosition);
    }
}

void Trampoline::moveTo(float x, float y)
{
    spawnPos = QPointF(x, y);
    if(bigTrampoline){
        ObjectModel::moveTo(x, y+BLOCSIZE/2);
    }
    else{
        ObjectModel::moveTo(x, y);
    }
}
