#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QWidget>

class Diagram : public QWidget
{
    Q_OBJECT
public:
    explicit Diagram(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // DIAGRAM_H
