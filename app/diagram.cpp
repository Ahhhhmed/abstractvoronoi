#include "diagram.h"

#include <QPainter>

Diagram::Diagram(QWidget *parent)
    : QWidget(parent)
    ,provider({QPointF(180,200),
              QPointF(140,200),
              QPointF(160,150),
              QPointF(160,50)},
              10,10,310,310)
{
    diagram.initialize(&provider);
}

void Diagram::paintEvent(QPaintEvent *event)
{
       QPainter painter(this);

       for(Edge* edge: diagram.getDiagram().edges){
           provider.DrawEdge(edge, painter);
       }
}

void Diagram::processNext()
{
    diagram.proces_next_site();
    update();
}

void Diagram::prosessAll()
{
    diagram.process_all_sites();
    update();
}
