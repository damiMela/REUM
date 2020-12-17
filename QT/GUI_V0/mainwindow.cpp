#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new QTcpServer(this);

    if(server->listen(QHostAddress::LocalHost, 26000) == false)
    {
        // Informar error
        close();
    }

    //connect(server, SIGNAL(newConnection()), this, SLOT(nuevaConexion()));
    connect(server, &QTcpServer::newConnection, this, &MainWindow::nuevaConexion);

    //<<<<<<<<<<<<<-Web View->>>>>>>>>>>>>>//
    ui->camView->setUrl(QUrl("http://192.168.0.17:4747/video"));
    ui->camView->show();

    //<<<<<<<<<<<<<-button icons->>>>>>>>>>>>>>//
    ui->UpBtn->setIcon(QIcon("../GUI_V0/images/up.png"));
    ui->UpBtn->setIconSize(ui->UpBtn->size());

    ui->DownBtn->setIcon(QIcon("../GUI_V0/images/down.png"));
    ui->DownBtn->setIconSize(ui->DownBtn->size());

    ui->LeftBtn->setIcon(QIcon("../GUI_V0/images/left.png"));
    ui->LeftBtn->setIconSize(ui->LeftBtn->size());

    ui->RightBtn->setIcon(QIcon("../GUI_V0/images/right.png"));
    ui->RightBtn->setIconSize(ui->RightBtn->size());

    //<<<<<<<<<<<<<-Table strech->>>>>>>>>>>>>>//
    ui->DataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nuevaConexion()
{
    // Tenemos un cliente nuevo
    cliente = server->nextPendingConnection();

    connect(cliente, &QTcpSocket::readyRead, this, &MainWindow::nuevosDatos);

    contador = 0;
}

void MainWindow::nuevosDatos()
{
    QByteArray datos = cliente->readLine();

    cliente->write(datos);
}
