#ifndef SCENERY_H
#define SCENERY_H

#include "inert.h"

enum TypeOfSceneryObject {  EMPTYSCENERYOBJECT,
                            SMALLHILLOBJECT,
                            BIGHILLOBJECT,
                            SMALLBUSHOBJECT,
                            MEDBUSHOBJECT,
                            BIGBUSHOBJECT,
                            SMALLCLOUDOBJECT,
                            MEDCLOUDOBJECT,
                            BIGCLOUDOBJECT    };

class Scenery : public Inert
{
private:
    TypeOfSceneryObject objectSceneryType;
public:
    Scenery(TypeOfSceneryObject typeOfSceneryObject);

    void animate() override;

    TypeOfSceneryObject getObjectSceneryType() { return objectSceneryType; }
};

#endif // SCENERY_H
