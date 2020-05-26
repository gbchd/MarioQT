#include "entity.h"
#include <QDebug>

Entity::Entity()
{
    collidable = true;
    walkable = false;
    ground = nullptr;
}

Entity::~Entity(){
    // delete les attributs alloués dynamiquement
}

void Entity::bounce(){
    velocity.setY(-2*speed);
}

void Entity::groundHandler(){
    if(grounded && ground != nullptr){
        if(hitbox.bottom() < ground->getHitbox().y() ||
                hitbox.x() > ground->getHitbox().right() ||
                hitbox.right() < ground->getHitbox().x()){
            reactionNoMoreOnGround();
        }
    }
}

void Entity::setCurrentTexture(QPixmap texture){
    if(movingDirection == LEFT){
        texture = texture.transformed(QTransform().scale(-1,1));
    }
    ObjectModel::setCurrentTexture(texture);
}


void Entity::updateVelocity(){
    if(moving){ // Si on bouge
        if(movingDirection == LEFT){
            if(running){velocity.setX(-1.5*speed);}
            else{velocity.setX(-speed);}
        }
        if(movingDirection == RIGHT){
            if(running){velocity.setX(1.5*speed);}
            else{velocity.setX(speed);}
        }
    }
    else{ // Si on ne bouge pas
        velocity.setX(0);
    }
}


void Entity::applyVelocityLimit(){
    // LIMITATION DU VECTEUR VITESSE PAR LE SPEEDLIMIT
    // EN X ET EN Y POS
    if(velocity.x()>speedLimit){
        velocity.setX(speedLimit);
    }
    if(velocity.x()<-speedLimit){
        velocity.setX(-speedLimit);
    }
    if(velocity.y()>speedLimit){
        velocity.setY(speedLimit);
    }
}

void Entity::updatePosition(){
    if(position.x() + velocity.x() < 0){
        moveTo(0,position.y() + velocity.y());
    }
    else{
        moveTo(position + velocity);
    }
}

void Entity::reactionNoMoreOnGround(){
    grounded = false;
    ground = nullptr;
}


void Entity::startPhantom(){
    phantom = true;
    opacity = 0.5;
    collidableWithOtherEntities = false;
    timerPhantom.start();
}

void Entity::stopPhantom(){
    phantom = false;
    opacity = 1;
    collidableWithOtherEntities = true;
    timerPhantom.invalidate();
}

void Entity::moveTo(QPointF newPosition){
    QPointF distanceBetweenPosAndHitbox;
    distanceBetweenPosAndHitbox.setX(hitboxEntity.x() - position.x());
    distanceBetweenPosAndHitbox.setY(hitboxEntity.y() - position.y());
    ObjectModel::moveTo(newPosition);

    hitboxEntity.moveTo(position+distanceBetweenPosAndHitbox);
}

void Entity::moveTo(float x, float y){
    hitboxEntity.moveTo(x + hitboxEntity.x() - position.x(), y + hitboxEntity.y() - position.y());
    ObjectModel::moveTo(x,y);
}




bool Entity::isColliding(ObjectModel *o){
    QRectF hitbox;
    QRectF oHitbox;
    Entity * e = dynamic_cast<Entity *>(o);
    if(e){
        if(!isCollidableWithOtherEntities() || !e->isCollidableWithOtherEntities()){
            return false;
        }
        hitbox = getHitboxEntity();
        oHitbox = e->getHitboxEntity();
    }
    else{
        hitbox = getHitbox();
        oHitbox = o->getHitbox();
    }
    return(hitbox.right() > oHitbox.left() &&
           hitbox.left() < oHitbox.right() &&
           hitbox.bottom() > oHitbox.top() &&
           hitbox.top() < oHitbox.bottom());
}

void Entity::solveCollision(ObjectModel *o){
    QRectF hitbox;
    QRectF oHitbox;
    Entity * e = dynamic_cast<Entity *>(o);
    if(e){
        if(!isCollidableWithOtherEntities() || !e->isCollidableWithOtherEntities()){
            return;
        }
        hitbox = getHitboxEntity();
        oHitbox = e->getHitboxEntity();
    }
    else{
        hitbox = getHitbox();
        oHitbox = o->getHitbox();
    }
    QRectF intersection = hitbox.intersected(oHitbox);

    if(intersection.width() < intersection.height()){
        //Collision on x axis
        if(hitbox.x() < oHitbox.x()){
            //Collision à droite
            moveTo(position.x() - intersection.width(), position.y());
        }
        else{
            //Collision à gauche
            moveTo(position.x() + intersection.width(), position.y());
        }
    }
    else{
        //Collision on y axis
        if(hitbox.y() < oHitbox.y()){
            //Collision en bas
            moveTo(position.x(), position.y() - intersection.height());
        }
        else{
            //Collision en haut
            moveTo(position.x(), position.y() + intersection.height());
        }
    }
}

void Entity::collisionHandler(ObjectModel *o){
    // On vérifie si la collision a un impact
    if(!o->isCollidable() || !isCollidable()){
        return;
    }

    // On corrige la position de l'entité
    solveCollision(o);

    // On agit en fonction de la direction de la collision
    QRectF hitbox;
    QRectF oHitbox;
    Entity * e = dynamic_cast<Entity *>(o);
    if(e){
        if(!isCollidableWithOtherEntities() || !e->isCollidableWithOtherEntities()){
            return;
        }
        hitbox = getHitboxEntity();
        oHitbox = e->getHitboxEntity();
    }
    else{
        hitbox = getHitbox();
        oHitbox = o->getHitbox();
    }

    if(hitbox.left() == oHitbox.right()){
        collisionOnLeftHandler(o);
    }
    if(hitbox.right() == oHitbox.left()){
        collisionOnRightHandler(o);
    }
    if(hitbox.top() == oHitbox.bottom()){
        collisionOnTopHandler(o);
    }
    if(hitbox.bottom() == oHitbox.top()){
        collisionOnBottomHandler(o);
    }
}


void Entity::collisionOnLeftHandler(ObjectModel *o){
    //qDebug() << "Colliding LEFT";
    if(velocity.x() < 0){velocity.setX(0);}
}

void Entity::collisionOnRightHandler(ObjectModel *o){
    //qDebug() << "Colliding RIGHT";
    if(velocity.x() > 0){velocity.setX(0);}
}
void Entity::collisionOnTopHandler(ObjectModel *o){
    //qDebug() << "Colliding TOP";
    if(velocity.y()<0){velocity.setY(0);}
}
void Entity::collisionOnBottomHandler(ObjectModel *o){
    //qDebug() << "Colliding BOTTOM";
    if(velocity.y()>0){velocity.setY(0);}
    if(o->isWalkable()){
        grounded = true;
        ground = o;
    }
}



