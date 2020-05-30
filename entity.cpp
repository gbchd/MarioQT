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

//PROBLEME AVEC LES COLLISIONS ENTRE ENTITE
void Entity::solveCollision(ObjectModel *o){
    QRectF thisHitbox;
    QRectF oHitbox;
    Entity * e = dynamic_cast<Entity *>(o);
    if(e){
        if(!isCollidableWithOtherEntities() || !e->isCollidableWithOtherEntities()){
            return;
        }
        thisHitbox = getHitboxEntity();
        oHitbox = e->getHitboxEntity();
    }
    else{
        thisHitbox = getHitbox();
        oHitbox = o->getHitbox();
    }


    /**
     * COLLISION RESOLUTION INSPIRED BY : https://hopefultoad.blogspot.com/2017/09/2d-aabb-collision-detection-and-response.html
     */

    // We calculate the previous position of the hitbox via the velocity.
    QRectF prevHitbox = thisHitbox;
    prevHitbox.moveTo(thisHitbox.topLeft() - velocity);

    QRectF intersection = thisHitbox.intersected(oHitbox);

    // We find out in which area was the previous hitbox
    // See this for more information : https://3.bp.blogspot.com/-ggebdmaQZ-0/WcDZchz2pzI/AAAAAAAAAZU/Y2huS7Ks2Ec-dMbX-c9fvuSTHXqrA619wCLcBGAs/s1600/collision%2Bquadrant%2Bchart.png
    bool top = false;
    bool right = false;
    bool bottom = false;
    bool left = false;

    if(prevHitbox.bottom() <= oHitbox.top()){
        top = true;
    }
    if(prevHitbox.left() >= oHitbox.right()){
        right = true;
    }
    if(prevHitbox.top() >= oHitbox.bottom()){
        bottom = true;
    }
    if(prevHitbox.right() <= oHitbox.left()){
        left = true;
    }

    // The slope of the two vector : velocity and the vector between the closest corner of the two objects.
    float slopeVelocity;
    float slopeCorner;

    // We handle the corner cases.
    if(top && left){
        slopeVelocity = (thisHitbox.top() - prevHitbox.bottom())/(thisHitbox.left() - prevHitbox.right());
        slopeCorner = (oHitbox.top() - prevHitbox.bottom())/(oHitbox.left() - prevHitbox.right());
        //Hit top side
        if(slopeVelocity < slopeCorner){
            left = false;
        }
        //Hit left side
        else{
            top = false;
        }
    }
    else if(top && right){
        slopeVelocity = (thisHitbox.top() - prevHitbox.bottom())/(thisHitbox.right() - prevHitbox.left());
        slopeCorner = (oHitbox.top() - prevHitbox.bottom())/(oHitbox.right() - prevHitbox.left());
        //Hit top side
        if(slopeVelocity > slopeCorner){
            right = false;
        }
        //Hit right side
        else{
            top = false;
        }
    }
    else if(right && bottom){
        slopeVelocity = (thisHitbox.bottom() - prevHitbox.top())/(thisHitbox.right() - prevHitbox.left());
        slopeCorner = (oHitbox.bottom() - prevHitbox.top())/(oHitbox.right() - prevHitbox.left());
        //Hit bottom side
        if(slopeVelocity < slopeCorner){
            right = false;
        }
        //Hit right side
        else{
            bottom = false;
        }
    }
    if(left && bottom){
        slopeVelocity = (thisHitbox.bottom() - prevHitbox.top())/(thisHitbox.left() - prevHitbox.right());
        slopeCorner = (oHitbox.bottom() - prevHitbox.top())/(oHitbox.left() - prevHitbox.right());
        //Hit bottom side
        if(slopeVelocity > slopeCorner){
            left = false;
        }
        //Hit left side
        else{
            bottom = false;
        }
    }


    //We move this object to the correct position
    if(top){
        moveTo(position.x(), oHitbox.top() - thisHitbox.height());
    }
    if(right){
        moveTo(position.x() + intersection.width(), position.y());
        //moveTo(oHitbox.right(), position.y()); Check ce qui va pas avec ça
    }
    if(bottom){
        moveTo(position.x(), oHitbox.bottom());
    }
    if(left){
        moveTo(position.x() - intersection.width(), position.y());
    }


    /*
     * CODE QUE JE GARDE AU CAS OU J'AI TOUT CASSE SANS M'EN RENDRE COMPTE
    QRectF intersection = thisHitbox.intersected(oHitbox);
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
    */
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
        //qDebug() << "Left";
        collisionOnLeftHandler(o);
        o->collisionOnRightHandler(this);
    }
    if(hitbox.right() == oHitbox.left()){
        //qDebug() << "Right";
        collisionOnRightHandler(o);
        o->collisionOnLeftHandler(this);
    }
    if(hitbox.top() == oHitbox.bottom()){
        //qDebug() << "Top";
        collisionOnTopHandler(o);
        o->collisionOnBottomHandler(this);
    }
    if(hitbox.bottom() == oHitbox.top()){
        //qDebug() << "Bottom";
        collisionOnBottomHandler(o);
        o->collisionOnTopHandler(this);
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



