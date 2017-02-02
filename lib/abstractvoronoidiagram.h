#ifndef ABSTRACTVORONOIDIAGRAM_H
#define ABSTRACTVORONOIDIAGRAM_H

#include "historygraph.h"
#include "planargraph.h"
#include "basicoperationprovider.h"

#include <vector>

class AbstractVoronoiDiagram
{
public:
    AbstractVoronoiDiagram();
    AbstractVoronoiDiagram(BasicOperationProvider* provider);

    HistoryGraph& getHistory();

    PlanarGraph& getDiagram();

    BasicOperationProvider *getProvider() const;

    void initialize(BasicOperationProvider* provider);
    void proces_next_site();
    void process_all_sites();
    
private:
    HistoryGraph history;
    PlanarGraph diagram;
    BasicOperationProvider* provider;

    void connectWithTwin(HistoryGraphNode* &shortenedCurrentNode, Edge* &currentEdge, Edge* &shortenedCurrentEdge, int current_site, int &segmentInterior, bool currentNode);
    void finish_pass(int current_site, std::vector<Edge *> &twin_edges, Edge *&currentEdge, std::vector<Edge *> &edge_stack, BasicOperationOutput firstIntersectionType, BasicOperationOutput currentIntersectionType);

    int current_step, size;
    std::vector<int> sites;
};

#endif // ABSTRACTVORONOIDIAGRAM_H
