#ifndef HISTORYGRAPH_H
#define HISTORYGRAPH_H

#include <vector>
#include "historygraphnode.h"
#include "graphvisitor.h"

class HistoryGraph
{
public:
    HistoryGraph();
    void accept(GraphVisitor& v);
private:
    std::vector<HistoryGraphNode*> source;
};

#endif // HISTORYGRAPH_H
