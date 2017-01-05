#ifndef HISTORYGRAPH_H
#define HISTORYGRAPH_H

#include <vector>
#include "historygraphnode.h"
#include "graphvisitor.h"

struct HistoryGraph
{
    HistoryGraph();
    void accept(GraphVisitor& v);

    std::vector<HistoryGraphNode*> source;
};

#endif // HISTORYGRAPH_H
