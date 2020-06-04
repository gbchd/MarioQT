#include "map.h"

Map::Map(){

}

Map::Map(QString filename){

    block_size = 32;

    QFile file_obj(filename);
    if(!file_obj.exists()){
        qDebug()<<"File does not exist"<<filename;
        exit(1);
    }
    if(!file_obj.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open "<<filename;
        exit(1);
    }

    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    QJsonDocument map = QJsonDocument::fromJson(json_bytes);
    QJsonObject jsonObject = map.object();

    name = jsonObject["name"].toString();
    creator = jsonObject["creator"].toString();
    creationDate = QDateTime::fromString(jsonObject["date"].toString(),"yyyy-MM-dd  HH:mm:ss");
    width = jsonObject["size"].toObject()["width"].toInt()*block_size;
    height = jsonObject["size"].toObject()["height"].toInt()*block_size;

    //modifier pour que ce soit un qPoint
    playerSpawnX = jsonObject["player"].toObject()["x"].toInt()*block_size;
    playerSpawnY = jsonObject["player"].toObject()["y"].toInt()*block_size;

    QJsonObject inertsObject = jsonObject["inerts"].toObject();
    foreach(const QString& key, inertsObject.keys()){
        addInert(inertsObject[key].toObject());
    }

    QJsonObject entitiesObject = jsonObject["entities"].toObject();
    foreach(const QString& key, entitiesObject.keys()){
        addEntity(entitiesObject[key].toObject());
    }
}

/**
 * @brief Map::addInert
 * @param inertObject
 *
 * Attention on alloue dynamiquement les inerts il faut donc penser à les delete()
 * lors de la destruction.
 */
