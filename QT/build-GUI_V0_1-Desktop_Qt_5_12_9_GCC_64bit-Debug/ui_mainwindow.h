/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwebengineview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *ctrlGroup;
    QHBoxLayout *horizontalLayout_2;
    QFrame *webcamFrame;
    QVBoxLayout *verticalLayout_3;
    QFrame *IpFrame;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *IpCamTxb;
    QPushButton *pushButton;
    QWebEngineView *camView;
    QFrame *btnFrame;
    QGridLayout *gridLayout;
    QPushButton *LeftBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *DownBtn;
    QPushButton *UpBtn;
    QPushButton *RightBtn;
    QSlider *velocitySlide;
    QGroupBox *dataGroup;
    QHBoxLayout *horizontalLayout;
    QTableWidget *datTable;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QPushButton *SaveDbBtn;
    QLabel *DbLbl;
    QPushButton *stopSaveBtn;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_5;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *loadDbBtn;
    QLabel *DbDirLoadLbl;
    QSpacerItem *horizontalSpacer_3;
    QTableView *DbTableView;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_6;
    QComboBox *tiposComboBox;
    QCheckBox *timeCheck;
    QCheckBox *dateCheck;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *tipoFiltroBtn;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QTimeEdit *timeEditFrom;
    QLabel *label_2;
    QTimeEdit *timeEditTo;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *rangoFilrtoBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(811, 723);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        ctrlGroup = new QGroupBox(tab);
        ctrlGroup->setObjectName(QString::fromUtf8("ctrlGroup"));
        horizontalLayout_2 = new QHBoxLayout(ctrlGroup);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        webcamFrame = new QFrame(ctrlGroup);
        webcamFrame->setObjectName(QString::fromUtf8("webcamFrame"));
        webcamFrame->setFrameShape(QFrame::StyledPanel);
        webcamFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(webcamFrame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        IpFrame = new QFrame(webcamFrame);
        IpFrame->setObjectName(QString::fromUtf8("IpFrame"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(IpFrame->sizePolicy().hasHeightForWidth());
        IpFrame->setSizePolicy(sizePolicy1);
        IpFrame->setFrameShape(QFrame::StyledPanel);
        IpFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(IpFrame);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        IpCamTxb = new QLineEdit(IpFrame);
        IpCamTxb->setObjectName(QString::fromUtf8("IpCamTxb"));

        horizontalLayout_3->addWidget(IpCamTxb);

        pushButton = new QPushButton(IpFrame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_3->addWidget(pushButton);


        verticalLayout_3->addWidget(IpFrame);

        camView = new QWebEngineView(webcamFrame);
        camView->setObjectName(QString::fromUtf8("camView"));
        camView->setMinimumSize(QSize(300, 250));

        verticalLayout_3->addWidget(camView);


        horizontalLayout_2->addWidget(webcamFrame);

        btnFrame = new QFrame(ctrlGroup);
        btnFrame->setObjectName(QString::fromUtf8("btnFrame"));
        btnFrame->setEnabled(false);
        btnFrame->setMaximumSize(QSize(500, 500));
        btnFrame->setFrameShape(QFrame::StyledPanel);
        btnFrame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(btnFrame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        LeftBtn = new QPushButton(btnFrame);
        LeftBtn->setObjectName(QString::fromUtf8("LeftBtn"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(LeftBtn->sizePolicy().hasHeightForWidth());
        LeftBtn->setSizePolicy(sizePolicy2);
        LeftBtn->setMinimumSize(QSize(75, 75));

        gridLayout->addWidget(LeftBtn, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(72, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 1, 1, 1);

        DownBtn = new QPushButton(btnFrame);
        DownBtn->setObjectName(QString::fromUtf8("DownBtn"));
        sizePolicy2.setHeightForWidth(DownBtn->sizePolicy().hasHeightForWidth());
        DownBtn->setSizePolicy(sizePolicy2);
        DownBtn->setMinimumSize(QSize(75, 75));

        gridLayout->addWidget(DownBtn, 4, 1, 1, 1);

        UpBtn = new QPushButton(btnFrame);
        UpBtn->setObjectName(QString::fromUtf8("UpBtn"));
        sizePolicy2.setHeightForWidth(UpBtn->sizePolicy().hasHeightForWidth());
        UpBtn->setSizePolicy(sizePolicy2);
        UpBtn->setMinimumSize(QSize(75, 75));

        gridLayout->addWidget(UpBtn, 0, 1, 1, 1);

        RightBtn = new QPushButton(btnFrame);
        RightBtn->setObjectName(QString::fromUtf8("RightBtn"));
        sizePolicy2.setHeightForWidth(RightBtn->sizePolicy().hasHeightForWidth());
        RightBtn->setSizePolicy(sizePolicy2);
        RightBtn->setMinimumSize(QSize(75, 75));

        gridLayout->addWidget(RightBtn, 2, 2, 1, 1);


        horizontalLayout_2->addWidget(btnFrame);

        velocitySlide = new QSlider(ctrlGroup);
        velocitySlide->setObjectName(QString::fromUtf8("velocitySlide"));
        velocitySlide->setEnabled(false);
        velocitySlide->setMinimumSize(QSize(50, 0));
        velocitySlide->setMaximumSize(QSize(100, 16777215));
        velocitySlide->setStyleSheet(QString::fromUtf8(".QSlider::vertical{\n"
"	margin: 30px, 30px;\n"
"}\n"
"\n"
".QSlider::groove:vertical {\n"
"    border: 1px solid #262626;\n"
"    width: 10px;\n"
"    background: #393939;\n"
"    margin: 0 12px;\n"
"}\n"
"\n"
".QSlider::handle:vertical {\n"
"    background: #22B14C;\n"
"    margin: -10px -30px;\n"
"}\n"
"\n"
""));
        velocitySlide->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(velocitySlide);


        verticalLayout_4->addWidget(ctrlGroup);

        dataGroup = new QGroupBox(tab);
        dataGroup->setObjectName(QString::fromUtf8("dataGroup"));
        horizontalLayout = new QHBoxLayout(dataGroup);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        datTable = new QTableWidget(dataGroup);
        if (datTable->columnCount() < 2)
            datTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        datTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        datTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (datTable->rowCount() < 3)
            datTable->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        datTable->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        datTable->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        datTable->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        datTable->setItem(0, 1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        datTable->setItem(1, 1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        datTable->setItem(2, 1, __qtablewidgetitem7);
        datTable->setObjectName(QString::fromUtf8("datTable"));
        datTable->setEnabled(false);
        datTable->setMinimumSize(QSize(150, 0));
        datTable->setMaximumSize(QSize(16777215, 250));

        horizontalLayout->addWidget(datTable);

        frame = new QFrame(dataGroup);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy3);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        SaveDbBtn = new QPushButton(frame);
        SaveDbBtn->setObjectName(QString::fromUtf8("SaveDbBtn"));
        SaveDbBtn->setEnabled(false);

        verticalLayout_2->addWidget(SaveDbBtn);

        DbLbl = new QLabel(frame);
        DbLbl->setObjectName(QString::fromUtf8("DbLbl"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(DbLbl->sizePolicy().hasHeightForWidth());
        DbLbl->setSizePolicy(sizePolicy4);
        DbLbl->setMinimumSize(QSize(0, 0));
        DbLbl->setMaximumSize(QSize(100, 80));
        DbLbl->setAutoFillBackground(false);
        DbLbl->setFrameShape(QFrame::NoFrame);
        DbLbl->setTextFormat(Qt::PlainText);
        DbLbl->setWordWrap(true);

        verticalLayout_2->addWidget(DbLbl, 0, Qt::AlignTop);

        stopSaveBtn = new QPushButton(frame);
        stopSaveBtn->setObjectName(QString::fromUtf8("stopSaveBtn"));
        stopSaveBtn->setEnabled(false);

        verticalLayout_2->addWidget(stopSaveBtn);


        horizontalLayout->addWidget(frame);


        verticalLayout_4->addWidget(dataGroup);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_5 = new QVBoxLayout(tab_2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        frame_2 = new QFrame(tab_2);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        loadDbBtn = new QPushButton(frame_2);
        loadDbBtn->setObjectName(QString::fromUtf8("loadDbBtn"));
        sizePolicy1.setHeightForWidth(loadDbBtn->sizePolicy().hasHeightForWidth());
        loadDbBtn->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(loadDbBtn);

        DbDirLoadLbl = new QLabel(frame_2);
        DbDirLoadLbl->setObjectName(QString::fromUtf8("DbDirLoadLbl"));

        horizontalLayout_4->addWidget(DbDirLoadLbl);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_5->addWidget(frame_2);

        DbTableView = new QTableView(tab_2);
        DbTableView->setObjectName(QString::fromUtf8("DbTableView"));

        verticalLayout_5->addWidget(DbTableView);

        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        frame_3 = new QFrame(groupBox);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_3);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        tiposComboBox = new QComboBox(frame_3);
        tiposComboBox->addItem(QString());
        tiposComboBox->addItem(QString());
        tiposComboBox->addItem(QString());
        tiposComboBox->addItem(QString());
        tiposComboBox->setObjectName(QString::fromUtf8("tiposComboBox"));
        tiposComboBox->setMinimumSize(QSize(180, 0));

        horizontalLayout_6->addWidget(tiposComboBox);

        timeCheck = new QCheckBox(frame_3);
        timeCheck->setObjectName(QString::fromUtf8("timeCheck"));
        timeCheck->setChecked(true);

        horizontalLayout_6->addWidget(timeCheck);

        dateCheck = new QCheckBox(frame_3);
        dateCheck->setObjectName(QString::fromUtf8("dateCheck"));
        dateCheck->setChecked(true);

        horizontalLayout_6->addWidget(dateCheck);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        tipoFiltroBtn = new QPushButton(frame_3);
        tipoFiltroBtn->setObjectName(QString::fromUtf8("tipoFiltroBtn"));

        horizontalLayout_6->addWidget(tipoFiltroBtn);


        verticalLayout_6->addWidget(frame_3);

        frame_4 = new QFrame(groupBox);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_4);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(frame_4);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        timeEditFrom = new QTimeEdit(frame_4);
        timeEditFrom->setObjectName(QString::fromUtf8("timeEditFrom"));
        timeEditFrom->setCurrentSection(QDateTimeEdit::HourSection);
        timeEditFrom->setCalendarPopup(false);

        horizontalLayout_5->addWidget(timeEditFrom);

        label_2 = new QLabel(frame_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        timeEditTo = new QTimeEdit(frame_4);
        timeEditTo->setObjectName(QString::fromUtf8("timeEditTo"));

        horizontalLayout_5->addWidget(timeEditTo);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        rangoFilrtoBtn = new QPushButton(frame_4);
        rangoFilrtoBtn->setObjectName(QString::fromUtf8("rangoFilrtoBtn"));

        horizontalLayout_5->addWidget(rangoFilrtoBtn);


        verticalLayout_6->addWidget(frame_4);


        verticalLayout_5->addWidget(groupBox);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 811, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        ctrlGroup->setTitle(QApplication::translate("MainWindow", "Contro de REUM", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Conectar", nullptr));
        LeftBtn->setText(QString());
        DownBtn->setText(QString());
        UpBtn->setText(QString());
        RightBtn->setText(QString());
        dataGroup->setTitle(QApplication::translate("MainWindow", "Entrada de datos", nullptr));
        QTableWidgetItem *___qtablewidgetitem = datTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Valor", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = datTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Unidad", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = datTable->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Temperatura", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = datTable->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Humedad", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = datTable->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Presion", nullptr));

        const bool __sortingEnabled = datTable->isSortingEnabled();
        datTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem5 = datTable->item(0, 1);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "C\302\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = datTable->item(1, 1);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "%", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = datTable->item(2, 1);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Pa", nullptr));
        datTable->setSortingEnabled(__sortingEnabled);

        SaveDbBtn->setText(QApplication::translate("MainWindow", "Grabar Datos", nullptr));
        DbLbl->setText(QString());
        stopSaveBtn->setText(QApplication::translate("MainWindow", "Parar Grabaci\303\263n", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Control", nullptr));
        loadDbBtn->setText(QApplication::translate("MainWindow", "Cargar archivo", nullptr));
        DbDirLoadLbl->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Filtros", nullptr));
        tiposComboBox->setItemText(0, QApplication::translate("MainWindow", "Todo", nullptr));
        tiposComboBox->setItemText(1, QApplication::translate("MainWindow", "Temperatura", nullptr));
        tiposComboBox->setItemText(2, QApplication::translate("MainWindow", "Humedad", nullptr));
        tiposComboBox->setItemText(3, QApplication::translate("MainWindow", "Presi\303\263n", nullptr));

        timeCheck->setText(QApplication::translate("MainWindow", "Timestamp", nullptr));
        dateCheck->setText(QApplication::translate("MainWindow", "Date", nullptr));
        tipoFiltroBtn->setText(QApplication::translate("MainWindow", "Filtrar tipo", nullptr));
        label->setText(QApplication::translate("MainWindow", "Desde", nullptr));
        timeEditFrom->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm:ss", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Hasta", nullptr));
        timeEditTo->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm:ss", nullptr));
        rangoFilrtoBtn->setText(QApplication::translate("MainWindow", "Filtrar rango", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "log reader", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
