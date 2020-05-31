#ifndef PIPE_H
#define PIPE_H

#include "inert.h"

enum TypePipe {NOPIPETYPE, SMALLPIPEOBJECT, MEDPIPEOBJECT, BIGPIPEOBJECT};

class Pipe : public Inert
{
private:
    TypePipe typePipe;

public:
    Pipe(TypePipe t);

    TypePipe getTypePipe() { return typePipe; }
};

#endif // PIPE_H
