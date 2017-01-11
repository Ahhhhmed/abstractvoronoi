#include "voronoiprovider.h"
#include <tuple>

VoronoiProvider::VoronoiProvider()
{

}

BasicOperationOutput VoronoiProvider::basic_operation(int p, int r, int q, int t, int s)
{

}

int VoronoiProvider::number_of_sites()
{
    return 2;
}

void VoronoiProvider::DrawEdge(Edge *edge, QPainter &painter)
{
    std::tuple<int,int,int,int> e = std::make_tuple(edge->p,edge->r,edge->q,edge->t);
    QPointF center(160,160);
    int radius(150);
    QPointF top(160,10);
    QPointF bot = QTransform().translate(center.x(),center.y()).rotate(180).translate(-center.x(),-center.y()).map(top);
    QPointF botRight = QTransform().translate(center.x(),center.y()).rotate(120).translate(-center.x(),-center.y()).map(top);
    QPointF botLeft = QTransform().translate(center.x(),center.y()).rotate(240).translate(-center.x(),-center.y()).map(top);

    if (edge->p == 0 || edge->q == 0){
        painter.drawEllipse(center, radius, radius);
    } else {
        if(e == std::make_tuple(1,0,2,0) || e == std::make_tuple(2,0,1,0)){
            painter.drawLine(top, bot);
        }
        if(e == std::make_tuple(1,0,2,3) || e == std::make_tuple(2,3,1,0) || e == std::make_tuple(2,0,1,3) || e == std::make_tuple(1,3,2,0)){
            painter.drawLine(top, center);
        }
        if(e == std::make_tuple(1,0,3,2) || e == std::make_tuple(3,0,1,2) || e == std::make_tuple(1,2,3,0) || e == std::make_tuple(3,2,1,0)){
            painter.drawLine(center, botLeft);
        }
        if(e == std::make_tuple(2,0,3,1) || e == std::make_tuple(2,1,3,0) || e == std::make_tuple(3,0,2,1) || e == std::make_tuple(3,1,2,0)){
            painter.drawLine(center, botRight);
        }
    }
}
