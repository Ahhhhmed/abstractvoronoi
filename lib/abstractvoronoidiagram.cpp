#include "abstractvoronoidiagram.h"
#include "graphvisitor.h"

#include <tuple>
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

    history.source.push_back(new HistoryGraphNode(Descriptor(std::make_tuple(0,1,2,0), std::make_tuple(0,2,1,0))));
    history.source.push_back(new HistoryGraphNode(Descriptor(std::make_tuple(1,0,2,1), std::make_tuple(1,2,0,1))));
    history.source.push_back(new HistoryGraphNode(Descriptor(std::make_tuple(2,0,1,2), std::make_tuple(2,1,0,2))));

    auto vertex1 = new Vertex(1,0,2);
    auto vertex2 = new Vertex(2,0,1);

    auto edge11 = new Edge(1,2,0,2);
    auto edge12 = new Edge(0,2,1,2);
    auto edge21 = new Edge(1,0,2,0);
    auto edge22 = new Edge(2,0,1,0);
    auto edge31 = new Edge(2,1,0,1);
    auto edge32 = new Edge(0,1,2,1);

    edge11->twin = edge12;
    edge12->twin = edge11;
    edge21->twin = edge22;
    edge22->twin = edge21;
    edge31->twin = edge32;
    edge32->twin = edge31;

    edge11->origin = vertex1;
    edge11->next = edge21;
    edge11->prev = edge21;
    edge11->history_graph_node = history.source[2];

    edge12->origin = vertex2;
    edge12->next = edge32;
    edge12->prev = edge32;
    edge12->history_graph_node = history.source[2];

    edge21->origin = vertex2;
    edge21->next = edge11;
    edge21->prev = edge11;
    edge21->history_graph_node = history.source[0];

    edge22->origin = vertex2;
    edge22->next = edge31;
    edge22->prev = edge31;
    edge22->history_graph_node = history.source[0];

    edge31->origin = vertex2;
    edge31->next = edge22;
    edge31->prev = edge22;
    edge31->history_graph_node = history.source[1];

    edge32->origin = vertex1;
    edge32->next = edge12;
    edge32->prev = edge12;
    edge32->history_graph_node = history.source[1];

    vertex1->edge = edge22;
    vertex2->edge = edge21;

    diagram.edges.insert({edge11, edge12, edge21, edge22, edge31, edge32});
    diagram.vertices.insert({vertex1, vertex2});
}

class IntersectionVisitor : public GraphVisitor{
    std::set<HistoryGraphNode*> intersected;
    int current_site;
    BasicOperationProvider* basic_operation;
public:
    IntersectionVisitor(int current_site, BasicOperationProvider* basic_operation)
        :current_site(current_site), basic_operation(basic_operation) {}
    void VisitHistoryGraphNode(HistoryGraphNode *node){
        if (intersection_empty != basic_operation->basic_operation(std::get<2>(node->descriptor().a),
                                                     std::get<0>(node->descriptor().a),
                                                     std::get<1>(node->descriptor().a),
                                                     std::get<0>(node->descriptor().b),
                                                     current_site)
           ){
            intersected.insert(node);
            GraphVisitor::VisitHistoryGraphNode(node);
        }

    }
    std::set<HistoryGraphNode*> getIntersected() {return intersected;}
};

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
