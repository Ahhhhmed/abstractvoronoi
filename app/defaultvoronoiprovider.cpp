#include "defaultvoronoiprovider.h"

#include <tuple>
#include <utility>
#include <QLineF>

double Distance(const QPointF& p1, const QPointF& p2)
{
    return QLineF(p1,p2).length();
}

bool orientation(const QPointF& p1, const QPointF& p2, const QPointF& p3){
    QPointF a = p2-p1;
    QPointF b = p3-p1;
    return a.x() * b.y() > b.x() * a.y();
}

QPointF DefaultVoronoiProvider::circumcircle(int s0, int s1, int s2)
{
    if(s0 != 0 && s1 != 0 && s2 != 0 ){
        QPointF p0 = sites[s0-1];
        QPointF p1 = sites[s1-1];
        QPointF p2 = sites[s2-1];
        float dA, dB, dC, aux1, aux2, div;

        dA = p0.x() * p0.x() + p0.y() * p0.y();
        dB = p1.x() * p1.x() + p1.y() * p1.y();
        dC = p2.x() * p2.x() + p2.y() * p2.y();

        aux1 = (dA*(p2.y() - p1.y()) + dB*(p0.y() - p2.y()) + dC*(p1.y() - p0.y()));
        aux2 = -(dA*(p2.x() - p1.x()) + dB*(p0.x() - p2.x()) + dC*(p1.x() - p0.x()));
        div = (2*(p0.x()*(p2.y() - p1.y()) + p1.x()*(p0.y()-p2.y()) + p2.x()*(p1.y() - p0.y())));

        //    if(div == 0){
        //        return false;
        //    }

        return QPointF(aux1/div, aux2/div);
    }

    while(s0 != 0){
        int tmp = s2;
        s2 = s1;
        s1 = s0;
        s0 = tmp;
    }

    QPointF p1 = sites[s1-1];
    QPointF p2 = sites[s2-1];

    QLineF bisector = QLineF((p1 + p2) /2, p2).normalVector();

    QLineF upperLine = QLineF(minX,minY,maxX,minY);
    QLineF lowerLine = QLineF(minX,maxY,maxX,maxY);
    QLineF leftLine = QLineF(minX,minY,minX,maxY);
    QLineF rightLine = QLineF(maxX,minY,maxX,maxY);

    QPointF upperIntersection;
    QPointF lowerIntersection;
    QPointF leftIntersection;
    QPointF rightIntersection;

    if(bisector.intersect(upperLine, &upperIntersection) != QLineF::NoIntersection
            && upperIntersection.x() >=minX && upperIntersection.x() <= maxX
            && orientation(p1, p2,upperIntersection)){
        return upperIntersection;
    }
    if(bisector.intersect(lowerLine, &lowerIntersection) != QLineF::NoIntersection
            && lowerIntersection.x() >=minX && lowerIntersection.x() <= maxX
            && orientation(p1, p2,lowerIntersection)){
        return lowerIntersection;
    }
    if(bisector.intersect(leftLine, &leftIntersection) != QLineF::NoIntersection
            && leftIntersection.x() >=minY && leftIntersection.x() <= maxY
            && orientation(p1, p2,leftIntersection)){
        return leftIntersection;
    }
    // other case
//    if(bisector.intersect(rightLine, &rightIntersection) != QLineF::NoIntersection
//            && rightIntersection.x() >=minY && rightIntersection.x() <= maxY
//            && orientation(p1, p2,rightIntersection))

    bisector.intersect(rightLine, &rightIntersection);
    return rightIntersection;
}

DefaultVoronoiProvider::DefaultVoronoiProvider(const std::vector<QPointF> &sites, int minX, int minY, int maxX, int maxY)
    :sites(sites)
    ,minX(minX)
    ,minY(minY)
    ,maxX(maxX)
    ,maxY(maxY)
{

}

BasicOperationOutput DefaultVoronoiProvider::basic_operation(int p, int r, int q, int t, int s)
{
    QPointF prq = circumcircle(p, r, q);
    QPointF qtp = circumcircle(q, t, p);

    bool prq_closest = is_closest_site(prq, s, p, r, q, t);
    bool qtp_closest = is_closest_site(qtp, s, p, r, q, t);

    if(prq_closest && qtp_closest){
        return whole_edge;
    }
    if(prq_closest && !qtp_closest){
        return segment_prq;
    }
    if(qtp_closest && !prq_closest){
        return segment_qtp;
    }
    // other case
    return intersection_empty;
}

int DefaultVoronoiProvider::number_of_sites()
{
    return sites.size();
}

void DefaultVoronoiProvider::DrawEdge(Edge *edge, QPainter &painter)
{
    if(edge->p ==0 || edge->q == 0){
        painter.drawRect(minX, minY, (maxX-minX), (maxY-minY));
    } else {
        painter.drawLine(circumcircle(edge->p,edge->r,edge->q), circumcircle(edge->q, edge->t, edge->p));
        painter.drawEllipse(sites[edge->p-1], 5,5);
    }
}

bool DefaultVoronoiProvider::is_closest_site(const QPointF &point, int s, int p1, int p2, int p3, int p4)
{
    return is_closer_site(point, s, p1) &&
            is_closer_site(point, s, p2) &&
            is_closer_site(point, s, p3) &&
            is_closer_site(point, s, p4);
}

bool DefaultVoronoiProvider::is_closer_site(const QPointF &point, int s, int p)
{
    if(p==0) {
        return true;
    }
    if(s==0){
        return false;
    }
    return Distance(point, sites[s-1]) < Distance(point, sites[p-1]);

}
