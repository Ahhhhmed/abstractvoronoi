#include "diagram.h"

#include <QPainter>
#include <iostream>
#include <QFileDialog>
#include <fstream>

#define minX 10
#define minY 10
#define maxX 650
#define maxY 460

Diagram::Diagram(QWidget *parent)
    : QWidget(parent)
    ,provider({QPointF(180,200),
              QPointF(140,200),
              QPointF(160,50),
              QPointF(170,150)},
              minX,minY,maxX,maxY)
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

void Diagram::Import()
{
    QString fileName= QFileDialog::getOpenFileName(this, tr("Import"), ".");
    if(fileName.length()){
        std::ifstream stream(fileName.toStdString());
        std::vector<QPointF> newSites;

        while(!stream.eof()){
            int x,y;
            stream >> x >> y;
            newSites.push_back(QPointF(x,y));
        }

        diagram.initialize(new DefaultVoronoiProvider(newSites,minX,minY,maxX,maxY));
        update();
    }
}

void Diagram::About()
{

}
