#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>

#include <QUrl>
#include <QDebug>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QTimer>

#include <QTcpSocket>
#include <QTcpServer>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>

#include <QTableWidgetItem>
#include <QDateTime>

#include <qcustomplot.h>

#define UPDATE_DATA_TIME 250

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connected_slot();
    void newTCPData_slot();

    void on_camConnectBtn_clicked();

    void on_UpBtn_pressed();
    void on_DownBtn_pressed();
    void on_LeftBtn_pressed();
    void on_RightBtn_pressed();

    void on_UpBtn_released();
    void on_DownBtn_released();
    void on_LeftBtn_released();
    void on_RightBtn_released();

    void on_SaveDbBtn_clicked();
    void on_loadDbBtn_clicked();
    void on_stopSaveBtn_clicked();

    void on_tipoFiltroBtn_clicked();
    void on_rangoFilrtoBtn_clicked();

    void on_lightBtn_clicked();

protected:
    void keyPressEvent(QKeyEvent *keyevent);
    void keyReleaseEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *bar);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    char dir;

    QSqlDatabase db;
    QSqlDatabase dbRead;
    QString rutaWriteDb;

    void sendTCPmsg(QString msg, bool raw = 0);
    void updateRobotDir(void);
    void updateTable(char itemIndex, QString val);
    void updateSQLdb(void);

    void plotSqlModel(QSqlQueryModel *model);
    void configureDbTable(void);

};
#endif // MAINWINDOW_H
