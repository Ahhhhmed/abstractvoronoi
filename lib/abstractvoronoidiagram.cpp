#include "abstractvoronoidiagram.h"
#include "graphvisitor.h"

#include <tuple>
#include <algorithm>
#include <numeric>
#include <stack>

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

    sites.resize(size-2);
    std::iota(sites.begin(), sites.end(), 3);
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
    history.source[2]->descriptor().setEdge(edge12);

    edge21->origin = vertex2;
    edge21->next = edge11;
    edge21->prev = edge11;
    edge21->history_graph_node = history.source[0];

    edge22->origin = vertex2;
    edge22->next = edge31;
    edge22->prev = edge31;
    edge22->history_graph_node = history.source[0];
    history.source[0]->descriptor().setEdge(edge22);

    edge31->origin = vertex2;
    edge31->next = edge22;
    edge31->prev = edge22;
    edge31->history_graph_node = history.source[1];

    edge32->origin = vertex1;
    edge32->next = edge12;
    edge32->prev = edge12;
    edge32->history_graph_node = history.source[1];
    history.source[1]->descriptor().setEdge(edge32);

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
        auto intersection_type = basic_operation->basic_operation(node->descriptor().edge->p, // std::get<2>(node->descriptor().a),
                                                                  node->descriptor().edge->r, //std::get<0>(node->descriptor().a),
                                                                  node->descriptor().edge->q, //std::get<1>(node->descriptor().a),
                                                                  node->descriptor().edge->t, //std::get<0>(node->descriptor().b),
                                                                  current_site);
        if (intersection_empty != intersection_type){
            if(node->children_number() == 0 && intersection_type != whole_edge){
                intersected.insert(node);
            }
            GraphVisitor::VisitHistoryGraphNode(node);
        }

    }
    std::set<HistoryGraphNode*> getIntersected() {return intersected;}
};

void AbstractVoronoiDiagram::connectWithTwin(HistoryGraphNode* &shortenedNode, Edge* &edge, Edge* &shortenedEdge, int current_site, int &segmentInterior, bool currentNode = true)
{
    if(edge->twin->twin == edge || segmentInterior == 1){
        if(segmentInterior != 1) edge->twin = shortenedEdge;

        if(currentNode){
            shortenedNode = new HistoryGraphNode(
                        Descriptor(std::make_tuple(current_site, edge->p, edge->q, current_site),
                                   std::make_tuple(edge->t, edge->q, edge->p, edge->t))
            );
        } else {
            shortenedNode = new HistoryGraphNode(
                        Descriptor(std::make_tuple(edge->r, edge->q, edge->p, edge->r),
                                   std::make_tuple(current_site, edge->p, edge->q, current_site))
            );
        }

        segmentInterior = 1;
        shortenedNode->descriptor().setEdge(shortenedEdge);
    } else {
        if(segmentInterior == 2){
            shortenedEdge->twin = edge->twin->twin->prev->prev;
            segmentInterior = 0;
        } else {
            shortenedEdge->twin = edge->twin->twin;
        }
        shortenedEdge->twin->twin = shortenedEdge;

        shortenedNode = shortenedEdge->twin->history_graph_node;
    }

    shortenedEdge->history_graph_node = shortenedNode;
}

