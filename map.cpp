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
    if(!type.compare("wall")){
        Inert * block = new Inert();

        int x = inertObject["x"].toInt();
        int y = inertObject["y"].toInt();

        block->moveTo(x*block_size,y*block_size);


        //====================================
        //  /!\  On set le(s) sprite(s)  /!\
        //     (en fonction du w et du h)
        //====================================

        int w = inertObject["width"].toInt();
        int h = inertObject["height"].toInt();

        block->setHitboxWidth(w*block_size);
        block->setHitboxHeight(h*block_size);

        QPixmap newTexture = paintSurface(w, h , ":/resources/graphics/blocs/wall.png");
        block->setCurrentTexture(newTexture);

        inerts.append(block);
    }
    else if(type.compare("anotherBlock")){
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
    else if(type.compare("turtle") == 0){
        /*
        Turtle * turtle = new Turtle();
        int x = entityObject["x"].toInt();
        int y = entityObject["y"].toInt();
        turtle->setX(x*block_size);
        turtle->setY(y*block_size-turtle->getCurrentTexture().height());

        entities.append(turtle);
        */
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
