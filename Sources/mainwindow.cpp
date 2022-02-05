#include "Headers\mainwindow.h"
#include "Headers\connect.h"
#include "ui_mainwindow.h"
#include "Headers\commands.h"
#include "Headers/scardoperations.h"
#include "Headers/apducommand.h"
#include <QString>
#include <QDebug>
#include <cstdio>
#include <stdio.h>
#include <cstring>

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

    lRet = connect->establishContext();
    if( lRet != SCARD_S_SUCCESS )
    {
        ui->connectedReaderName->setText("Connection Failed!");
        ui->connectedReaderName->setStyleSheet("QLabel {font-weight: bold; color : red; }");

        ui->UID->clear();
        ui->statusUID->clear();
        ui->UIDframe->setEnabled(choice::clear);
        ui->tabs->setEnabled(choice::clear);
    }
    else
    {
        connect->setReaderLists(choice::set);
        readerList = connect->getReaderLists();
        QString readerListStr = (QString::fromWCharArray(readerList));
        qDebug() << readerList;

        if( readerListStr != NULL )
        {
            ui->connectedReaderName->setText(readerListStr);
            ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : green; }");
            ui->UIDframe->setEnabled(choice::set);
        }
        else
        {
            ui->connectedReaderName->setText("Connection Failed");
            ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : red; }");
            ui->UID->clear();
            ui->statusUID->clear();
            ui->UIDframe->setEnabled(choice::clear);
            ui->tabs->setEnabled(choice::clear);
        }
    }
}

void MainWindow::on_ConnectUID_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    connect->connectCard();
    connect->setCardUID();
    QString UID = connect->getCardUID();
    if(UID != "00 00 00 00")
    {
    ui->UID->setText(UID);
    ui->statusUID->setText("Connected.");
    ui->statusUID->setStyleSheet("QLabel#statusUID {font-weight: bold; color : green; }");
    ui->SBframe->setEnabled(choice::set);
    ui->keyAframe->setEnabled(choice::set);
    ui->keyBframe->setEnabled(choice::set);
    ui->tabs->setEnabled(choice::set);
    ui->Operations->setEnabled(choice::set);
    ui->ReleaseUID->setEnabled(choice::set);


    }
    else
    {
    ui->UID->clear();
    ui->statusUID->setText("Failed!");
    ui->statusUID->setStyleSheet("QLabel#statusUID {font-weight: bold; color : red; }");
    ui->ReleaseUID->setEnabled(choice::clear);
    }
}
void MainWindow::on_ReleaseUID_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    connect->disconnectCard();
    ui->UID->clear();
    ui->statusUID->setText("Disconnected.");
    ui->statusUID->setStyleSheet("QLabel#statusUID {font-weight: bold; color : green; }");
    ui->keyAframe->setEnabled(choice::clear);
    ui->keyBframe->setEnabled(choice::clear);
    ui->RWframe->setEnabled(choice::clear);
    ui->SBframe->setEnabled(choice::clear);
    ui->tabs->setEnabled(choice::clear);
    ui->ReleaseUID->setEnabled(choice::clear);
    ui->statusA->clear();
    ui->statusB->clear();
    ui->statusRW->clear();

    ui->tabs->setCurrentIndex(0);
}
void MainWindow::on_loadTo0A_clicked()
{
    QString _keyA;
    _keyA.append ( (ui->keyA5->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA4->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA3->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA2->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA1->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA0->toPlainText()).toUtf8() );

    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};

    scrdops.setKeyA(_keyA);
    BYTE storageAddress = V_MEMORY;
    apdu.setLoadKeyCommand(scrdops.getKeyA() , storageAddress);
    if (connect->loadKey(apdu.getLoadKeyCommand()) != SCARD_S_SUCCESS)
        {
            ui->statusA->setText("Failed to load key!");
            ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : red; }");
        }
    else
        {
            ui->statusA->setText("Key loaded.");
            ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : green; }");
        }

}
void MainWindow::on_loadTo1A_clicked()
{
    QString _keyA;
    _keyA.append ( (ui->keyA5->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA4->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA3->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA2->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA1->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA0->toPlainText()).toUtf8() );

    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};
    qDebug() << _keyA;
    scrdops.setKeyA(_keyA);
    BYTE storageAddress = NV_MEMORY;
    apdu.setLoadKeyCommand(scrdops.getKeyA() , storageAddress);
    if (connect->loadKey(apdu.getLoadKeyCommand()) != SCARD_S_SUCCESS)
        {
            ui->statusA->setText("Failed to load key!");
            ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : red; }");
        }
    else
        {
            ui->statusA->setText("Key loaded.");
            ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : green; }");
        }

}
void MainWindow::on_loadTo0B_clicked()
{
    QString _keyB;
    _keyB.append ( (ui->keyB5->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB4->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB3->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB2->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB1->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB0->toPlainText()).toUtf8() );

    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};

    scrdops.setKeyB(_keyB);
    BYTE storageAddress = V_MEMORY;
    apdu.setLoadKeyCommand(scrdops.getKeyB() , storageAddress);
    if (connect->loadKey(apdu.getLoadKeyCommand()) != SCARD_S_SUCCESS)
        {
            ui->statusB->setText("Failed to load key!");
            ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : red; }");
        }
    else
        {
            ui->statusB->setText("Key loaded.");
            ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : green; }");
        }

}


