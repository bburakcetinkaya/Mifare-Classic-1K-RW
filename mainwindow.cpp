#include "mainwindow.h"
#include "connect.h"
#include "ui_mainwindow.h"
#include "commands.h"
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_connectReader_clicked()
{
    SCardConnection* connect =SCardConnection::getInstance();
    LPTSTR readerList;
    LONG lRet;
    connect->setEstablishContext();
    lRet = connect->getEstablishContext();
    if(lRet != SCARD_S_SUCCESS)
    {
        ui->connectedReaderName->setText("Connection Failed!");
        ui->connectedReaderName->setStyleSheet("QLabel {font-weight: bold; color : red; }");
        return;
    }

    connect->setReaderLists(choice::set);
    readerList = connect->getReaderLists();
    if(NULL != readerList)
    {
        QString readerListS = QString::fromWCharArray(readerList);
        ui->connectedReaderName->setText(readerListS);
        ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : green; }");
    }
    else
    {
        ui->connectedReaderName->setText("Connection Failed");
        ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : red; }");
    }


}


void MainWindow::on_ConnectUID_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    connect->connectCard();
    connect->setCardUID();
    QString UID = connect->getCardUID();
    if(UID != "")
    {
    ui->UID->setText(UID);
    ui->UID->setStyleSheet("QLineEdit#connectedReaderName {color : black; }");
    }
    else
    {
    ui->UID->setText("Failed!");
    ui->UID->setStyleSheet("QLineEdit#connectedReaderName {color : red; }");
    }
}


