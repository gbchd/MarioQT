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
    zValue = 0;
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
        currentTexture = loadTexture(":/resources/graphics/items/coin-0.png").scaled(BLOCSIZE*0.75, BLOCSIZE*0.75, Qt::KeepAspectRatio);
        break;
    case STARCOLLECTABLE:
        currentTexture = loadTexture(":/resources/graphics/items/starman-0.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        spawnAnimationTimer.start();
        break;
    case MUSHROOMCOLLECTABLE:
        currentTexture = loadTexture(":/resources/graphics/items/mushroom-red.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        movingDirection = RIGHT;
        spawnAnimationTimer.start();
        break;
    case FLOWERCOLLECTABLE:
        currentTexture = loadTexture(":/resources/graphics/items/fire-flower-0.png").scaled(BLOCSIZE, BLOCSIZE, Qt::KeepAspectRatio);
        spawnAnimationTimer.start();
        break;
    default:
        break;
    }
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
    handleCollisionWithObject(o);
}

void CollectableItem::collisionOnRightHandler(ObjectModel *o)
{
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
