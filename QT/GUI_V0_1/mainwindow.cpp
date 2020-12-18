#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

#define UPDATE_DATA_TIME 2000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->installEventFilter(this);
    qDebug() << "ready\n";

    //<<<<<<<<<<<<<-TCP client setup->>>>>>>>>>>>>>//
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress("192.168.0.28"), 80);
    connect(socket, &QTcpSocket::connected, this, &MainWindow::connected_slot);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::newTCPData_slot);
    dir = 's';

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
    ui->datTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

MainWindow::~MainWindow()
{
    delete ui;
}


//------------------------------------------------TCP-------------------------------------------//
void MainWindow::connected_slot()
{
    ui->datTable->setEnabled(true);
    ui->btnFrame->setEnabled(true);
    ui->velocitySlide->setEnabled(true);

    //<<<<<<<<<<<<<<-QTimer->>>>>>>>>>>>>>>>//
    QTimer *update_dir_timer = new QTimer(this);
    connect(update_dir_timer, &QTimer::timeout, this, &MainWindow::updateRobotDir);
    update_dir_timer->start(UPDATE_DATA_TIME);
}

void MainWindow::newTCPData_slot()
{
    static bool firstTime = false;
    QByteArray datos = socket->readLine();
    QString str_input = QString::fromStdString(datos.toStdString());
    QStringList input_list = str_input.split("#");

    if(input_list.count()> 1){
        if(!firstTime){
            ui->SaveDbBtn->setEnabled(true);
            firstTime = true;
        }

        input_list.pop_front();
        qDebug() << input_list[0] << "-----" << input_list[1] <<"\n";

        for(int i = 0; i < 1; i++){
            QByteArray d = input_list[i].toUtf8();
            updateTable(d[0], input_list[i+1]);
        }
    }

}

void MainWindow::sendTCPmsg(QString msg){
    QString send_msg = "#";
    send_msg.append(msg);
    send_msg.append("&");

    std::string str_msg = send_msg.toStdString();
    const char* char_msg = str_msg.c_str();
    socket->write(char_msg);
}

//---------------------------------------------KEY PRESS----------------------------------------//
void MainWindow::keyPressEvent(QKeyEvent *keyevent)
{
    int pressed_key = keyevent->key();

    if(pressed_key == Qt::Key_Up)           dir = 'f';
    else if(pressed_key == Qt::Key_Down)    dir = 'b';
    else if(pressed_key == Qt::Key_Left)    dir = 'l';
    else if(pressed_key == Qt::Key_Right)   dir = 'r';
}

void MainWindow::keyReleaseEvent(QKeyEvent *keyevent)
{
    int released_key = keyevent->key();
    if(released_key) dir = 's';
}


//-------------------------------------------UPDATE DATA----------------------------------------//
void MainWindow::updateRobotDir(){
    QString s = QString(dir);
    s.append(QString::number(ui->velocitySlide->value()));
    qDebug() << s << "\n";
    sendTCPmsg(s);
}

void MainWindow::updateTable(char itemChar, QString val)
{
    int itemIndex = 0;
    switch(itemChar){
        case 't':   itemIndex = 0;      break;
        case 'h':   itemIndex = 1;      break;
        case 'p':   itemIndex = 2;      break;
        default:    itemIndex = 0;      break;
    }

    if(ui->datTable->item(itemIndex, 0)){
         ui->datTable->item(itemIndex, 0)->setText(val);
         ui->datTable->update();
    }
    else{
        QTableWidgetItem *itemVal = new QTableWidgetItem(val);
        ui->datTable->setItem(itemIndex, 0, itemVal);
    }

}
//------------------------------------------BUTTON SLOTS-----------------------------------------//
void MainWindow::on_pushButton_clicked()
{
    QString url_string = "http://";
    url_string.append(ui->IpCamTxb->text());
    url_string.append(":4747/video");

    //<<<<<<<<<<<<<-Web View->>>>>>>>>>>>>>//
    ui->camView->setUrl(QUrl(url_string));
    ui->camView->show();
}

void MainWindow::on_UpBtn_pressed(){    dir = 'f';  }
void MainWindow::on_DownBtn_pressed(){  dir = 'b';  }
void MainWindow::on_LeftBtn_pressed(){  dir = 'l';  }
void MainWindow::on_RightBtn_pressed(){ dir = 'r';  }

void MainWindow::on_UpBtn_released(){   dir = 's';  }
void MainWindow::on_DownBtn_released(){ dir = 's';  }
void MainWindow::on_LeftBtn_released(){ dir = 's';  }
void MainWindow::on_RightBtn_released(){dir = 's';  }


void MainWindow::on_SaveDbBtn_clicked()
{
    QString rutaBase = QFileDialog::getSaveFileName(this,
                                        tr("Save Address Book"),
                                        "", tr("sqlite data base(*.sqlite);;All Files (*)"));
    rutaBase += ".sqlite";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(rutaBase);

    if(!db.open())
    {  QMessageBox::critical(NULL, "Alumnos", "Error en la apertura de la base de datos de alumnos!");
       exit(1);
    }

    QString ConsultaREUM_data("CREATE TABLE IF NOT EXISTS reumData("
                                "time VARCHAR(20) PRIMARY KEY,"
                                "type VARCHAR (10),"
                                "val VARCHAR (10),"
                                "unit VARCHAR(5)"
                                ");");

    QSqlQuery tabla(db);
    qDebug() << "Query Alumnos:" << ConsultaREUM_data.toLocal8Bit().constData() << endl;
    if(!tabla.prepare(ConsultaREUM_data))
        QMessageBox::critical(NULL, "Base de Datos", "No se pudo preparar la consulta");
    if (!tabla.exec())
        exit(1);

    ui->DbLbl->setText(rutaBase);
    ui->SaveDbBtn->setEnabled(false);
}
