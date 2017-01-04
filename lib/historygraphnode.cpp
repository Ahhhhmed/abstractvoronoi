#include "historygraphnode.h"

HistoryGraphNode::HistoryGraphNode(Descriptor d)
    :d(d)
{

}

Descriptor HistoryGraphNode::descriptor() const
{
    return d;
}

size_t HistoryGraphNode::children_number() const
{
    return children.size();
}

HistoryGraphNode *HistoryGraphNode::child(size_t i) const
{
    return i< children.size()? children[i] : nullptr;
}

void HistoryGraphNode::addChild(HistoryGraphNode *g)
{
    children.push_back(g);
}

void HistoryGraphNode::accept(GraphVisitor &v)
{
    v.VisitHistoryGraphNode(this);
}
