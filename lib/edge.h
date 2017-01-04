#ifndef EDGE_H
#define EDGE_H

#include "descriptor.h"

class Vertex;

struct Edge
{
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

    int p,q,r,t; // sites
    Descriptor* d;
    Edge *twin, *next, *prev;
    Vertex *origin;
    int face;
};

#endif // EDGE_H
