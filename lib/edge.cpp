#include "edge.h"
#include "vertex.h"


Edge::Edge()
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
