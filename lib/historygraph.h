#ifndef HISTORYGRAPH_H
#define HISTORYGRAPH_H

#include <vector>
#include "historygraphnode.h"

class HistoryGraph
{
public:
    HistoryGraph();
private:
    std::vector<HistoryGraphNode*> source;
};

#endif // HISTORYGRAPH_H
