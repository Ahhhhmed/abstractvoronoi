#ifndef GRAPHVISITOR_H
#define GRAPHVISITOR_H

class HistoryGraphNode;

class GraphVisitor
{
public:
    GraphVisitor();
    virtual void VisitHistoryGraphNode(HistoryGraphNode* node);
};

#endif // GRAPHVISITOR_H