void Map::addInert(QJsonObject inertObject){
    QString type = inertObject["type"].toString();
    if(type.compare("wall") == 0){
        Wall * wall = new Wall();

        int x = inertObject["x"].toInt();
        int y = inertObject["y"].toInt();

        wall->moveTo(x*block_size,y*block_size);


        //====================================
        //  /!\  On set le(s) sprite(s)  /!\
        //     (en fonction du w et du h)
        //====================================

        int w = inertObject["width"].toInt();
        int h = inertObject["height"].toInt();

        wall->setHitboxWidth(w*block_size);
        wall->setHitboxHeight(h*block_size);

        QPixmap newTexture = paintSurface(w, h,":/resources/graphics/blocs/wall.png");
        wall->setCurrentTexture(newTexture);

        inerts.append(wall);
    }
    else if(type.compare("block") == 0){
        Block * block = new Block();

        int x = inertObject["x"].toInt();
        int y = inertObject["y"].toInt();

        block->moveTo(x*block_size,y*block_size);

        int w = inertObject["width"].toInt();
        int h = inertObject["height"].toInt();

        block->setHitboxWidth(w*block_size);
        block->setHitboxHeight(h*block_size);

        QPixmap newTexture = paintSurface(w, h,":/resources/graphics/blocs/block.png");
        block->setCurrentTexture(newTexture);

        inerts.append(block);
    }
    else if(type.compare("box") == 0){
        Box * box = new Box();

        int x = inertObject["x"].toInt();
        int y = inertObject["y"].toInt();

        box->moveTo(x*block_size,y*block_size);

        int w = inertObject["width"].toInt();
        int h = inertObject["height"].toInt();

        box->setHitboxWidth(w*block_size);
        box->setHitboxHeight(h*block_size);

        QPixmap newTexture = paintSurface(w, h,":/resources/graphics/blocs/box-0.bmp");
        box->setCurrentTexture(newTexture);


        switch(inertObject["content"].toInt()){
        case 1:
            box->setBoxContent(MUSHROOMBOX);
            break;
        case 2:
            box->setBoxContent(FLOWERBOX);
            break;
        case 3:
            box->setBoxContent(COINBOX);
            break;
        case 4:
            box->setBoxContent(STARBOX);
            break;
        case 5:
            box->setBoxContent(USEDBOX);
            break;
        case 0:
        default:
            break;
        }

        // We transform the int corresponding to the content back into the enum object
        box->setBoxContent(static_cast<BoxContent>(inertObject["content"].toInt()));

        inerts.append(box);
    }
    else if(type.compare("pipe") == 0){
        Pipe * pipe;

        switch(inertObject["pipeType"].toInt()){
        case 1:
            pipe = new Pipe(SMALLPIPEOBJECT);
            break;
        case 2:
            pipe = new Pipe(MEDPIPEOBJECT);
            break;
        case 3:
            pipe = new Pipe(BIGPIPEOBJECT);
            break;
        case 0:
        default:
            pipe = new Pipe(NOPIPETYPE);
            break;
        }

        int x = inertObject["x"].toInt();
        int y = inertObject["y"].toInt();

        pipe->moveTo(x*block_size,y*block_size);

        inerts.append(pipe);
    }
    else if(type.compare("scenery") == 0){
        Scenery * scenery;

        switch(inertObject["sceneryType"].toInt()){
        case 1:
            scenery = new Scenery(SMALLHILLOBJECT);
            break;
        case 2:
            scenery = new Scenery(BIGHILLOBJECT);
            break;
        case 3:
            scenery = new Scenery(SMALLBUSHOBJECT);
            break;
        case 4:
            scenery = new Scenery(MEDBUSHOBJECT);
            break;
        case 5:
            scenery = new Scenery(BIGBUSHOBJECT);
            break;
        case 6:
            scenery = new Scenery(SMALLCLOUDOBJECT);
            break;
        case 7:
            scenery = new Scenery(MEDCLOUDOBJECT);
            break;
        case 8:
            scenery = new Scenery(BIGCLOUDOBJECT);
            break;
        case 0:
        default:
            scenery = new Scenery(EMPTYSCENERYOBJECT);
            break;
        }

        int x = inertObject["x"].toInt();
        int y = inertObject["y"].toInt();

        scenery->moveTo(x*block_size,y*block_size);

        inerts.append(scenery);
    }
    else if(type.compare("brick") == 0){
        Brick * brick = new Brick();

        int x = inertObject["x"].toInt();
        int y = inertObject["y"].toInt();

        brick->moveTo(x*block_size,y*block_size);

        int w = inertObject["width"].toInt();
        int h = inertObject["height"].toInt();

        brick->setHitboxWidth(w*block_size);
        brick->setHitboxHeight(h*block_size);

        QPixmap newTexture = paintSurface(w, h,":/resources/graphics/blocs/brick.bmp");
        brick->setCurrentTexture(newTexture);

        if(inertObject["isCoinBrick"].toInt()==1){
            brick->setBrickState(BRICKWILLGIVECOINONNEXTHIT);
        }

        inerts.append(brick);
    }
    else if(type.compare("billBlaster") == 0){
        BillBlaster * billBlaster = new BillBlaster();

        int x = inertObject["x"].toInt();
        int y = inertObject["y"].toInt();

        billBlaster->moveTo(x*block_size,y*block_size);

        billBlaster->setHitboxWidth(block_size);
        billBlaster->setHitboxHeight(2*block_size);

        inerts.append(billBlaster);
    }
    else if(type.compare("trampoline") == 0){
        Trampoline * trampoline = new Trampoline(inertObject["big"].toInt());

        float x = inertObject["x"].toDouble();
        float y = inertObject["y"].toDouble();

        trampoline->moveTo(x*block_size,y*block_size);

        trampoline->setHitboxWidth(block_size);

        if(trampoline->isTrampolineBig()){
            trampoline->moveTo(trampoline->getPosition().x(), trampoline->getPosition().y()-block_size);
            trampoline->setHitboxHeight(3*block_size/2);
        }
        else{
            trampoline->setHitboxHeight(block_size);
        }

        inerts.append(trampoline);
    }
    else if(type.compare("flagpole") == 0){
        Flagpole * flagpole = new Flagpole();

        float x = inertObject["x"].toDouble();
        float y = inertObject["y"].toDouble();

        flagpole->moveTo(x*block_size,y*block_size);

        inerts.append(flagpole);

        flagpole->moveFlagOnPole();
        inerts.append(flagpole->getFlag());

        Inert * castle = new Inert();
        castle->moveTo((x+5)*block_size, (y+7)*block_size);
        castle->setHitboxWidth(4*block_size);
        castle->setHitboxHeight(4*block_size);
        castle->setCurrentTexture(ObjectModel::loadTexture(":/resources/graphics/castle.png").scaled(block_size*4, block_size*4));
        inerts.append(castle);
    }
    else if(type.compare("movingplatform") == 0){
        MovingPlatform * movingPlatform = new MovingPlatform(inertObject["big"].toInt());

        float x = inertObject["x"].toDouble();
        float y = inertObject["y"].toDouble();

        movingPlatform->moveTo(x*block_size,y*block_size);
        movingPlatform->setSpawnPosition(movingPlatform->getPosition());

        inerts.append(movingPlatform);
    }
    else if(type.compare("firebar") == 0){
        Firebar * firebar = new Firebar();

        float x = inertObject["x"].toDouble();
        float y = inertObject["y"].toDouble();

        firebar->moveTo(x*block_size,y*block_size);

        inerts.append(firebar);

        FireBall * fb1 = new FireBall(Direction::RIGHT);
        FireBall * fb2 = new FireBall(Direction::RIGHT);
        FireBall * fb3 = new FireBall(Direction::RIGHT);
        FireBall * fb4 = new FireBall(Direction::RIGHT);
        FireBall * fb5 = new FireBall(Direction::RIGHT);
        FireBall * fb6 = new FireBall(Direction::RIGHT);

        fb1->setFireballOfFirebar(true);
        fb2->setFireballOfFirebar(true);
        fb3->setFireballOfFirebar(true);
        fb4->setFireballOfFirebar(true);
        fb5->setFireballOfFirebar(true);
        fb6->setFireballOfFirebar(true);

        firebar->setFireball(0, fb1);
        firebar->setFireball(1, fb2);
        firebar->setFireball(2, fb3);
        firebar->setFireball(3, fb4);
        firebar->setFireball(4, fb5);
        firebar->setFireball(5, fb6);

        entities.append(fb1);
        entities.append(fb2);
        entities.append(fb3);
        entities.append(fb4);
        entities.append(fb5);
        entities.append(fb6);
    }
    else if(type.compare("anotherBlock") == 0){
        //add another block
    }
    else{
        //erreur
    }
}

