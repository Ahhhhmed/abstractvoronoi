#include "historygraph.h"

HistoryGraph::HistoryGraph()
{

}

void HistoryGraph::accept(GraphVisitor &v)
{
    for (auto node: source) {
        node->accept(v);
    }
}
