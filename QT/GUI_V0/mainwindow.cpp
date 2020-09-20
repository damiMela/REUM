#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    QWebEngineView *view = new QWebEngineView(ui->frame);
    view->load(QUrl("http://192.168.0.57:4747/video"));
    view->show();

    QGraphicsProxyWidget *w = scene->addWidget(view);
    w->setRotation(90);
    ui->graphicsView->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}

