#include "diagram.h"

#include <QPainter>
#include <iostream>
#include <QFileDialog>
#include <fstream>

#include <random>
std::random_device rd;
std::mt19937 rng(rd());

#define minX 10
#define minY 10
#define maxX 650
#define maxY 460

Diagram::Diagram(QWidget *parent)
    : QWidget(parent)
{
    Random();
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

void Diagram::Random(){

    std::uniform_int_distribution<int> uniX(minX + 50,maxX - 50);
    std::uniform_int_distribution<int> uniY(minY + 50,maxY - 50);

    std::vector<QPointF> newSites;

    for(int i = 0, n = std::uniform_int_distribution<int>(4,15)(rng); i < n; i++){
        newSites.push_back(QPointF(uniX(rng),uniY(rng)));
    }

    provider = new DefaultVoronoiProvider(newSites,minX,minY,maxX,maxY);
    diagram.initialize(provider);
    update();
}
