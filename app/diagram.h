#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "voronoiprovider.h"

#include <QWidget>
#include <abstractvoronoidiagram.h>

class Diagram : public QWidget
{
    Q_OBJECT
public:
    explicit Diagram(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
    void processNext();
    void prosessAll();

private:
    AbstractVoronoiDiagram diagram;
    VoronoiProvider provider;
};

#endif // DIAGRAM_H
