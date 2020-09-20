#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWebEngineView *view = new QWebEngineView(this);
    view->setFixedSize(400, 350);
    view->load(QUrl("http://192.168.0.57:4747/video"));
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

