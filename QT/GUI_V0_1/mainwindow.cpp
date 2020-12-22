#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

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
    dir = 'S';

     //<<<<<<<<<<<<<-button icons->>>>>>>>>>>>>>//
    ui->UpBtn->setIcon(QIcon("../GUI_V0/images/up.png"));
    ui->UpBtn->setIconSize(ui->UpBtn->size());

    ui->DownBtn->setIcon(QIcon("../GUI_V0/images/down.png"));
    ui->DownBtn->setIconSize(ui->DownBtn->size());

    ui->LeftBtn->setIcon(QIcon("../GUI_V0/images/left.png"));
    ui->LeftBtn->setIconSize(ui->LeftBtn->size());

    ui->RightBtn->setIcon(QIcon("../GUI_V0/images/right.png"));
    ui->RightBtn->setIconSize(ui->RightBtn->size());

    //<<<<<<<<<<<<<-Others->>>>>>>>>>>>>>//
    ui->datTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->IpCamTxb->setInputMask("000.000.000.000");
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
    ui->SaveDbBtn->setEnabled(true);
    sendTCPmsg("C");

    //<<<<<<<<<<<<<<-QTimer->>>>>>>>>>>>>>>>//
    QTimer *update_dir_timer = new QTimer(this);
    connect(update_dir_timer, &QTimer::timeout, this, &MainWindow::updateRobotDir);
    update_dir_timer->start(UPDATE_DATA_TIME);
}

void MainWindow::newTCPData_slot()
{
    #define CANT_ITEMS_RCV  4

    QByteArray datos = socket->readLine();
    QString str_input = QString::fromStdString(datos.toStdString());
    QStringList input_list = str_input.split("#");
    input_list.pop_front();
    for(int i = CANT_ITEMS_RCV*2; i < input_list.length(); i++)
        input_list.removeAt(i);

    if(input_list.count()> 1){
        for(int j = 0; j < CANT_ITEMS_RCV*2; j+=2){
            QByteArray d = input_list[j].toUtf8();
            updateTable(d[0], input_list[j+1]);
        }

        if(db.isOpen())updateSQLdb();
    }

}

void MainWindow::sendTCPmsg(QString msg){
    QString send_msg = "#";
    send_msg.append(msg);
    send_msg.append("&");
    send_msg.append("");

    std::string str_msg = send_msg.toStdString();
    const char* char_msg = str_msg.c_str();
    socket->write(char_msg);
    qDebug() << char_msg;
}

//---------------------------------------------KEY PRESS----------------------------------------//
void MainWindow::keyPressEvent(QKeyEvent *keyevent)
{
    int pressed_key = keyevent->key();

    if(pressed_key == Qt::Key_Up)           dir = 'F';
    else if(pressed_key == Qt::Key_Down)    dir = 'B';
    else if(pressed_key == Qt::Key_Left)    dir = 'L';
    else if(pressed_key == Qt::Key_Right)   dir = 'R';
}

void MainWindow::keyReleaseEvent(QKeyEvent *keyevent)
{
    int released_key = keyevent->key();
    if(released_key) dir = 'S';
}


void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "APP_NAME",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        sendTCPmsg("T");
        event->accept();

    }
}

//-------------------------------------------UPDATE DATA----------------------------------------//
void MainWindow::updateRobotDir(){
    QString dir_s = QString(dir);
    int v_int = ui->velocitySlide->value();

    dir_s.append(QString::number(v_int));
    sendTCPmsg(dir_s);
}

