#ifndef PLANARGRAPH_H
#define PLANARGRAPH_H

#include "edge.h"
#include "vertex.h"
#include <set>

struct PlanarGraph
{
    PlanarGraph();

    void addEdge(Edge* e);
    void addVertex(Vertex* v);

    void removeEdge(Edge* e);
    void removeVertex(Vertex* v);

    std::set<Edge*> edges;
    std::set<Vertex*> vertices;

};

#endif // PLANARGRAPH_H
