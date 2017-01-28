#ifndef DEFAULTVORONOIPROVIDER_H
#define DEFAULTVORONOIPROVIDER_H

#include <basicoperationprovider.h>
#include <edge.h>
#include <QPainter>
#include <vector>
#include <utility>
#include <QPointF>

class DefaultVoronoiProvider : public BasicOperationProvider
{
public:
    DefaultVoronoiProvider(const std::vector<QPointF> &sites, int minX, int minY, int maxX, int maxY);

    BasicOperationOutput basic_operation(int p, int r, int q, int t, int s) override;
    int number_of_sites() override;

    void DrawEdge(Edge* edge, QPainter& painter);
private:
    QPointF circumcircle(int s0, int s1, int s2);

    bool is_closest_site(const QPointF& point, int s, int p1, int p2, int p3, int p4);
    bool is_closer_site(const QPointF& point, int s, int p);

    const std::vector<QPointF> sites;
    int minX, minY, maxX, maxY;
};

#endif // DEFAULTVORONOIPROVIDER_H
