#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H
#include <tuple>
#include <set>

typedef std::tuple<int, int, int, int> description_tuple;

class Descriptor
{
public:
    Descriptor(description_tuple a, description_tuple b);
    std::set<int> set() const;
private:
    description_tuple a,b;
};

#endif // DESCRIPTOR_H
