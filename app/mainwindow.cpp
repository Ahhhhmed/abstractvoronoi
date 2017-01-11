#include "mainwindow.h"
#include "ui_mainwindow.h"

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
