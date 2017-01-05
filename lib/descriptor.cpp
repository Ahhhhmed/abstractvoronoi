#include "descriptor.h"
#include "edge.h"

Descriptor::Descriptor(description_tuple a, description_tuple b)
    :a(a)
    ,b(b)
    ,edge(nullptr)
{

}

std::set<int> Descriptor::set() const
{
    return std::set<int>({std::get<0>(a),
                             std::get<1>(a),
                             std::get<2>(a),
                             std::get<3>(a),
                             std::get<0>(b),
                             std::get<1>(b),
                             std::get<2>(b),
                             std::get<3>(b)
                         });
}

Edge *Descriptor::getEdge() const
{
    return edge;
}

void Descriptor::setEdge(Edge *value)
{
    edge = value;
}
