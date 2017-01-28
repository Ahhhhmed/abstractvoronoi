#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    QList<QToolBar *> allToolBars = findChildren<QToolBar *>();
    for(QToolBar *tb: allToolBars) {
        removeToolBar(tb);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::About()
{
    QMessageBox::about(this,"About", "This is a demo application showing regular voronoi <br>diagrams bounded by a rectangle. <br><br> For more information see <a href=\"www.github.com\/ahhhhmed\/abstractvoronoi\">GitHub page</a>");
}
