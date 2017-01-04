#include "historygraphnode.h"

HistoryGraphNode::HistoryGraphNode(Descriptor d)
    :d(d)
{

}

Descriptor HistoryGraphNode::descriptor()
{
    return d;
}

size_t HistoryGraphNode::children_number()
{
    return children.size();
}

HistoryGraphNode *HistoryGraphNode::child(size_t i)
{
    return i< children.size()? children[i] : nullptr;
}

void HistoryGraphNode::addChild(HistoryGraphNode *g)
{
    children.push_back(g);
}