void AbstractVoronoiDiagram::finish_pass(int current_site, std::vector<Edge*> &twin_edges, Edge* &currentEdge, std::vector<Edge*> &edge_stack, BasicOperationOutput firstIntersectionType, BasicOperationOutput currentIntersectionType)
{
    Edge* firstEdge = edge_stack[0];

    Edge* newEdge = new Edge(currentEdge->p,firstEdge->q,current_site,currentEdge->q);
    diagram.edges.insert(newEdge);
    Edge* newEdgeTwin = new Edge(current_site,currentEdge->q,currentEdge->p,firstEdge->q);
    diagram.edges.insert(newEdgeTwin);
    twin_edges.push_back(newEdgeTwin);

    newEdge->twin = newEdgeTwin;
    newEdgeTwin->twin = newEdge;

    HistoryGraphNode* newNode = new HistoryGraphNode(
                Descriptor(std::make_tuple(firstEdge->q, currentEdge->p, current_site, firstEdge->q),
                           std::make_tuple(currentEdge->q, current_site, currentEdge->p, currentEdge->q))
    );
    newEdge->history_graph_node  = newNode;
    newEdgeTwin->history_graph_node  = newNode;
    newNode->descriptor().setEdge(newEdge);


    Vertex* newVertex = new Vertex(currentEdge->p, currentEdge->q, current_site);
    diagram.vertices.insert(newVertex);

    Edge* shortenedCurrentEdge = new Edge(currentEdge->p,
                                          current_site,
                                          currentEdge->q,
                                          currentIntersectionType == two_components ? current_site : currentEdge->t);
    diagram.edges.insert(shortenedCurrentEdge);
    shortenedCurrentEdge->origin = newVertex;

    HistoryGraphNode* shortenedCurrentNode;
    int segment_int = 0;
    if(currentIntersectionType == segment_interior){
        segment_int = 2;
    }

    connectWithTwin(shortenedCurrentNode, currentEdge, shortenedCurrentEdge, current_site, segment_int, true);

    Edge* shortenedFirstEdge = new Edge(firstEdge->p,
                                        currentIntersectionType == two_components ? current_site : firstEdge->r,
                                        firstEdge->q,
                                        current_site);
    diagram.edges.insert(shortenedFirstEdge);
    shortenedFirstEdge->origin = firstEdge->origin;

    HistoryGraphNode* shortenedFirstNode;

    if(currentIntersectionType != segment_interior){
        segment_int = 0;
    }
    connectWithTwin(shortenedFirstNode, firstEdge, shortenedFirstEdge, current_site, segment_int, false);

    if(firstIntersectionType != two_components){
        if(firstEdge->prev == currentEdge){
            shortenedFirstEdge->prev = shortenedCurrentEdge;
        } else {
            shortenedFirstEdge->prev = firstEdge->prev;
            firstEdge->prev->next = shortenedFirstEdge;
        }
    }

    newEdge->prev = shortenedFirstEdge;
    shortenedFirstEdge->next = newEdge;

    newEdge->next = shortenedCurrentEdge;
    shortenedCurrentEdge->prev = newEdge;

    if(currentIntersectionType != two_components){
        if(currentEdge->next == firstEdge){
            shortenedCurrentEdge->next = shortenedFirstEdge;
        } else {
            shortenedCurrentEdge->next = currentEdge->next;
            currentEdge->next->prev = shortenedCurrentEdge;
        }
    }

    //firstEdge->history_graph_node->addChild(shortenedFirstNode);
    diagram.edges.erase(firstEdge);

    currentEdge->history_graph_node->addChild(shortenedCurrentNode);
    diagram.edges.erase(currentEdge);

    if(firstIntersectionType != segment_interior) edge_stack.push_back(currentEdge);
    for(auto e:edge_stack){
        e->history_graph_node->addChild(newNode);
        diagram.edges.erase(e);

        if(e != firstEdge){
            diagram.vertices.erase(e->origin);
        }
    }

    edge_stack.clear();
}

void AbstractVoronoiDiagram::proces_next_site()
{
    if (current_step > size) return;

    auto current_site = sites[(current_step++) - 3];
    IntersectionVisitor visitor(current_site, provider);
    history.accept(visitor);
    std::set<HistoryGraphNode*> intersected = visitor.getIntersected();

    std::set<Edge*> edge_set;
    for(auto node: intersected){
        edge_set.insert(node->descriptor().getEdge());
        edge_set.insert(node->descriptor().getEdge()->twin);
    }

    BasicOperationOutput firstIntersectionType;
    std::vector<Edge*> edge_stack;
    std::vector<Edge*> twin_edges;
    Edge* currentEdge = nullptr;
    while(!edge_set.empty() || currentEdge != nullptr){
        if(currentEdge == nullptr) {
            currentEdge = *edge_set.begin();
        }
        edge_set.erase(currentEdge);

        switch (provider->basic_operation(currentEdge->p,
                                          currentEdge->r,
                                          currentEdge->q,
                                          currentEdge->t,
                                          current_site)
                ){
        case segment_qtp:
            firstIntersectionType = segment_qtp;
            // fall through
        case whole_edge:
            edge_stack.push_back(currentEdge);
            currentEdge = currentEdge->next;
            break;
        case segment_prq:
            if(!edge_stack.empty()){
                finish_pass(current_site, twin_edges, currentEdge, edge_stack, firstIntersectionType, segment_prq);
            }
            currentEdge = nullptr;
            break;
        case segment_interior:
            edge_stack.push_back(currentEdge);
            finish_pass(current_site, twin_edges, currentEdge, edge_stack, segment_interior, segment_interior);
            currentEdge = nullptr;
            break;
        case two_components:
            if(!edge_stack.empty()){
                finish_pass(current_site, twin_edges, currentEdge, edge_stack, firstIntersectionType, two_components);
            } else {
                firstIntersectionType = segment_qtp;
                edge_stack.push_back(currentEdge);
                currentEdge = currentEdge->next;
            }
            break;
        default:
            currentEdge = nullptr;
            break;
        }
    }

    for(Edge* edge:twin_edges){
        Edge* nextEdge = edge->twin->prev->twin->prev->twin;
        edge->next = nextEdge;
        nextEdge->prev = edge;
    }
}

void AbstractVoronoiDiagram::process_all_sites()
{
    while(current_step<=size){
        proces_next_site();
    }
}

PlanarGraph &AbstractVoronoiDiagram::getDiagram()
{
    return diagram;
}

AbstractVoronoiDiagram::AbstractVoronoiDiagram(BasicOperationProvider *provider)
{
    initialize(provider);
}

HistoryGraph &AbstractVoronoiDiagram::getHistory()
{
    return history;
}
