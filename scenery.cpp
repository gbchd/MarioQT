#include "scenery.h"

Scenery::Scenery(TypeOfSceneryObject typeOfSceneryObject)
{
    objectSceneryType = typeOfSceneryObject;

    zValue = 1;

    switch (typeOfSceneryObject) {
    case SMALLHILLOBJECT:
        currentTexture = loadTexture(":/resources/graphics/hill-small.png");
        break;
    case BIGHILLOBJECT:
        currentTexture = loadTexture(":/resources/graphics/hill-big.png");
        break;
    case SMALLBUSHOBJECT:
        currentTexture = loadTexture(":/resources/graphics/bush-small.png");
        break;
    case MEDBUSHOBJECT:
        currentTexture = loadTexture(":/resources/graphics/bush-med.png");
        break;
    case BIGBUSHOBJECT:
        currentTexture = loadTexture(":/resources/graphics/bush-big.png");
        break;
    case SMALLCLOUDOBJECT:
        currentTexture = loadTexture(":/resources/graphics/cloud-small.png");
        break;
    case MEDCLOUDOBJECT:
        currentTexture = loadTexture(":/resources/graphics/cloud-med.png");
        break;
    case BIGCLOUDOBJECT:
        currentTexture = loadTexture(":/resources/graphics/cloud-big.png");
        break;
    case EMPTYSCENERYOBJECT:
    default:
        break;
    }

    collidable = false;
    walkable = false;
}
