#ifndef VERTEX_H
#define VERTEX_H

class Edge;

struct Vertex
{
    Vertex(int p, int q, int r, Edge* edge);

    int p,q,r; // defining sites
    Edge* edge;

};

#endif // VERTEX_H