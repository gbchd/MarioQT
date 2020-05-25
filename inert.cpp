#include "inert.h"


Inert::Inert()
{
    collidable = true;
    walkable = true;
}

Inert::~Inert(){
    // delete les attributs alloués dynamiquement
}

void Inert::animate(){
    //Possible de mettre en place des animations pour les inert (cycle de pixmap)
}
