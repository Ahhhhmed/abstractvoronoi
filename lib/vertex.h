#ifndef VERTEX_H
#define VERTEX_H

struct Edge;

struct Vertex
{
    Vertex();
    Vertex(int p, int q, int r);

    int p,q,r; // sites
    Edge* edge;

};

#endif // VERTEX_H
