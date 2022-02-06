#include "Headers\mainwindow.h"
#include "Headers\connect.h"
#include "ui_mainwindow.h"
#include "Headers\commands.h"
#include "Headers/scardoperations.h"
#include "Headers/apducommand.h"
#include "Headers/textwindow.h"
#include <QString>
#include <QDebug>
#include <cstdio>
#include <stdio.h>
#include <cstring>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TextWindow* txtwnd = TextWindow::getInstance();
    connect(txtwnd, SIGNAL(listIsReady()) ,this , SLOT(applyDataFromTextWindow()));
    connect(txtwnd, SIGNAL(keyAisReady()) ,this , SLOT(applyDataFromTextWindowToKeyA()));
    connect(txtwnd, SIGNAL(keyBisReady()) ,this , SLOT(applyDataFromTextWindowToKeyB()));
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
    ui->RAW->setEnabled(choice::clear);
    ui->Utility->setEnabled(choice::clear);
    ui->Commands->setEnabled(choice::clear);

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
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};

    QString _keyA = MainWindow::getKeyA();
    QByteArray _keyBytes = QByteArray::fromHex(_keyA.toLatin1());
    BYTE keyA[KEY_SIZE] = {};
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            keyA[i] = _keyBytes[i];
       // printf("%X ",keyA[i]);
        }
    scrdops.setKeyA(keyA);
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
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};

    QString _keyA = MainWindow::getKeyA();
    BYTE keyA[KEY_SIZE] = {};
    QByteArray _keyBytes = QByteArray::fromHex(_keyA.toLatin1());
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            keyA[i] = _keyBytes[i];
        printf("%X ",keyA[i]);
        }
    scrdops.setKeyA(keyA);
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
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};

    QString _keyB = MainWindow::getKeyB();
    BYTE keyB[KEY_SIZE] = {};
    QByteArray _keyBytes = QByteArray::fromHex(_keyB.toLatin1());
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            keyB[i] = _keyBytes[i];
        printf("%X ",keyB[i]);
        }
    scrdops.setKeyB(keyB);
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
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};

    QString _keyB = MainWindow::getKeyB();
    BYTE keyB[KEY_SIZE] = {};
    QByteArray _keyBytes = QByteArray::fromHex(_keyB.toLatin1());
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            keyB[i] = _keyBytes[i];
        }
    scrdops.setKeyB(keyB);
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
    TextWindow* txtwnd = TextWindow::getInstance();

    QString blockString = (ui->blockSelect->text());
    connect->setBlockNum(blockString);
    apdu.setReadCommand(connect->getBlockNum());

    QString recievedData;
    recievedData = connect->readDataBlock(apdu.getReadCommand());
    QStringList dataList = recievedData.split(' ');

    if (dataList.at(BLOCK_SIZE-RESPONSE_SIZE)   != SUCCESS_RESPONSE[0] &&
        dataList.at(BLOCK_SIZE-RESPONSE_SIZE+1) != SUCCESS_RESPONSE[1])
        {
            ui->statusRW->setText("Read successfully.");
            ui->statusRW->setStyleSheet("QLabel#statusRW {font-weight: bold; color : green; }");
            MainWindow::applyDataToReadBLocks(dataList);
            txtwnd->setTextWindowTextReadOnly(true);
            ui->ACframe->setEnabled(true);
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

    QString _writeBlock = MainWindow::getWriteBlocks();
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
{
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};
    QAbstractButton *button = ui->rawKeySelectGroup->checkedButton();
    QString _keyA = MainWindow::getKeyA();
    QByteArray _keyBytes = QByteArray::fromHex(_keyA.toLatin1());
    BYTE keyA[KEY_SIZE] = {};
    QString sectorStr;
    int sectorNum = -1;
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            keyA[i] = _keyBytes[i];
       // printf("%X ",keyA[i]);
        }
    scrdops.setKeyA(keyA);

    QString recievedData;
    QStringList recievedDataSplit;
    QVector<QStringList> dataList;
   // if(button == ui->rawCheckKeyA)  on_loadTo0A_clicked();
    //if(button == ui->rawCheckKeyB)  on_loadTo1B_clicked();
    for(int i = 0; i<64; i++)
        {
        QString blockStr = QString::number(i);

        on_loadTo0A_clicked();
        connect->setBlockNum(blockStr);
        if(i%4 == 0)
            {
                sectorNum++;
                sectorStr = QString::number(i/4);

            //qDebug() << recievedData;
                apdu.setLoadKeyCommand(scrdops.getKeyA() , V_MEMORY);
                connect->loadKey(apdu.getLoadKeyCommand());
                apdu.setAuthCommand(connect->getBlockNum(), KEYA_SELECT, 0x00);
                //qDebug() << apdu.getAuthCommand();
                connect->authenticate(apdu.getAuthCommand());
            }
            apdu.setReadCommand(connect->getBlockNum());
            recievedData = connect->readDataBlock(apdu.getReadCommand());
            recievedData.push_front(" "+blockStr+" ");
            if(i%4 != 0)recievedData.push_front("\0");
            else recievedData.push_front(sectorStr);

            recievedDataSplit = recievedData.split(' ');
            dataList.append(recievedDataSplit);
    }
    qDebug() << dataList;
    QStringList rawHeaders = {"Sector","Block","B0","B1","B2","B3","B4","B5"
                             ,"B6","B7","B8","B9","B10","B11","B12","B13","B14","B15" };
    for(int row = 0; row< dataList.length()+1;row++)
    {
        ui->rawDataTable->insertRow( row );
        for(int column = 0; column<BLOCK_SIZE+2; column++)
        {
             if(row==0)
             {
                 ui->rawDataTable->item(row,column);
                 ui->rawDataTable->setItem(row,column,new QTableWidgetItem(rawHeaders.at(column)));
                 ui->rawDataTable->resizeColumnsToContents();
             }
             else
             {
                 ui->rawDataTable->item(row,column);
                 ui->rawDataTable->setItem(row,column,new QTableWidgetItem((dataList[row-1]).at(column)));
             }
        }
    }
    //ui->rawDataTable->
}
void MainWindow::on_textKeyA_clicked()
{
    TextWindow* txtwnd = TextWindow::getInstance();
    txtwnd->show();
    txtwnd->setTextAreaSelect(0);
    txtwnd->setInputMaxSize(KEY_SIZE);
}
void MainWindow::on_textKeyB_clicked()
{
    TextWindow* txtwnd = TextWindow::getInstance();
    txtwnd->show();
    txtwnd->setTextAreaSelect(1);
    txtwnd->setInputMaxSize(KEY_SIZE);
}
void MainWindow::on_textRWblocks_clicked()
{
    TextWindow* txtwnd = TextWindow::getInstance();
    txtwnd->show();
    txtwnd->setTextAreaSelect(2);
    txtwnd->setInputMaxSize(BLOCK_SIZE);
}

