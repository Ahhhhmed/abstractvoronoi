#ifndef HISTORYGRAPHNODE_H
#define HISTORYGRAPHNODE_H

#include "descriptor.h"
#include <vector>

class HistoryGraphNode
{
public:
    HistoryGraphNode(Descriptor d);
    Descriptor descriptor();
    size_t children_number();
    HistoryGraphNode* child(size_t i);
    void addChild(HistoryGraphNode* g);
private:
    Descriptor d;
    std::vector<HistoryGraphNode*> children;
};

#endif // HISTORYGRAPHNODE_H