void MainWindow::on_loadTo1B_clicked()
{
    QString _keyB;
    _keyB.append ( (ui->keyB5->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB4->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB3->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB2->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB1->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB0->toPlainText()).toUtf8() );

    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};

    scrdops.setKeyB(_keyB);
    BYTE storageAddress = NV_MEMORY;
    apdu.setLoadKeyCommand(scrdops.getKeyB() , storageAddress);
    if (connect->loadKey(apdu.getLoadKeyCommand()) != SCARD_S_SUCCESS)
        {
            ui->statusA->setText("Failed to load key!");
            ui->statusA->setStyleSheet("QLabel#statusB {font-weight: bold; color : red; }");
        }
    else
        {
            ui->statusA->setText("Key loaded.");
            ui->statusA->setStyleSheet("QLabel#statusB {font-weight: bold; color : green; }");
        }

}


void MainWindow::on_authWithKeyA_clicked()
{

    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    QString blockString =(ui->blockSelect->text());
    connect->setBlockNum(blockString);

    apdu.setAuthCommand(connect->getBlockNum(), KEYA_SELECT, 0x00);

    if (connect->authenticate(apdu.getAuthCommand()) != SCARD_S_SUCCESS)
        {
            ui->statusA->setText("Failed to authenticate!");
            ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : red; }");
        }
    else
        {
            ui->statusA->setText("Authenticated.");
            ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : green; }");
            ui->RWframe->setEnabled(choice::set);
            ui->RAW->setEnabled(choice::set);
            ui->Commands->setEnabled(choice::set);
            ui->Utility->setEnabled(choice::set);
        }
}
void MainWindow::on_authWithKeyB_clicked()
{

        SCardConnection* connect = SCardConnection::getInstance();
        APDUCommand apdu{};
        QString blockString =(ui->blockSelect->text());
        connect->setBlockNum(blockString);

        apdu.setAuthCommand(connect->getBlockNum(), KEYB_SELECT, 0X00);

        if (connect->authenticate(apdu.getAuthCommand()) != SCARD_S_SUCCESS)
            {
                ui->statusB->setText("Failed to authenticate!");
                ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : red; }");
            }
        else
            {
                ui->statusB->setText("Authenticated.");
                ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : green; }");
                ui->RWframe->setEnabled(choice::set);
                ui->RAW->setEnabled(choice::set);
                ui->Commands->setEnabled(choice::set);
            }

}

void MainWindow::on_readBlock_clicked()
{
    MainWindow::setReadOnlyReadBlocks();
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    QString recievedData;
    QString blockString = (ui->blockSelect->text());
    connect->setBlockNum(blockString);
    apdu.setReadCommand(connect->getBlockNum());

    recievedData = connect->readDataBlock(apdu.getReadCommand());
    QStringList dataList = recievedData.split(' ');

    if (dataList.at(BLOCK_SIZE-RESPONSE_SIZE)   != SUCCESS_RESPONSE[0] &&
        dataList.at(BLOCK_SIZE-RESPONSE_SIZE+1) != SUCCESS_RESPONSE[1])
        {

        ui->statusRW->setText("Read successfully.");
        ui->statusRW->setStyleSheet("QLabel#statusRW {font-weight: bold; color : green; }");
        MainWindow::applyDataToReadBLocks(dataList);

        }
    else
        {
        ui->statusRW->setText("Failed to read!");
        ui->statusRW->setStyleSheet("QLabel#statusRW {font-weight: bold; color : red; }");
        }
}

void MainWindow::on_writeBlock_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    QString _writeBlock;
    _writeBlock.append ( (ui->R15->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R14->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R13->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R12->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R11->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R10->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R9 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R8 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R7 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R6 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R5 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R4 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R3 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R2 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R1 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R0 ->toPlainText()).toUtf8() );


    QByteArray _writeBlockBytes = QByteArray::fromHex(_writeBlock.toLatin1());
    BYTE writeBlock[BLOCK_SIZE];
    for( int i=0 ; i<static_cast<int>(BLOCK_SIZE) ; i++ )
    {
        writeBlock[i] = _writeBlockBytes[i];
    printf("%X ",writeBlock[i]);
    }
    QString blockString = (ui->blockSelect->text());
    connect->setBlockNum(blockString);
    apdu.setWriteCommand(connect->getBlockNum(), writeBlock);
    if(connect->writeDataBlock(apdu.getWriteCommand()) != SCARD_S_SUCCESS)
        {
        ui->statusRW->setText("Failed to write!");
        ui->statusRW->setStyleSheet("QLabel#statusRW {font-weight: bold; color : red; }");
        }
    else
        {
        ui->statusRW->setText("Written successfully.");
        ui->statusRW->setStyleSheet("QLabel#statusRW {font-weight: bold; color : green; }");
        }
}



void MainWindow::on_rawGO_clicked()
{}
//{

//    QList< QStringList > lists;
//    QString line;
//    do {
//        line = in.readLine();
//        lists << line.split("\t");
//    } while (!line.isNull());

//    tableWidget.setRowCount( lists.size() );
//    tableWidget.setColumnCount( lists[0].size() );

//    for ( int row = 0; row < lists.size(); ++row ) {
//        for ( int column = 0; column < lists[row].size(); ++column ) {
//            tableWidget.setItem(row, column, new QTableWidgetItem(lists[row][column]));
//        }
//    }
//}
//}
