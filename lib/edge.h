#ifndef EDGE_H
#define EDGE_H

#include "descriptor.h"

class Vertex;

class Edge
{
public:
    Edge(int p, int q, int r, int t);
    Edge(int p,
         int q,
         int r,
         int t,
         Descriptor* d,
         Edge* twin,
         Edge* next,
         Edge* prev,
         Vertex* origin,
         int face);

    Vertex *getOrigin() const;
    void setOrigin(Vertex *value);

    Edge *getTwin() const;
    void setTwin(Edge *value);

    Edge *getNext() const;
    void setNext(Edge *value);

    Edge *getPrev() const;
    void setPrev(Edge *value);

    int getFace() const;
    void setFace(int value);

private:
    int p,q,r,t; // sites
    Descriptor* d;
    Edge *twin, *next, *prev;
    Vertex *origin;
    int face;
};

#endif // EDGE_H
