#ifndef VORONOIPROVIDER_H
#define VORONOIPROVIDER_H

#include <basicoperationprovider.h>
#include <edge.h>
#include <QPainter>

class VoronoiProvider : public BasicOperationProvider
{
public:
    VoronoiProvider();

    BasicOperationOutput basic_operation(int p, int r, int q, int t, int s) override;
    int number_of_sites() override;

    void DrawEdge(Edge* edge, QPainter& painter);
};

#endif // VORONOIPROVIDER_H
