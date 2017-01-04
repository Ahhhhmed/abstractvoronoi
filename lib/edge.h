#ifndef EDGE_H
#define EDGE_H

#include "descriptor.h"

class Edge
{
public:
    Edge(int p, int q, int r, int t);
    Edge(int p, int q, int r, int t, Descriptor* d);
private:
    int p,q,r,t; // sites
    Descriptor* d;
};

#endif // EDGE_H
