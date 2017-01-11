#include "voronoiprovider.h"

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

    QPoint p(10, 10);
    QPoint q(30, 30);
    if (edge->p == 0 || edge->q == 0){
        painter.drawRect(QRectF(p,q));
    } else {
        painter.drawLine(p, q);
    }
}
