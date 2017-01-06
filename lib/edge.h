#ifndef EDGE_H
#define EDGE_H

class HistoryGraphNode;

struct Vertex;

struct Edge
{
    Edge();
    Edge(int p,
         int q,
         int r,
         int t);

    int p,q,r,t; // sites
    HistoryGraphNode* history_graph_node;
    Edge *twin, *next, *prev;
    Vertex *origin;
    int face();
};

#endif // EDGE_H
