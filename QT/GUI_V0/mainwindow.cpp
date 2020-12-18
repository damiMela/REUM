#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //<<<<<<<<<<<<<-Web View->>>>>>>>>>>>>>//


    //<<<<<<<<<<<<<-TCP client setup->>>>>>>>>>>>>>//
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress("192.168.0.28"), 80);
    connect(socket, &QTcpSocket::connected, this, &MainWindow::connected_slot);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::newTCPData_slot);

    //<<<<<<<<<<<<<-button icons->>>>>>>>>>>>>>//
    ui->UpBtn->setIcon(QIcon("../GUI_V0/arrows/images/up.png"));
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


void MainWindow::connected_slot()
{

}

void MainWindow::newTCPData_slot()
{
    QByteArray datos = socket->readLine();
    socket->write(datos);
}

void MainWindow::on_UpBtn_clicked()
{
    socket->write(QByteArray("h\n\r"));
}

void MainWindow::on_camConnBtn_clicked()
{
    QString url_string = "http://";
    url_string.append(ui->IpCam_txb->toPlainText());
    url_string.append(":4747/video");
    qDebug()<< url_string << "\n";
    ui->camView->setUrl(QUrl(url_string));
    ui->camView->show();
}
