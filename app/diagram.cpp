#include "diagram.h"

#include <QPainter>

Diagram::Diagram(QWidget *parent) : QWidget(parent)
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
