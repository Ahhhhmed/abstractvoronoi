#include "planargraph.h"

PlanarGraph::PlanarGraph()
{

}

void PlanarGraph::addEdge(Edge *e)
{
    edges.insert(e);
}

void PlanarGraph::addVertex(Vertex *v)
{
    vertices.insert(v);
}

void PlanarGraph::removeEdge(Edge *e)
{
    edges.erase(e);
}

void PlanarGraph::removeVertex(Vertex *v)
{
    vertices.erase(v);
}
