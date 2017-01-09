#ifndef HISTORYGRAPHNODE_H
#define HISTORYGRAPHNODE_H

#include "descriptor.h"
#include "graphvisitor.h"
#include <vector>

class HistoryGraphNode
{
public:
    HistoryGraphNode(Descriptor d);
    Descriptor &descriptor();
    size_t children_number() const;
    HistoryGraphNode* child(size_t i) const;
    void addChild(HistoryGraphNode* g);

    void accept(GraphVisitor& v);
private:
    Descriptor d;
    std::vector<HistoryGraphNode*> children;
};

#endif // HISTORYGRAPHNODE_H
