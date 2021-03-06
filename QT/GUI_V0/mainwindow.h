#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>

#include <QUrl>
#include <QDebug>

#include <QTcpServer>
#include <QTcpSocket>

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

    void on_UpBtn_clicked();
    void on_camConnBtn_clicked();

private:
    Ui::MainWindow *ui;

    QTcpServer *server;
    QTcpSocket *socket;
    int cant_conexiones;
};
#endif // MAINWINDOW_H
