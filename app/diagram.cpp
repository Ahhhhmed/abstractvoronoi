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
    ,provider(new DefaultVoronoiProvider({QPointF(200,200),
                                          QPointF(130,200),
                                          QPointF(360,240),
                                          QPointF(154,141),
                                          QPointF(450, 200)},
                                         minX,minY,maxX,maxY))
{
    diagram.initialize(provider);
}

void Diagram::paintEvent(QPaintEvent *event)
{
       QPainter painter(this);

       for(Edge* edge: diagram.getDiagram().edges){
           provider->DrawEdge(edge, painter);
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
    QString fileName= QFileDialog::getOpenFileName(this, tr("Import"));
    if(fileName.length()){
        std::ifstream stream(fileName.toStdString());
        std::vector<QPointF> newSites;

        while(!stream.eof()){
            int x,y;
            stream >> x >> y;
            if(stream.eof()) break;
            newSites.push_back(QPointF(x,y));
        }

        provider = new DefaultVoronoiProvider(newSites,minX,minY,maxX,maxY);
        diagram.initialize(provider);
        update();
    }
}
