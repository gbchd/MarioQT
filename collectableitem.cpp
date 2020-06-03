#include "collectableitem.h"
#include "mario.h"

#include <QDebug>

CollectableItem::CollectableItem(TypeItem t, QPointF spawnerBlockPos)
{
    solid = false;
    typeItem = t;
    this->spawnerBlockPos = spawnerBlockPos;
    moveTo(spawnerBlockPos);
    gravity = 0;
    moving = false;
    itemWasPickedUpByMario = false;

    setHitboxEntityWidth(BLOCSIZE);
    setHitboxEntityHeight(BLOCSIZE);
    hitboxEntity.moveTo(position);
    setHitboxWidth(BLOCSIZE);
    setHitboxHeight(BLOCSIZE);
    hitbox.moveTo(position);

    switch(typeItem){
    case COINCOLLECTABLE:
        score = 200;
        currentTexture = loadTexture(":/resources/graphics/items/coin-0.png").scaled(BLOCSIZE*0.75, BLOCSIZE*0.75, Qt::KeepAspectRatio);
        break;
    case STARCOLLECTABLE:
        score = 1000;
        starTexture[0] = loadTexture(":/resources/graphics/items/starman-0.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        starTexture[1] = loadTexture(":/resources/graphics/items/starman-1.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        starTexture[2] = loadTexture(":/resources/graphics/items/starman-2.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        starTexture[3] = loadTexture(":/resources/graphics/items/starman-3.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        currentTexture = starTexture[0];
        spawnAnimationTimer.start();
        break;
    case MUSHROOMCOLLECTABLE:
        score = 1000;
        currentTexture = loadTexture(":/resources/graphics/items/mushroom-red.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        movingDirection = RIGHT;
        spawnAnimationTimer.start();
        break;
    case FLOWERCOLLECTABLE:
        score = 1000;
        flowerTexture[0] = loadTexture(":/resources/graphics/items/fire-flower-0.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        flowerTexture[1] = loadTexture(":/resources/graphics/items/fire-flower-1.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        flowerTexture[2] = loadTexture(":/resources/graphics/items/fire-flower-2.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        flowerTexture[3] = loadTexture(":/resources/graphics/items/fire-flower-3.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        currentTexture = flowerTexture[0];
        spawnAnimationTimer.start();
        break;
    default:
        break;
    }

    zValue = 2;
    animationTimer.start();
    currentTextureNumber=0;
}

void CollectableItem::advance()
{
    switch(typeItem){
        case STARCOLLECTABLE:
            // TODO JUMP AROUND
            break;
        case MUSHROOMCOLLECTABLE:
            groundHandler();
            if(!grounded){
                velocity.setY(velocity.y() + gravity);
            }
            else{
                velocity.setY(0);
            }
            updateVelocity();
            applyVelocityLimit();

            moveTo(position+velocity);
            break;
        default:
            break;
    }
}

void CollectableItem::animate()
{
    if(spawnAnimationTimer.isValid()){
        if(spawnAnimationTimer.elapsed() <= durationSpawnAnimation){
            moveTo(position.x(), spawnerBlockPos.y() - ((float)BLOCSIZE/(float)durationSpawnAnimation)*spawnAnimationTimer.elapsed());
        }
        else{
            spawnAnimationTimer.invalidate();

            // We start moving right if we are a mushroom
            moveTo(position.x(), spawnerBlockPos.y()-BLOCSIZE);
            moving = true;
            gravity = 5;
        }
    }

    if(typeItem == FLOWERCOLLECTABLE || typeItem == STARCOLLECTABLE){
        if(animationTimer.elapsed() > newAnimationDelay){
            animationTimer.restart();
            if(currentTextureNumber > 3){
                currentTextureNumber = 0;
            }
            if(typeItem == FLOWERCOLLECTABLE){
                setCurrentTexture(flowerTexture[currentTextureNumber]);
            }
            else if(typeItem == STARCOLLECTABLE){
                setCurrentTexture(starTexture[currentTextureNumber]);
            }
            currentTextureNumber++;
        }
    }
}

void CollectableItem::collisionByDefaultHandler(ObjectModel *o){
    handleCollisionWithObject(o);
}

void CollectableItem::collisionOnBottomHandler(ObjectModel *o)
{
    handleCollisionWithObject(o);
}

void CollectableItem::collisionOnLeftHandler(ObjectModel *o)
{
    movingDirection =  RIGHT;
    handleCollisionWithObject(o);
}

void CollectableItem::collisionOnRightHandler(ObjectModel *o)
{
    movingDirection  = LEFT;
    handleCollisionWithObject(o);
}

void CollectableItem::collisionOnTopHandler(ObjectModel *o)
{
    handleCollisionWithObject(o);
}

void CollectableItem::handleCollisionWithObject(ObjectModel *o)
{
    Mario * mario = dynamic_cast<Mario *>(o);
    if(mario != nullptr){
        deletable = true;
    }

}