/**
 * @brief Map::addEntity
 * @param entityObject
 *
 * Attention on alloue dynamiquement les entities il faut donc penser à les delete()
 * lors de la destruction.
 */
void Map::addEntity(QJsonObject entityObject){
    QString type = entityObject["type"].toString();
    if(type.compare("goomba") == 0){
        qDebug() << type.compare("goomba");

        Goomba * goomba = new Goomba();
        int x = entityObject["x"].toInt();
        int y = entityObject["y"].toInt();
        goomba->moveTo(x*block_size, y*block_size-goomba->getCurrentTexture().height());

        entities.append(goomba);
    }
    else if(type.compare("koopa") == 0){

        Koopa * koopa = new Koopa();
        int x = entityObject["x"].toInt();
        int y = entityObject["y"].toInt();
        koopa->moveTo(x*block_size, y*block_size-koopa->getCurrentTexture().height());

        entities.append(koopa);

    }
    else if(type.compare("coin") == 0){

        Coin * coin = new Coin(false);
        int x = entityObject["x"].toInt();
        int y = entityObject["y"].toInt();
        coin->moveTo(x*block_size, y*block_size-coin->getCurrentTexture().height());

        entities.append(coin);

    }
    else{
        //erreur
    }
}

QPixmap Map::paintSurface(int w, int h, QString texturePath){
    QImage texture(texturePath);
    texture = texture.scaled(block_size,block_size);
    QPixmap pixmap = QPixmap(w*block_size,h*block_size);
    QPainter *paint = new QPainter(&pixmap);
    for(int col = 0; col < w; col++){
        for(int line = 0; line < h; line++){
            QPoint position(col*block_size, line*block_size);
            paint->drawImage(position,texture);
        }
    }
    return pixmap;
}
