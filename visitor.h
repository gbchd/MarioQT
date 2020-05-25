#ifndef VISITOR_H
#define VISITOR_H

class ObjectModel;

class Visitor
{
public:
    Visitor();
    virtual void visit(ObjectModel * e) = 0;
};

#endif // VISITOR_H
