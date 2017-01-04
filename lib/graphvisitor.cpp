#include "graphvisitor.h"
#include "historygraphnode.h"

GraphVisitor::GraphVisitor()
{

}

void GraphVisitor::VisitHistoryGraphNode(HistoryGraphNode *node)
{
    for (size_t i = 0; i < node->children_number(); ++i) {
        node->child(i)->accept(*this);
    }
}
