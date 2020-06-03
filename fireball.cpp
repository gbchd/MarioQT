#include "fireball.h"

FireBall::FireBall(Direction direction)
{
    textures[0] = loadTexture(":/resources/graphics/items/fireball-0.png").scaled(BLOCSIZE/2, BLOCSIZE/2);
    textures[1] = loadTexture(":/resources/graphics/items/fireball-1.png").scaled(BLOCSIZE/2, BLOCSIZE/2);
    textures[2] = loadTexture(":/resources/graphics/items/fireball-2.png").scaled(BLOCSIZE/2, BLOCSIZE/2);
    textures[3] = loadTexture(":/resources/graphics/items/fireball-3.png").scaled(BLOCSIZE/2, BLOCSIZE/2);

    deathTextures[0] = loadTexture(":/resources/graphics/firework-0.png").scaled(BLOCSIZE/2, BLOCSIZE/2);
    deathTextures[1] = loadTexture(":/resources/graphics/firework-1.png").scaled(BLOCSIZE/1.15, BLOCSIZE/1.15);
    deathTextures[2] = loadTexture(":/resources/graphics/firework-2.png").scaled(BLOCSIZE, BLOCSIZE);
    deathFrameCounter = 0;

    setHitboxWidth(BLOCSIZE/2);
    setHitboxHeight(BLOCSIZE/2);
    setHitboxEntityWidth(BLOCSIZE/2);
    setHitboxEntityHeight(BLOCSIZE/2);

    hitbox.moveTo(position);
    hitboxEntity.moveTo(position);

    currentTexture = textures[0];
    textureNumber = 0;
    speed = 8;
    animationTimer.start();

    collidable = true;
    moving = true;
    if(direction == LEFT){
        velocity.setX(-speed);
    }
    else{
        velocity.setX(+speed);
    }

    gravity = bounceGravity;

    solid = false;

    speedLimit = 10;
}

void FireBall::advance()
{
    if(!dead){
        velocity.setY(velocity.y() + gravity);

        updateVelocity();
        applyVelocityLimit();

        moveTo(position+velocity);
    }
}

void FireBall::animate()
{
    if(deathFrameCounter > 2){
        deletable = true;
    }
    else if(dead){
        currentTexture = deathTextures[deathFrameCounter];

        // We center the explosion at every frame (since every frame is larger that the previous one)
        if(deathFrameCounter==0){
            moveTo(position.x() - (deathTextures[0].width()-textures[0].width())/2, position.y() - (deathTextures[0].width()-textures[0].width())/2);
        }
        else{
            moveTo(position.x() - (deathTextures[deathFrameCounter].width()-deathTextures[deathFrameCounter-1].width())/2, position.y() - (deathTextures[deathFrameCounter].width()-textures[deathFrameCounter-1].width())/2);
        }

        deathFrameCounter++;
    }
    else if(animationTimer.elapsed() > animationDelay){
        animationTimer.restart();
        if(textureNumber > 3){
            textureNumber = 0;
        }
        setCurrentTexture(textures[textureNumber]);
        textureNumber++;
    }
}

void FireBall::die()
{
    dead = true;
}

void FireBall::collisionByDefaultHandler(ObjectModel *o)
{
    die();
}

void FireBall::collisionOnBottomHandler(ObjectModel *o)
{
    velocity.setY(-6.4);
}

void FireBall::collisionOnTopHandler(ObjectModel *o)
{
    velocity.setY(-6.4);
}

void FireBall::collisionOnLeftHandler(ObjectModel *o)
{
    die();
}

void FireBall::collisionOnRightHandler(ObjectModel *o)
{
    die();
}
