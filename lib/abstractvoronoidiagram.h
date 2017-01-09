#ifndef ABSTRACTVORONOIDIAGRAM_H
#define ABSTRACTVORONOIDIAGRAM_H

#include "historygraph.h"
#include "planargraph.h"
#include "basicoperationprovider.h"

#include <vector>

class AbstractVoronoiDiagram
{
public:
    AbstractVoronoiDiagram(AbstractVoronoiDiagram const&) = delete;
    void operator=(AbstractVoronoiDiagram const&) = delete;

    static AbstractVoronoiDiagram &instance();

    HistoryGraph& getHistory();

    PlanarGraph& getDiagram();

    BasicOperationProvider *getProvider() const;

    void initialize(BasicOperationProvider* provider);
    void proces_next_site();
    void process_all_sites();
private:
    AbstractVoronoiDiagram();

    HistoryGraph history;
    PlanarGraph diagram;
    BasicOperationProvider* provider;

    int current_step, size;
    std::vector<int> sites;
};

#endif // ABSTRACTVORONOIDIAGRAM_H
