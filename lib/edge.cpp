#include "edge.h"

Edge::Edge(int p, int q, int r, int t)
    :p(p)
    ,q(q)
    ,r(r)
    ,t(t)
{

}

Edge::Edge(int p, int q, int r, int t, Descriptor* d)
    :p(p)
    ,q(q)
    ,r(r)
    ,t(t)
    ,d(d)
{

}
