#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>

#include <QUrl>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>

#include <QTcpSocket>
#include <QTcpServer>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QTableWidgetItem>
#include <QDateTime>

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

    void on_pushButton_clicked();

    void on_UpBtn_pressed();
    void on_DownBtn_pressed();
    void on_LeftBtn_pressed();
    void on_RightBtn_pressed();

    void on_UpBtn_released();
    void on_DownBtn_released();
    void on_LeftBtn_released();
    void on_RightBtn_released();

    void on_SaveDbBtn_clicked();

protected:
    void keyPressEvent(QKeyEvent *keyevent);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    char dir;

    QSqlDatabase db;

    void sendTCPmsg(QString msg);
    void updateRobotDir(void);
    void updateTable(char itemIndex, QString val);

};
#endif // MAINWINDOW_H