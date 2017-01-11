#include "diagram.h"

#include <QPainter>

Diagram::Diagram(QWidget *parent) : QWidget(parent)
{

}

void Diagram::paintEvent(QPaintEvent *event)
{
       QPainter painter(this);

       QPoint p(10, 10);
       QPoint q(30, 30);

       painter.drawLine(p, q);
}
