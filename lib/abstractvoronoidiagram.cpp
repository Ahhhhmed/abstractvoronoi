#include "abstractvoronoidiagram.h"

#include <algorithm>
#include <numeric>

AbstractVoronoiDiagram &AbstractVoronoiDiagram::instance()
{
    static AbstractVoronoiDiagram inst;

    return inst;
}

AbstractVoronoiDiagram::AbstractVoronoiDiagram()
{

}

BasicOperationProvider* AbstractVoronoiDiagram::getProvider() const
{
    return provider;
}

void AbstractVoronoiDiagram::initialize(BasicOperationProvider *provider)
{
    this->provider = provider;

    size = provider->number_of_sites();

    current_step = 3;

    sites.resize(size);
    std::iota(sites.begin(), sites.end(), 0);
    std::random_shuffle(sites.begin(), sites.end());

    history.source.clear();
    diagram.edges.clear();
    diagram.vertices.clear();

    //intitialize starting structures...
}

void AbstractVoronoiDiagram::proces_next_site()
{

}

void AbstractVoronoiDiagram::process_all_sites()
{
    while(current_step<=size){
        proces_next_site();
    }
}

PlanarGraph AbstractVoronoiDiagram::getDiagram() const
{
    return diagram;
}

HistoryGraph AbstractVoronoiDiagram::getHistory() const
{
    return history;
}
