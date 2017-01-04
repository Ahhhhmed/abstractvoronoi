#include "edge.h"
#include "vertex.h"

Edge::Edge(int p, int q, int r, int t)
    :p(p)
    ,q(q)
    ,r(r)
    ,t(t)
{

}

Edge::Edge(int p, int q, int r, int t, Descriptor* d, Edge *twin, Edge *next, Edge *prev, Vertex *origin, int face)
    :p(p)
    ,q(q)
    ,r(r)
    ,t(t)
    ,d(d)
    ,twin(twin)
    ,next(next)
    ,prev(prev)
    ,origin(origin)
    ,face(face)
{

}

Vertex *Edge::getOrigin() const
{
    return origin;
}

void Edge::setOrigin(Vertex *value)
{
    origin = value;
}

Edge *Edge::getTwin() const
{
    return twin;
}

void Edge::setTwin(Edge *value)
{
    twin = value;
}

Edge *Edge::getNext() const
{
    return next;
}

void Edge::setNext(Edge *value)
{
    next = value;
}

Edge *Edge::getPrev() const
{
    return prev;
}

void Edge::setPrev(Edge *value)
{
    prev = value;
}

int Edge::getFace() const
{
    return face;
}

void Edge::setFace(int value)
{
    face = value;
}
