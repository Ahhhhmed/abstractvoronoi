#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H
#include <tuple>
#include <set>

struct Edge;
typedef std::tuple<int, int, int, int> description_tuple;

class Descriptor
{
public:
    Descriptor(description_tuple a, description_tuple b);
    std::set<int> set() const;

    Edge *getEdge() const;
    void setEdge(Edge *value);

private:
    description_tuple a,b;
    Edge* edge;
};

#endif // DESCRIPTOR_H
