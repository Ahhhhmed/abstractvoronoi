#include "edge.h"
#include "vertex.h"
#include "descriptor.h"

Edge::Edge()
{

}

Edge::Edge(int p, int q, int r, int t)
    :p(p)
    ,q(q)
    ,r(r)
    ,t(t)
    ,d(nullptr)
    ,twin(nullptr)
    ,next(nullptr)
    ,prev(nullptr)
    ,origin(nullptr)
{

}

int Edge::face()
{
    return p;
}