void MainWindow::updateTable(char itemChar, QString val)
{
    int itemIndex = 0;
    switch(itemChar){
        case 't':   itemIndex = 0;      break;
        case 'l':   itemIndex = 1;      break;
        case 'p':   itemIndex = 2;      break;
        case 'g':   itemIndex = 3;      break;
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

void MainWindow::updateSQLdb(void){
    QString consulta;
    QString time, date;

    QString temp_s = "";
    QString luz_s  = "";
    QString pres_s = "";
    QString gas_s  = "";

    //-------timestamp
    date = QDate::currentDate().toString();
    time = QTime::currentTime().toString();

    //-------tableData
    for (int i = 0; i < ui->datTable->rowCount(); ++i) {
        QTableWidgetItem *d_item = ui->datTable->item(i, 0);
        QString type = ui->datTable->verticalHeaderItem(i)->text();
        if(d_item){
            if(QString::compare(type, "Temperatura"))
                temp_s = d_item->text();
            if(QString::compare(type, "Luz"))
                luz_s = d_item->text();
            if(QString::compare(type, "Presion"))
                pres_s = d_item->text();
            if(QString::compare(type, "Gas (CO)"))
                gas_s = d_item->text();
        }
    }
    consulta.append("INSERT INTO reumData(time, date, temp, luz, pres, gas)"
                    "VALUES ('"+time+
                    "', '"+date+
                    "', '"+temp_s+
                    "', '"+luz_s +
                    "', '"+pres_s+
                    "', '"+gas_s +
                    "' );");

    QSqlQuery insert_data(db);
    insert_data.prepare(consulta);
    if(!insert_data.exec()){
        QMessageBox::critical(NULL, "Alumnos", "Error mientras se guardaban los datos.");
    }
    qDebug() << "Query insert:" << consulta.toLocal8Bit().constData() << endl;
    consulta = "";
}
//------------------------------------------BUTTON SLOTS-----------------------------------------//
void MainWindow::on_camConnectBtn_clicked()
{
    QString url_string = "http://";
    url_string.append(ui->IpCamTxb->text());
    url_string.append(":4747/video");

    //<<<<<<<<<<<<<-Web View->>>>>>>>>>>>>>//
    ui->camView->setUrl(QUrl(url_string));
    ui->camView->show();
}

void MainWindow::on_UpBtn_pressed(){    dir = 'F';  }
void MainWindow::on_DownBtn_pressed(){  dir = 'B';  }
void MainWindow::on_LeftBtn_pressed(){  dir = 'L';  }
void MainWindow::on_RightBtn_pressed(){ dir = 'R';  }

void MainWindow::on_UpBtn_released(){   dir = 'S';  }
void MainWindow::on_DownBtn_released(){ dir = 'S';  }
void MainWindow::on_LeftBtn_released(){ dir = 'S';  }
void MainWindow::on_RightBtn_released(){dir = 'S';  }


void MainWindow::on_SaveDbBtn_clicked()
{
    QString rutaBase = QFileDialog::getSaveFileName(this,
                                        tr("Save Address Book"),
                                        "", tr("sqlite data base(*.sqlite);;All Files (*)"));
    rutaBase.append(".sqlite");

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(rutaBase);

    if(!db.open())
    {  QMessageBox::critical(NULL, "data log", "Error en la apertura de la base de datos!");
       exit(1);
    }

    QString ConsultaREUM_data("CREATE TABLE IF NOT EXISTS reumData("
                                "time VARCHAR(20) PRIMARY KEY,"
                                "date VARCHAR(20), "
                                "temp VARCHAR(5),"
                                "luz  VARCHAR(5),"
                                "pres VARCHAR(5),"
                                "gas  VARCHAR(5)"
                                ");");

    QSqlQuery tabla(db);
    qDebug() << "Query create:" << ConsultaREUM_data.toLocal8Bit().constData() << endl;
    if(!tabla.prepare(ConsultaREUM_data))
        QMessageBox::critical(NULL, "Base de Datos", "No se pudo preparar la consulta");
    if (!tabla.exec())
        exit(1);

    ui->DbLbl->setText(rutaBase);
    ui->SaveDbBtn->setEnabled(false);
    ui->stopSaveBtn->setEnabled(true);
}

void MainWindow::on_stopSaveBtn_clicked()
{
    db.close();
    db.setDatabaseName("");
    ui->stopSaveBtn->setEnabled(false);
    ui->SaveDbBtn->setEnabled(true);
}


void MainWindow::on_loadDbBtn_clicked()
{   QString rutaBase = QFileDialog::getOpenFileName(this,
            tr("Abrir base de datos"), "",
            tr("qlite data base(*.sqlite);;All Files (*)"));

    if(rutaBase == "")
        return;
    if(rutaBase == db.databaseName()){
        QMessageBox::critical(NULL, "data log - read", "la base de datos esta siendo utilizada");
        return;
    }

    dbRead = QSqlDatabase::addDatabase("QSQLITE");
    dbRead.setDatabaseName(rutaBase);
   if(!dbRead.open()){
        QMessageBox::critical(NULL, "data log - read", "Error en la apertura de la base de datos");
        return;
    }

    QString consultaDB_read("SELECT * FROM reumData");

    QSqlQuery sqlQuery(dbRead);
    qDebug() << "Query create:" << consultaDB_read.toLocal8Bit().constData() << endl;
    if(!sqlQuery.prepare(consultaDB_read))
        QMessageBox::critical(NULL, "Base de Datos", "No se pudo preparar la consulta");
    if (!sqlQuery.exec())
        exit(1);

    QSqlQueryModel *sqlModel = new QSqlQueryModel;
    sqlModel->setQuery(sqlQuery);
    ui->DbTableView->setModel(sqlModel);
    ui->DbDirLoadLbl->setText(rutaBase);
}

void MainWindow::on_tipoFiltroBtn_clicked()
{   QString select_db_s = "";

    if(dbRead.isOpen()){
        QString selected = ui->tiposComboBox->currentText();
        if(ui->timeCheck->isChecked()) select_db_s.append("time, ");
        if(ui->dateCheck->isChecked()) select_db_s.append("date, ");

        if(!selected.compare("Todo"))
               select_db_s = "*";
        else if(!selected.compare("Temperatura"))
                select_db_s.append("temp");
        else if(!selected.compare("Luz"))
                select_db_s.append("luz");
        else if(!selected.compare("Presión"))
                select_db_s.append("pres");
        else if(!selected.compare("Gas (CO)"))
                select_db_s.append("gas");

        QSqlQuery sqlQuery(dbRead);
        QString consultaDB_read("SELECT "+select_db_s+" FROM reumData");
        qDebug() << "Query select:" << consultaDB_read.toLocal8Bit().constData() << endl;
        if(!sqlQuery.prepare(consultaDB_read))
            QMessageBox::critical(NULL, "Base de Datos", "No se pudo preparar la consulta");
        if (!sqlQuery.exec())
            exit(1);

        QSqlQueryModel *sqlModel = new QSqlQueryModel;
        sqlModel->setQuery(sqlQuery);
        ui->DbTableView->setModel(sqlModel);
    }
}

void MainWindow::on_rangoFilrtoBtn_clicked()
{
   if(dbRead.isOpen()){
       QString from = ui->timeEditFrom->time().toString();
       QString to = ui->timeEditTo->time().toString();

       QSqlQuery sqlQuery(dbRead);
       QString consultaDB_read("SELECT * FROM reumData WHERE time BETWEEN '"+from+"' AND '"+to+"'");
       qDebug() << "Query select:" << consultaDB_read.toLocal8Bit().constData() << endl;

       if(!sqlQuery.prepare(consultaDB_read))
           QMessageBox::critical(NULL, "Base de Datos", "No se pudo preparar la consulta");
       if (!sqlQuery.exec())
           exit(1);

       QSqlQueryModel *sqlModel = new QSqlQueryModel;
       sqlModel->setQuery(sqlQuery);
       ui->DbTableView->setModel(sqlModel);
   }
}


void MainWindow::on_UpBtn_clicked()
{

}
