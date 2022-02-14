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
#include <cstdint>
#include <QBitArray>
#include <QTableWidgetItem>
#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

     m_keyA = "FFFFFFFFFFFF"
    ,m_keyB = "FFFFFFFFFFFF"
             ,m_sectorTrailer[0] = {0b1111'1111},m_sectorTrailer[1] = {0b1111'1111},m_sectorTrailer[2] = {0b1111'1111},m_sectorTrailer[3] = {0b1111'1111},
                                                                                    m_sectorTrailer[4] = {0b1111'1111},m_sectorTrailer[5] = {0b1111'1111}
             ,m_sectorTrailer[6] = {0b1111'1111},m_sectorTrailer[7] = {0b0000'0111},m_sectorTrailer[8] = {0b1000'0000},m_sectorTrailer[9] = {0b0110'1001}
             ,m_sectorTrailer[10] = {0b1111'1111},m_sectorTrailer[11] = {0b1111'1111},m_sectorTrailer[12] = {0b1111'1111},m_sectorTrailer[13] = {0b1111'1111},
                                                                                      m_sectorTrailer[14] = {0b1111'1111},m_sectorTrailer[15] = {0b1111'1111};


    ui->setupUi(this);
    TextWindow* txtwnd = TextWindow::getInstance();
    connect(txtwnd, SIGNAL(listIsReady()) ,this , SLOT(applyDataFromTextWindow()));
    connect(txtwnd, SIGNAL(keyAIsReady()) ,this , SLOT(applyDataFromTextWindowToKeyA()));
    connect(txtwnd, SIGNAL(keyBIsReady()) ,this , SLOT(applyDataFromTextWindowToKeyB()));
    connect(txtwnd, SIGNAL(utilityKeyIsReady()) ,this , SLOT(applyDataFromTextWindowToUtilityKey()));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_connectReader_clicked()
{

    SCardConnection* connect = SCardConnection::getInstanceNew();
    LPTSTR readerList = NULL;

    if( connect->establishContext() != SCARD_S_SUCCESS )
    {
        ui->connectedReaderName->setText("Connection Failed!");
        ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : red; }");

        ui->UID->clear();
        ui->statusUID->clear();
        ui->UIDframe->setEnabled(false);
        ui->tabs->setEnabled(false);
        ui->disconnectUID->setEnabled(false);
    }
    else
    {   ui->commandTextWindow->append("EstablishContext()");
        if(connect->setReaderLists() != SCARD_S_SUCCESS)
            {
                ui->connectedReaderName->setText("Connection Failed");
                ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : red; }");
                ui->UID->clear();
                ui->statusUID->clear();
                MainWindow::availability(0xA0,0,0,0,0,0,0,0,0);
            }
        else
            {
            readerList = connect->getReaderLists();
            QString readerListStr = QString::fromWCharArray(readerList);
            qDebug() << readerListStr;

            if( readerListStr != NULL )
                {
                    ui->connectedReaderName->setText(readerListStr);
                    ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : green; }");
                    MainWindow::availability(0xA0,0xC0,0,0,0,0,0,0,0);
//                    ui->UIDframe->setEnabled(true);
//                    ui->disconnectReader->setEnabled((true));
//                    ui->connectReader->setEnabled(false);
//                    ui->Commands->setEnabled(choice::set);
//                    ui->commandTextWindow->setEnabled(true);
                    ui->commandTextWindow->append("ReaderConnect()");
                }


            }
    }
}
void MainWindow::on_disconnectReader_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    connect->disconnectReader();
    ui->connectedReaderName->clear();
    ui->commandTextWindow->append("ReaderDisconnectConnect()");
    MainWindow::availability(0xC0,0,0,0,0,0,0,0,0);
    ui->rawDataTable->clear();
    ui->commandTextWindow->clear();


}

void MainWindow::on_ConnectUID_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();

    if(connect->connectCard() != SCARD_S_SUCCESS)
        {
            ui->statusUID->setText("Failed to connect!");
            ui->statusUID->setStyleSheet("QLabel#statusUID {font-weight: bold; color : red; }");
            return;
        }
    BYTE *response;
    LONG lRet = connect->setCardUID();
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
            ui->statusUID->setText("Failed to read UID!");
            ui->statusUID->setStyleSheet("QLabel#statusUID {font-weight: bold; color : red; }");
            return;
        }
    ui->UID->setText(connect->getCardUID());
    ui->statusUID->setText("Connected.");
    ui->statusUID->setStyleSheet("QLabel#statusUID {font-weight: bold; color : green; }");
    MainWindow::availability(0xA0,0xA0,0xC4,0xBF,0xBF,0,0,0,0);
//      MainWindow::availability((SBframe|tabs|Operations|
//                                keyAframe|factoryKeyA|loadTo0A|loadTo1A|copyToKeyA|textKeyA|
//                                keyBframe|factoryKeyB|loadTo0B|loadTo1B|copyToKeyB|textKeyB|
//                                UIDframe|disconnectReader|disconnectUID), 0);

//      MainWindow::setKeyAFrameEnable(0b1111'1101);
//      MainWindow::setKeyAFrameEnable(0b1111'1101);
      //    ui->SBframe->setEnabled(choice::set);
//    ui->keyAframe->setEnabled(choice::set);
//    ui->keyBframe->setEnabled(choice::set);
//    ui->tabs->setEnabled(choice::set);
//    ui->Operations->setEnabled(choice::set);
//    ui->disconnectUID->setEnabled(choice::set);
//    ui->RAW->setEnabled(true);
//    ui->Utility->setEnabled(choice::clear);
    ui->commandTextWindow->append("UIDConnect()");
}
void MainWindow::on_disconnectUID_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    if(connect->disconnectCard() != SCARD_S_SUCCESS)
        {
            ui->statusUID->setText("Failed to disconnected!");
            ui->statusUID->setStyleSheet("QLabel#statusUID {font-weight: bold; color : red; }");
            return;
        }
    ui->UID->clear();
    ui->statusUID->setText("Disconnected.");
    ui->statusUID->setStyleSheet("QLabel#statusUID {font-weight: bold; color : green; }");
    MainWindow::availability(0xA0,0xC0,0,0,0,0,0,0,0);
    ui->statusA->clear();
    ui->statusB->clear();
    ui->statusRW->clear();
    ui->commandTextWindow->append("UIDDisconnect()");
    ui->tabs->setCurrentIndex(0);
    MainWindow::on_RWClear_clicked();
    ui->rawDataTable->clear();
    ui->commandTextWindow->clear();
}

void MainWindow::on_loadTo0A_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};
    MainWindow::setKeyA();
    QString _keyA = MainWindow::getKeyA();
    QByteArray _keyBytes = QByteArray::fromHex(_keyA.toLatin1());
    BYTE keyA[KEY_SIZE] = {};
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            keyA[i] = _keyBytes[i];
        }
    scrdops.setKeyA(keyA);
    BYTE storageAddress = V_MEMORY;
    apdu.setLoadKeyCommand(scrdops.getKeyA() , storageAddress);
    BYTE *response = connect->getResponse();
    LONG lRet = connect->loadKey(apdu.getLoadKeyCommand());

    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
            ui->statusA->setText("Failed to load key!");
            ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : red; }");
            return;
        }
        ui->statusA->setText("Key loaded.");
        ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : green; }");
        ui->commandTextWindow->append("KeyALoadToVolatileMemory()");
        MainWindow::availability(0xA0,0xA0,0xC4,0xFF,0xBF,0,0,0,0);
}
void MainWindow::on_loadTo1A_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};
    MainWindow::setKeyA();
    QString _keyA = MainWindow::getKeyA();
    BYTE keyA[KEY_SIZE] = {};
    QByteArray _keyBytes = QByteArray::fromHex(_keyA.toLatin1());
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            keyA[i] = _keyBytes[i];
        }
    scrdops.setKeyA(keyA);
    BYTE storageAddress = NV_MEMORY;
    apdu.setLoadKeyCommand(scrdops.getKeyA() , storageAddress);
    BYTE *response = connect->getResponse();;
    LONG lRet = connect->loadKey(apdu.getLoadKeyCommand());
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
            ui->statusA->setText("Failed to load key!");
            ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : red; }");
            return;
        }
            ui->statusA->setText("Key loaded.");
            ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : green; }");
            ui->commandTextWindow->append("KeyALoadToNonVolatileMemory()");
            MainWindow::availability(0xA0,0xA0,0xC4,0xFF,0xBF,0,0,0,0);

}
void MainWindow::on_loadTo0B_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};
    MainWindow::setKeyB();
    QString _keyB = MainWindow::getKeyB();
    BYTE keyB[KEY_SIZE] = {};
    QByteArray _keyBytes = QByteArray::fromHex(_keyB.toLatin1());
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            keyB[i] = _keyBytes[i];
        }
    scrdops.setKeyB(keyB);
    BYTE storageAddress = V_MEMORY;
    apdu.setLoadKeyCommand(scrdops.getKeyB() , storageAddress);
    BYTE *response = connect->getResponse();
    LONG lRet = connect->loadKey(apdu.getLoadKeyCommand());
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
            ui->statusB->setText("Failed to load key!");
            ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : red; }");
            return;
        }

            ui->statusB->setText("Key loaded.");
            ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : green; }");
            ui->commandTextWindow->append("KeyBLoadToNonVolatileMemory()");
            MainWindow::availability(0xA0,0xA0,0xC4,0xBF,0xFF,0,0,0,0);

}
void MainWindow::on_loadTo1B_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};
    MainWindow::setKeyB();
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
    BYTE *response = connect->getResponse();
    LONG lRet = connect->loadKey(apdu.getLoadKeyCommand());
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
            ui->statusB->setText("Failed to load key!");
            ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : red; }");
            return;
        }

            ui->statusB->setText("Key loaded.");
            ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : green; }");
            ui->commandTextWindow->append("KeyBLoadToNonVolatileMemory()");
            MainWindow::availability(0xA0,0xA0,0xC4,0xBF,0xFF,0,0,0,0);
}

void MainWindow::on_authWithKeyA_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    QString blockString = ui->blockSelect->text();
    connect->setBlockNum(blockString);

    apdu.setAuthCommand(connect->getBlockNum(), KEYA_SELECT);
    LONG lRet = connect->authenticate(apdu.getAuthCommand());
    BYTE *response = connect->getResponse();
    if((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1]))
     {
        ui->statusA->setText("Failed to authenticate!");
        ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : red; }");
        ui->commandTextWindow->append("AuthenticateWithKeyA()");
        MainWindow::on_RWClear_clicked();
        return;
     }

        ui->statusA->setText("Authenticated.");
        ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : green; }");
        MainWindow::setKeyA();
        MainWindow::availability(0xA0,0xA0,0xFF,0xFF,0xBF,0xBF,0x83,0x80,0);
        ui->utilityBlock->setText(blockString);
        ui->commandTextWindow->append("AuthenticateWithKeyA()");



}
void MainWindow::on_authWithKeyB_clicked()
{

        SCardConnection* connect = SCardConnection::getInstance();
        APDUCommand apdu{};
        QString blockString =(ui->blockSelect->text());
        connect->setBlockNum(blockString);

        apdu.setAuthCommand(connect->getBlockNum(), KEYB_SELECT);

        BYTE *response;
        LONG lRet = connect->authenticate(apdu.getAuthCommand());
        response = connect->getResponse();
        if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
            {
                ui->statusB->setText("Failed to authenticate!");
                ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : red; }");
                ui->commandTextWindow->append("AuthenticateWithKeyB()");
                return;
            }

            ui->statusB->setText("Authenticated.");
            ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : green; }");
            MainWindow::setKeyB();
            MainWindow::availability(0xA0,0xA0,0xFF,0xBF,0xFF,0xBF,0x83,0x80,0);
            ui->utilityBlock->setText(blockString);
            ui->commandTextWindow->append("AuthenticateWithKeyB()");
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
    MainWindow::on_RWClear_clicked();
    BYTE *response;
    LONG lRet = connect->readDataBlock(apdu.getReadCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {

        ui->statusRW->setText("Failed  to read !");
        ui->statusRW->setStyleSheet("QLabel#statusRW {font-weight: bold; color : red; }");

        return;
    }
            QStringList dataList = connect->getReadDataBlockString().split(' ');
            MainWindow::applyDataToReadBLocks(dataList);
            ui->statusRW->setText("Read successfully.");
            ui->statusRW->setStyleSheet("QLabel#statusRW {font-weight: bold; color : green; }");
            txtwnd->setTextWindowTextReadOnly(true);
            ui->commandTextWindow->append("ReadBlock()");
            MainWindow::availability(0xA0,0xA0,0xFF,0xBF,0xFF,0xFF,0x83,0x80,0);

}
void MainWindow::on_writeBlock_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    QString blockString = (ui->blockSelect->text());
    connect->setBlockNum(blockString);
    if((connect->getBlockNum()+1)%4 == 0 )
        {
            ui->statusRW->setText("Cannot write to sector trailer!");
            ui->statusRW->setStyleSheet("QLabel#statusRW {font-weight: bold; color : red; }");
            return;
        }
    QString _writeBlock = MainWindow::getWriteBlocks();
    QByteArray _writeBlockBytes = QByteArray::fromHex(_writeBlock.toLatin1());
    BYTE writeBlock[BLOCK_SIZE];
    for( int i=0 ; i<static_cast<int>(BLOCK_SIZE) ; i++ )
    {
        writeBlock[i] = _writeBlockBytes[i];
    }

    apdu.setWriteCommand(connect->getBlockNum(), writeBlock);
    BYTE *response;
    LONG lRet = connect->writeDataBlock(apdu.getWriteCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
        ui->statusRW->setText("Failed to write!");
        ui->statusRW->setStyleSheet("QLabel#statusRW {font-weight: bold; color : red; }");
        return;
        }

        ui->statusRW->setText("Written successfully.");
        ui->statusRW->setStyleSheet("QLabel#statusRW {font-weight: bold; color : green; }");
        ui->commandTextWindow->append("WriteBlock()");
        MainWindow::availability(0xA0,0xA0,0xFF,0xBF,0xFF,0xFF,0x83,0x80,0);

}
void MainWindow::on_rawGO_clicked()
{

    QAbstractButton *keyButton = ui->rawKeySelectGroup->checkedButton();
    QAbstractButton *formatButton = ui->rawFormatSelectGroup->checkedButton();
    QString _keyA = MainWindow::getKeyA();
    QByteArray _keyBytes = QByteArray::fromHex(_keyA.toLatin1());

    bool hexFormat = 1;
    bool asciiFormat = 0;

     if(keyButton == ui->rawCheckKeyA && formatButton == ui->rawCheckHex)
         MainWindow::printRawTable(MainWindow::authAndReadAllData(_keyBytes,V_MEMORY,KEYA_SELECT),hexFormat);
     if(keyButton == ui->rawCheckKeyA && formatButton == ui->rawCheckASCII)
         MainWindow::printRawTable(MainWindow::authAndReadAllData(_keyBytes,V_MEMORY,KEYA_SELECT),asciiFormat);

     if(keyButton == ui->rawCheckKeyB && formatButton == ui->rawCheckHex)
         MainWindow::printRawTable(MainWindow::authAndReadAllData(_keyBytes,V_MEMORY,KEYB_SELECT),hexFormat);
     if(keyButton == ui->rawCheckKeyB && formatButton == ui->rawCheckASCII)
         MainWindow::printRawTable(MainWindow::authAndReadAllData(_keyBytes,V_MEMORY,KEYB_SELECT),asciiFormat);



    ui->commandTextWindow->append("ReadAllData()");

}
QVector<QStringList> MainWindow::authAndReadAllData(const QByteArray &_keyBytes,const BYTE &storageSelect,
                                                                                const BYTE &keySelect)
{
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    SCardOperations scrdops{};

    QString sectorStr;
    int sectorNum = -1;
    QString recievedData{};
    QStringList recievedDataSplit{};
    QVector<QStringList> dataList;
    BYTE key[KEY_SIZE] = {};
    BYTE *response;

    for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
    {
        key[i] = _keyBytes[i];
    }
    if(keySelect == KEYA_SELECT)
    {
        scrdops.setKeyA(key);
        apdu.setLoadKeyCommand(scrdops.getKeyA() , storageSelect);
    }
    if(keySelect == KEYB_SELECT)
    {
        scrdops.setKeyB(key);
        apdu.setLoadKeyCommand(scrdops.getKeyB() , storageSelect);
    }

    LONG lRet = connect->loadKey(apdu.getLoadKeyCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
        ui->statusRAW->setText("Failed to read!");
        ui->statusRAW->setStyleSheet("QLabel#statusRAW {font-weight: bold; color : red; }");
        return dataList;
    }

            QProgressDialog progress;
            progress.setMinimum(0);
            progress.setMaximum(64);
            progress.setLabelText("         Reading data...         ");
            progress.setCancelButton(0);
            progress.resize(250,60);
            progress.setWindowFlags( Qt::CustomizeWindowHint );
            progress.setWindowModality(Qt::ApplicationModal);
            progress.setFixedSize(progress.geometry().width(),progress.geometry().height());

    progress.show();
    MainWindow::setEnabled((false));
    for(DWORD i = 0; i<TOTALBLOCK_SIZE; i++)
        {
        QCoreApplication::processEvents();
        progress.setValue(i);
        Sleep(250);
        QString blockStr = QString::number(i);
        connect->setBlockNum(blockStr);
        if(i%4 == 0)
            {
                sectorNum++;
                sectorStr = QString::number(i/4);
                apdu.setAuthCommand(connect->getBlockNum(), keySelect);
                lRet = connect->authenticate(apdu.getAuthCommand());
                response = connect->getResponse();
                if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
                {
                        for(DWORD k = 0 ; k<BLOCK_SIZE ; k++ )recievedData.push_front(" \0 ");

                }
            }
            apdu.setReadCommand(connect->getBlockNum());
            recievedData = "";
            lRet = connect->readDataBlock(apdu.getReadCommand());
            response = connect->getResponse();
            if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
                {
                    for(DWORD k = 0 ; k<BLOCK_SIZE-1 ; k++ )  recievedData.append(" \0 ");
                 }
            else
                {
                recievedData = connect->getReadDataBlockString();
                }
                recievedData.push_front(" "+blockStr+" ");

                if(i%4 != 0)recievedData.push_front("\0");
                else recievedData.push_front(sectorStr);

                recievedDataSplit = recievedData.split(' ');
                dataList.append(recievedDataSplit);
    }
    progress.close();
    MainWindow::setEnabled((true));
    progress.deleteLater();
    return dataList;
}
void MainWindow::printRawTable(const QVector<QStringList> &dataList, const bool formatSelect)
{
    if(dataList.size()!=64) return;
    QStringList columnHeaders = {"Sector","Block","B0","B1","B2","B3","B4","B5"
                             ,"B6","B7","B8","B9","B10","B11","B12","B13","B14","B15" };
    QFont font; font.setBold(true);


    ui->rawDataTable->clear();
    ui->rawDataTable->setVisible(true);
    ui->rawDataTable->setShowGrid(true);
    ui->rawDataTable->showGrid();

    if(!formatSelect)
    {
        for(DWORD row = 0; row< TOTALBLOCK_SIZE+1;row++)
        {
            ui->rawDataTable->insertRow( row );

            for(DWORD column = 0; column<BLOCK_SIZE+(DWORD)2; column++)
            {
                 if(row==0)
                 {
                     ui->rawDataTable->item(row,column);
                     ui->rawDataTable->setItem(row,column,new QTableWidgetItem(columnHeaders.at(column)));
                      ui->rawDataTable->item(row,column)->QTableWidgetItem::setBackground(QColor(QRgb(0xEFE9E5)));
                     ui->rawDataTable->item(row,column)->setFont(font);
                 }
                 else
                 {
                     if(column == 0 || column == 1)
                     {
                         ui->rawDataTable->item(row,column);
                         ui->rawDataTable->setItem(row,column,new QTableWidgetItem((dataList[row-1]).at(column)));
                         ui->rawDataTable->item(row,column)->setFont(font);
                         if((row)%4 ==0) ui->rawDataTable->item(row,column)->QTableWidgetItem::setBackground(QColor(QRgb(0xF7F4F2)));
                     }
                     else
                     {
                         QString dataStr = (dataList[row-1][column]);
                         QString asciiValue = QString::fromLocal8Bit(QByteArray::fromHex(dataStr.toLatin1()));
                         ui->rawDataTable->item(row,column);
                         ui->rawDataTable->setItem(row,column,new QTableWidgetItem(asciiValue));
                         if((row)%4 ==0) ui->rawDataTable->item(row,column)->QTableWidgetItem::setBackground(QColor(QRgb(0xF7F4F2)));
                     }
                 }
            }
        }
    }
    else
    {
        for(DWORD row = 0; row< TOTALBLOCK_SIZE+1;row++)
        {
            ui->rawDataTable->insertRow( row );
            for(DWORD column = 0; column<BLOCK_SIZE+(DWORD)2; column++)
            {
                 if(row==0)
                 {
                     ui->rawDataTable->item(row,column);
                     ui->rawDataTable->setItem(row,column,new QTableWidgetItem(columnHeaders.at(column)));
                     ui->rawDataTable->item(row,column)->QTableWidgetItem::setBackground(QColor(QRgb(0xEFE9E5)));
                     ui->rawDataTable->item(row,column)->setFont(font);
                 }
                 else
                 {
                     if(column == 0 || column == 1)
                        {
                         ui->rawDataTable->item(row,column);
                         ui->rawDataTable->setItem(row,column,new QTableWidgetItem((dataList[row-1]).at(column)));
                         ui->rawDataTable->item(row,column)->setFont(font);
                         if((row)%4 ==0) ui->rawDataTable->item(row,column)->QTableWidgetItem::setBackground(QColor(QRgb(0xF7F4F2)));
                        }
                     else
                        {
                         if(dataList[row-1].at(column) != '\0' )
                             {
                                 ui->rawDataTable->item(row,column);
                                 ui->rawDataTable->setItem(row,column,new QTableWidgetItem((dataList[row-1]).at(column)));
                                 if((row)%4 ==0) ui->rawDataTable->item(row,column)->QTableWidgetItem::setBackground(QColor(QRgb(0xF7F4F2)));
                             }
                         else
                         {
                             ui->rawDataTable->item(row,column);
                             ui->rawDataTable->setItem(row,column,new QTableWidgetItem((dataList[row-1]).at(column)));
                             ui->rawDataTable->item(row,column)->QTableWidgetItem::setBackground(QColor(QRgb(0x858280)));
                         }
                        }

                 }
            }
        }
    }
    ui->statusRAW->clear();
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

void MainWindow::on_writeVB_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    QString blockString = (ui->blockSelect->text());
    if((blockString.toInt()+1)%4 == 0 )
    {
        ui->statusVB->setText("Cannot format sector trailer as value block!");
        ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
        ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");
        return;
    }
    QString valueStr =( (ui->valueBlockInit->toPlainText()).toLocal8Bit() );
    QString valueHexStr;
    valueHexStr.setNum(valueStr.toInt(),16);
    if(valueHexStr.length() %2)   valueHexStr.insert(0,QLatin1String("0"));
    valueHexStr = valueHexStr.toUpper();
    QByteArray blockHexByteArray = QByteArray::fromHex(valueHexStr.toLatin1());
    BYTE valueNum[4]{0x00, 0x00, 0x00, 0x00};
    std::reverse(blockHexByteArray.begin(),blockHexByteArray.end());
    qDebug() << blockHexByteArray;
    qDebug() << blockHexByteArray.length();
//    qDebug() <<
    for( int i = 0; i<blockHexByteArray.length();i++)
    {
        valueNum[i] |= (BYTE)blockHexByteArray[i];

    }


    connect->setBlockNum(blockString);

    apdu.setValueBlockCommand(connect->getBlockNum(),valueNum);

    LONG lRet = connect->writeDataBlock(apdu.getWriteCommand());
    BYTE *response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
      ui->statusVB->setText("Failed to format as value block!");
      ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
      ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");
      MainWindow::availability(0xA0,0xA0,0xFF,0xBF,0xFF,0xFF,0x83,0x80,0);
      return;
    }
    ui->statusVB->setText("Succesfully formated as value block.");
    ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : green; }");
    ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");
    MainWindow::availability(0xA0,0xA0,0xFF,0xFF,0xBF,0xFF,0xFF,0x80,0);

}
void MainWindow::on_readVB_clicked()
{
    APDUCommand apdu{};
    SCardConnection* connect = SCardConnection::getInstance();
    QString blockString = (ui->blockSelect->text());

    connect->setBlockNum(blockString);
    apdu.setReadValueBlockCommand(connect->getBlockNum());


    LONG lRet = connect->readValueBlock(apdu.getReadCommand());
    BYTE *response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
            ui->textVB->setText("Fail!");
            MainWindow::availability(0xA0,0xA0,0xFF,0xBF,0xFF,0xFF,0x83,0x80,0);
        }
    else
       {

        int receivedData = connect->getValue();
        qDebug() << receivedData;
        QString valueStr = QString::number(receivedData);
        ui->textVB->setText(valueStr);
        MainWindow::availability(0xA0,0xA0,0xFF,0xFF,0xBF,0xFF,0xFF,0x80,0);
        }

}

void MainWindow::on_utilityKCChange_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    SCardOperations scrdops{};
    QAbstractButton *usingKey = ui->utilityUsingKeyGroup->checkedButton();
    QAbstractButton *changeKey = ui->utilityChangeKeyGroup->checkedButton();

    BYTE key[KEY_SIZE] = {};
    BYTE keySelect = KEYA_SELECT;

    if(usingKey == (ui->utilityUsingKeyA))
    {
        MainWindow::setKeyA();
        QString _key = MainWindow::getKeyA();
        QByteArray _keyBytes = QByteArray::fromHex(_key.toLatin1());
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            key[i] = _keyBytes[i];
        }
        scrdops.setKeyA(key);
        apdu.setLoadKeyCommand(scrdops.getKeyA() , V_MEMORY);
        keySelect = KEYA_SELECT;
    }
    if(usingKey == (ui->utilityUsingKeyB))
    {
        MainWindow::setKeyB();
        QString _key = MainWindow::getKeyB();
        QByteArray _keyBytes = QByteArray::fromHex(_key.toLatin1());
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            key[i] = _keyBytes[i];
        }
        scrdops.setKeyB(key);
        apdu.setLoadKeyCommand(scrdops.getKeyB() , V_MEMORY);
        keySelect = KEYB_SELECT;
    }
    LONG lRet = connect->loadKey(apdu.getLoadKeyCommand());
    BYTE* response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
        ui->statusUtilityKC->setText("Failed!");
        ui->statusUtilityKC->setStyleSheet("QLabel#statusUtilityKC {font-weight: bold; color : red; }");
         return;
    }

    for(int i = (ui->sectorBegin->value()); i<=(ui->sectorEnd->value()); i++)
        {
                QString blockStr = QString::number((i*4)+3);
                connect->setBlockNum(blockStr);
                BYTE block = connect->getBlockNum();
                apdu.setAuthCommand(block, keySelect);

                LONG lRet = connect->authenticate(apdu.getAuthCommand());
                BYTE* response = connect->getResponse();
              if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
                {
                  ui->statusUtilityKC->setText("Failed!");
                  ui->statusUtilityKC->setStyleSheet("QLabel#statusUtilityKC {font-weight: bold; color : red; }");
                    return;
                }

                apdu.setReadCommand(block);
                lRet = connect->readDataBlock(apdu.getReadCommand());
                response = connect->getResponse();
               if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
                {
                   ui->statusUtilityKC->setText("Failed!");
                   ui->statusUtilityKC->setStyleSheet("QLabel#statusUtilityKC {font-weight: bold; color : red; }");
                    return;
                }
  //PROBLEM HERE !!!!!
             //  m_sectorTrailer = *(i+connect->getBlockAsByte());
               for( int i=0 ; i<static_cast<int>(BLOCK_SIZE) ; i++ )
               {
                  // m_sectorTrailer[i] = *(connect->getBlockAsByte()+i);
                   qDebug() << "before change: " <<*(m_sectorTrailer+i);
               }
               QString _sectorTrailerString = connect->getReadDataBlockString();
               QByteArray _sectorTrailerBlock = QByteArray::fromHex(_sectorTrailerString.toLatin1());
               BYTE _sectorTrailer[BLOCK_SIZE];

               BYTE keyB[KEY_SIZE];
               BYTE keyA[KEY_SIZE];


                       QString _keyA = MainWindow::getKeyB();
                       QByteArray _keyABytes = QByteArray::fromHex(_keyA.toLatin1());
                       QString _keyB = MainWindow::getKeyB();
                       QByteArray _keyBBytes = QByteArray::fromHex(_keyB.toLatin1());

                       for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
                       {
                           keyA[i] = _keyABytes[i];
                           keyB[i] = _keyBBytes[i];
                       }

               for( int i=0 ; i<static_cast<int>(BLOCK_SIZE) ; i++ )
               {
                   _sectorTrailer[i] = _sectorTrailerBlock[i];
               }
               for(int i = 0; i<(static_cast<int>(BLOCK_SIZE)) ; i++)
                 {
                        if(i<6)
                       {
                           m_sectorTrailer[i] = keyA[i];
                       }
                        if(6<=i && i<10)
                       {
                           m_sectorTrailer[i] = _sectorTrailer[i];
                       }
                         if(10<=i && i<static_cast<int>(BLOCK_SIZE))
                       {
                           m_sectorTrailer[i] = keyB[i-10];
                       }
                 }
               for( int i=0 ; i<static_cast<int>(BLOCK_SIZE) ; i++ )
               {
                   qDebug() << "after change: " <<*(m_sectorTrailer+i);
               }


               if(changeKey == ui->utilityChangeKeyA)
                    {
                        MainWindow::constructKeys(KEYA_SELECT);
                    }
                if(changeKey == ui->utilityChangeKeyB)
                    {
                       MainWindow::constructKeys(KEYB_SELECT);
                    }

                apdu.setWriteCommand(i*4+3,m_sectorTrailer);
                connect->writeDataBlock(apdu.getWriteCommand());
                lRet = connect->authenticate(apdu.getAuthCommand());
                response = connect->getResponse();
              if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
                {
                  ui->statusUtilityKC->setText("Failed!");
                  ui->statusUtilityKC->setStyleSheet("QLabel#statusUtilityKC {font-weight: bold; color : red; }");
                    return;
                }

                ui->statusUtilityKC->setText("Success.");
                ui->statusUtilityKC->setStyleSheet("QLabel#statusUtilityKC {font-weight: bold; color : green; }");
        }
}
void MainWindow::on_commandsClear_clicked()
{
    ui->commandTextWindow->clear();
}

void MainWindow::on_readAccessConditions_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};

    QString blockString = (ui->blockSelect->text());
    connect->setBlockNum(blockString);
    apdu.setReadCommand(connect->getBlockNum());

    int indexOfSectorTrailer = blockString.toInt();
    if((indexOfSectorTrailer+1)%4 != 0)
    {
        while((indexOfSectorTrailer+1)%4 != 0)
        {
        indexOfSectorTrailer++;
        }
        connect->setBlockNum(QString::number(indexOfSectorTrailer));
        apdu.setReadCommand(connect->getBlockNum());

        QString sectorTrailer;
        BYTE *response;
        LONG lRet = connect->readDataBlock(apdu.getReadCommand());
        response = connect->getResponse();
       if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
            ui->statusAC->setText("Could not read!");
            ui->statusAC->setStyleSheet("QLabel#statusAC {font-weight:bold; color:red;}");
            return;
        }


        sectorTrailer = connect->getReadDataBlockString();
        QByteArray byteList = QByteArray::fromHex(sectorTrailer.toLatin1());
        BYTE B8 = byteList.at(8);
        BYTE B7 = byteList.at(7);

        if(  !(B7 & mask6) &&  !(B8 & mask2) &&  !(B8 & mask6)  ) ui->accessCondition->setText("read A/B - write A/B - increment A/B - decrement,transfer,restore A/B [transport config]");
        //   0  0  0
        if(  !(B7 & mask6) &&   (B8 & mask2) &&  !(B8 & mask6) ) ui->accessCondition->setText("read A/B - write N- increment N - decrement,transfer,restore N [r/w]");
        //   0  1  0
        if(   (B7 & mask6) &&  !(B8 & mask2) &&  !(B8 & mask6) ) ui->accessCondition->setText("read A/B - write B - increment N - decrement,transfer,restore N [r/w]");
        //   1  0  0
        if(   (B7 & mask6) &&   (B8 & mask2) &&  !(B8 & mask6) ) ui->accessCondition->setText("read A/B - write B- increment B - decrement,transfer,restore A/B [value block]");
        //   1  1  0
        if(  !(B7 & mask6) &&  !(B8 & mask2) &&   (B8 & mask6) ) ui->accessCondition->setText("read A/B - write N - increment N - decrement,transfer,restore A/B [value block]");
        //   0  0  1       
        if(  !(B7 & mask6) &&   (B8 & mask2) &&   (B8 & mask6) ) ui->accessCondition->setText("read B - write B- increment N - decrement,transfer,restore N [r/w]");
        //   0  1  1        
        if(   (B7 & mask6) &&  !(B8 & mask2) &&   (B8 & mask6) ) ui->accessCondition->setText("read B - write (never)- increment (never) - decrement,transfer,restore (never) [r/w]");
        //   1  0  1        
        if(   (B7 & mask6) &&   (B8 & mask2) &&   (B8 & mask6) ) ui->accessCondition->setText("read (never) - write (never)- increment (never) - decrement,transfer,restore (never) [r/w]");
        //   1  1  1

         ui->statusAC->setText("Access Conditions Read!");
         ui->statusAC->setStyleSheet("QLabel#statusAC {font-weight:bold; color:green;}");
        ui->accessCondition->setStyleSheet("QLineEdit#accessCondition {font-weight:bold; color:green;}");
        ui->accessConditionSTRead->clear();
        MainWindow::availability(0xA0,0xA0,0xFF,0xFF,0xBF,0xFF,0xFF,0xF0,0);


    }
    else
    {
        connect->setBlockNum(QString::number(indexOfSectorTrailer));
        apdu.setReadCommand(connect->getBlockNum());

        QString sectorTrailer;
        BYTE *response;
        LONG lRet = connect->readDataBlock(apdu.getReadCommand());
        response = connect->getResponse();
       if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
           ui->statusAC->setText("Could not read!");
           ui->statusAC->setStyleSheet("QLabel#statusAC {font-weight:bold; color:red;}");
            return;
        }
        sectorTrailer = connect->getReadDataBlockString();
        QByteArray byteList = QByteArray::fromHex(sectorTrailer.toLatin1());
        qDebug() << byteList.at(7) << " " << byteList.at(8);
        BYTE B8 = byteList.at(8);
        BYTE B7 = byteList.at(7);
        //qDebug() << B7 << " " << B8;
        if(  !(B7 & mask7) &&  !(B8 & mask3) && !(B8 & mask7) )
            ui->accessConditionSTRead->setText("KeyA[read(never),write(A)], access-bits[read(A),write(never)], KeyB[read(A),write(A)]");
        //   0  0  0
        else if(  !(B7 & mask7) &&  !(B8 & mask3) &&  (B8 & mask7) )
            ui->accessConditionSTRead->setText("KeyA[read(never),write(A)], access-bits[read(A),write(A)], KeyB[read(A),write(A)]");
        //   0  0  1
        else if(  !(B7 & mask7) &&   (B8 & mask3) && !(B8 & mask7) )
            ui->accessConditionSTRead->setText("KeyA[read(never),write(never)], access-bits[read(A),write(never)], KeyB[read(A),write(never)]");
        //   0  1  0
        else if(  !(B7 & mask7) &&   (B8 & mask3) &&  (B8 & mask7) )
            ui->accessConditionSTRead->setText("KeyA[read(never),write(B)], access-bits[read(A/B),write(B)], KeyB[read(never),write(B)]");
        //   0  1  1
        else if(   (B7 & mask7) &&  !(B8 & mask3) && !(B8 & mask7) )
            ui->accessConditionSTRead->setText("KeyA[read(never),write(B)], access-bits[read(A/B),write(never)], KeyB[read(never),write(B)]");
        //   1  0  0
        else if(   (B7 & mask7) &&  !(B8 & mask3) &&  (B8 & mask7) )
            ui->accessConditionSTRead->setText("KeyA[read(never),write(never)], access-bits[read(A/B),write(B)], KeyB[read(never),write(never)]");
        //   1  0  1
        else if(   (B7 & mask7) &&   (B8 & mask3) && !(B8 & mask7) )
            ui->accessConditionSTRead->setText("KeyA[read(never),write(never)], access-bits[read(A/B),write(never)], KeyB[read(never),write(never)]");
        //   1  1  0
        else if(   (B7 & mask7) &&   (B8 & mask3) &&  (B8 & mask7) )
            ui->accessConditionSTRead->setText("KeyA[read(never),write(never)], access-bits[read(A),write(never)], KeyB[read(never),write(never)]");
        //   1  1  1
        ui->statusAC->setText("Access Conditions Read!");
        ui->statusAC->setStyleSheet("QLabel#statusAC {font-weight:bold; color:green;}");
       ui->accessConditionST->setStyleSheet("QLineEdit#accessConditionST {font-weight:bold; color:red;}");
        ui->accessCondition->clear();
        MainWindow::availability(0xA0,0xA0,0xFF,0xFF,0xBF,0xFF,0xFF,0x8F,0XFF);

    }
    ui->commandTextWindow->append("ReadAccessConditions()");
}
void MainWindow::on_accessConditionST_currentIndexChanged(int index)
{

    switch (index)
    {
    case 0:
        m_sectorTrailer[6] &= ~(mask7 | mask3);
        m_sectorTrailer[7] &= ~(mask7 | mask3);
        m_sectorTrailer[8] &= ~(mask7 | mask3);

        m_sectorTrailer[6] |= (0b1000'1000);
        m_sectorTrailer[7] |= (0b0000'1000);
        m_sectorTrailer[8] |= (0b0000'0000);
        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 1:
        m_sectorTrailer[6] &= ~(mask7 | mask3);
        m_sectorTrailer[7] &= ~(mask7 | mask3);
        m_sectorTrailer[8] &= ~(mask7 | mask3);


        m_sectorTrailer[6] |= (0b0000'1000);
        m_sectorTrailer[7] |= (0b0000'1000);
        m_sectorTrailer[8] |= (0b0000'1000);

        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 2:
        m_sectorTrailer[6] &= ~(mask7 | mask3);
        m_sectorTrailer[7] &= ~(mask7 | mask3);
        m_sectorTrailer[8] &= ~(mask7 | mask3);

        m_sectorTrailer[6] |= (0b1000'0000);
        m_sectorTrailer[7] |= (0b1000'1000);
        m_sectorTrailer[8] |= (0b0000'0000);

        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 3:
        m_sectorTrailer[6] &= ~(mask7 | mask3);
        m_sectorTrailer[7] &= ~(mask7 | mask3);
        m_sectorTrailer[8] &= ~(mask7 | mask3);

        m_sectorTrailer[6] |= (0b0000'0000);
        m_sectorTrailer[7] |= (0b1000'1000);
        m_sectorTrailer[8] |= (0b0000'1000);
        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 4:
        m_sectorTrailer[6] &= ~(mask7 | mask3);
        m_sectorTrailer[7] &= ~(mask7 | mask3);
        m_sectorTrailer[8] &= ~(mask7 | mask3);

        m_sectorTrailer[6] |= (0b1000'1000);
        m_sectorTrailer[7] |= (0b0000'0000);
        m_sectorTrailer[8] |= (0b1000'0000);
        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 5:
        m_sectorTrailer[6] &= ~(mask7 | mask3);
        m_sectorTrailer[7] &= ~(mask7 | mask3);
        m_sectorTrailer[8] &= ~(mask7 | mask3);

        m_sectorTrailer[6] |= (0b0000'1000);
        m_sectorTrailer[7] |= (0b0000'0000);
        m_sectorTrailer[8] |= (0b1000'1000);
        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 6:
        m_sectorTrailer[6] &= ~(mask7 | mask3);
        m_sectorTrailer[7] &= ~(mask7 | mask3);
        m_sectorTrailer[8] &= ~(mask7 | mask3);

        m_sectorTrailer[6] |= (0b1000'0000);
        m_sectorTrailer[7] |= (0b1000'0000);
        m_sectorTrailer[8] |= (0b1000'0000);
        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 7:
        m_sectorTrailer[6] &= ~(mask7 | mask3);
        m_sectorTrailer[7] &= ~(mask7 | mask3);
        m_sectorTrailer[8] &= ~(mask7 | mask3);

        m_sectorTrailer[6] |= (0b0000'0000);
        m_sectorTrailer[7] |= (0b1000'0000);
        m_sectorTrailer[8] |= (0b1000'1000);
        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    }
}
void MainWindow::on_accessConditionDB_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        m_sectorTrailer[6] &= (mask7 | mask3); //not necessary
        m_sectorTrailer[7] &= (mask7 | mask3);
        m_sectorTrailer[8] &= (mask7 | mask3);

        m_sectorTrailer[6] |= (0b0111'0111);
        m_sectorTrailer[7] |= (0b0000'0111);
        m_sectorTrailer[8] |= (0b0000'0000);


        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 1:
        m_sectorTrailer[6] &= (mask7 | mask3);
        m_sectorTrailer[7] &= (mask7 | mask3);
        m_sectorTrailer[8] &= (mask7 | mask3);

        m_sectorTrailer[6] |= (0b0000'0111);
        m_sectorTrailer[7] |= (0b0000'0111);
        m_sectorTrailer[8] |= (0b0000'0111);

        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 2:
        m_sectorTrailer[6] &= (mask7 | mask3);
        m_sectorTrailer[7] &= (mask7 | mask3);
        m_sectorTrailer[8] &= (mask7 | mask3);

        m_sectorTrailer[6] |= (0b0111'0000);
        m_sectorTrailer[7] |= (0b0111'0111);
        m_sectorTrailer[8] |= (0b0000'0000);

        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 3:
        m_sectorTrailer[6] &= (mask7 | mask3);
        m_sectorTrailer[7] &= (mask7 | mask3);
        m_sectorTrailer[8] &= (mask7 | mask3);

        m_sectorTrailer[6] |= (0b0000'0000);
        m_sectorTrailer[7] |= (0b0111'0111);
        m_sectorTrailer[8] |= (0b0000'0111);

        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 4:
        m_sectorTrailer[6] &= (mask7 | mask3);
        m_sectorTrailer[7] &= (mask7 | mask3);
        m_sectorTrailer[8] &= (mask7 | mask3);

        m_sectorTrailer[6] |= (0b0111'0111);
        m_sectorTrailer[7] |= (0b0000'0000);
        m_sectorTrailer[8] |= (0b0111'0000);

        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 5:
        m_sectorTrailer[6] &= (mask7 | mask3);
        m_sectorTrailer[7] &= (mask7 | mask3);
        m_sectorTrailer[8] &= (mask7 | mask3);

        m_sectorTrailer[6] |= (0b0000'0111);
        m_sectorTrailer[7] |= (0b0000'0000);
        m_sectorTrailer[8] |= (0b0111'0111);

        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 6:
        m_sectorTrailer[6] &= (mask7 | mask3);
        m_sectorTrailer[7] &= (mask7 | mask3);
        m_sectorTrailer[8] &= (mask7 | mask3);

        m_sectorTrailer[6] |= (0b0111'0000);
        m_sectorTrailer[7] |= (0b0111'0000);
        m_sectorTrailer[8] |= (0b0111'0000);

        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 7:
        m_sectorTrailer[6] &= (mask7 | mask3);
        m_sectorTrailer[7] &= (mask7 | mask3);
        m_sectorTrailer[8] &= (mask7 | mask3);

        m_sectorTrailer[6] |= (0b0000'0000);
        m_sectorTrailer[7] |= (0b0111'0000);
        m_sectorTrailer[8] |= (0b0111'0111);

        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    }
}

void MainWindow::on_accessConditionDBChange_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    QString blockString = (ui->blockSelect->text());
    int indexOfSectorTrailer = blockString.toInt();


    if((indexOfSectorTrailer+1)%4 != 0)
    {
        while((indexOfSectorTrailer+1)%4 != 0)
        {
        indexOfSectorTrailer++;
        }
    }
    qDebug() << indexOfSectorTrailer;
    connect->setBlockNum(QString::number(indexOfSectorTrailer));
    apdu.setWriteCommand(connect->getBlockNum(),m_sectorTrailer);

    BYTE *response;
    LONG lRet = connect->writeDataBlock(apdu.getWriteCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
        ui->statusAC->setText("Could not change the access conditions!");
        ui->statusAC->setStyleSheet("QLabel#statusAC {font-weight:bold; color:red;}");
        return;
    }
    ui->statusAC->setText("Access conditions have changed successfully.");
    ui->statusAC->setStyleSheet("QLabel#statusAC {font-weight:bold; color:green;}");
}
void MainWindow::on_accessConditionSTChange_clicked()
{
    MainWindow::on_accessConditionDBChange_clicked();
}

void MainWindow::on_restoreVB_clicked()
{
    //read value from data block
    APDUCommand apdu{};
    SCardConnection* connect = SCardConnection::getInstance();
    QString blockString = (ui->blockSelect->text());

    connect->setBlockNum(blockString);
    apdu.setReadValueBlockCommand(connect->getBlockNum());


    LONG lRet = connect->readValueBlock(apdu.getReadCommand());
    BYTE *response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
           return;
        }



        int receivedData = connect->getValue();
        qDebug() << receivedData;
        QString valueStr = QString::number(receivedData);


    // write part of the transfer operation

    QString destinationBlockString = ui->destinationBlockSelect->text();
    if((destinationBlockString.toInt()+1)%4 == 0 )
    {
        ui->statusVB->setText("Cannot restore to sector trailer!");
        ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
        ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");
        return;
    }
    QString valueHexStr;
    valueHexStr.setNum(valueStr.toInt(),16);
    if(valueHexStr.length() %2)   valueHexStr.insert(0,QLatin1String("0"));
    valueHexStr = valueHexStr.toUpper();
    QByteArray blockHexByteArray = QByteArray::fromHex(valueHexStr.toLatin1());
    BYTE valueNum[4]{0x00, 0x00, 0x00, 0x00};
    std::reverse(blockHexByteArray.begin(),blockHexByteArray.end());
    qDebug() << blockHexByteArray;
    qDebug() << blockHexByteArray.length();
    for( int i = 0; i<blockHexByteArray.length();i++)
    {
        valueNum[i] |= (BYTE)blockHexByteArray[i];
    }
    connect->setBlockNum(destinationBlockString);

    apdu.setValueBlockCommand(connect->getBlockNum(),valueNum);

    lRet = connect->writeDataBlock(apdu.getWriteCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
      ui->statusVB->setText("Could not restored to destination as value block!");
      ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
      ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");
      return;
    }
    ui->statusVB->setText("Succesfully restored tovalue block.");
    ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : green; }");
    ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");
}
void MainWindow::on_transferVB_clicked()
{
    //read value from data block
    APDUCommand apdu{};
    SCardConnection* connect = SCardConnection::getInstance();
    QString blockString = (ui->blockSelect->text());

    connect->setBlockNum(blockString);
    apdu.setReadValueBlockCommand(connect->getBlockNum());

    QString valueStr;
    LONG lRet = connect->readValueBlock(apdu.getReadCommand());
    BYTE *response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
        ui->statusVB->setText("Cannot transfer to sector trailer!");
        ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
        ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");
        return;
        }
    else
       {

        int receivedData = connect->getValue();
        qDebug() << receivedData;
         valueStr = QString::number(receivedData);
        //ui->textVB->setText(valueStr);
        }

    // write part of the transfer operation

    QString destinationBlockString = ui->destinationBlockSelect->text();
    if((destinationBlockString.toInt()+1)%4 == 0 )
    {
        ui->statusVB->setText("Cannot transfer to sector trailer!");
        ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
        ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");
        return;
    }
    QString valueHexStr;
    valueHexStr.setNum(valueStr.toInt(),16);
    if(valueHexStr.length() %2)   valueHexStr.insert(0,QLatin1String("0"));
    valueHexStr = valueHexStr.toUpper();
    QByteArray blockHexByteArray = QByteArray::fromHex(valueHexStr.toLatin1());
    BYTE valueNum[4]{0x00, 0x00, 0x00, 0x00};
    std::reverse(blockHexByteArray.begin(),blockHexByteArray.end());
    qDebug() << blockHexByteArray;
    qDebug() << blockHexByteArray.length();
//    qDebug() <<
    for( int i = 0; i<blockHexByteArray.length();i++)
    {
        valueNum[i] |= (BYTE)blockHexByteArray[i];

    }

    connect->setBlockNum(destinationBlockString);

    apdu.setValueBlockCommand(connect->getBlockNum(),valueNum);

    lRet = connect->writeDataBlock(apdu.getWriteCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
         ui->statusVB->setText("Could not transfer to destination as value block!");
         ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
         ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");
         return;
        }
    BYTE emptyBLock[BLOCK_SIZE];
    for( int i = 0; i<static_cast<int>(BLOCK_SIZE);i++)
        {
           emptyBLock[i] = (BYTE)0x00;

        }
    connect->setBlockNum(blockString);
    apdu.setWriteCommand(connect->getBlockNum(),emptyBLock);
    lRet = connect->writeDataBlock(apdu.getWriteCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
        ui->statusVB->setText("Could not transfer to destination as value block!");
        ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
        ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");
      return;
    }

    ui->statusVB->setText("Succesfully transfer tovalue block.");
    ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : green; }");
    ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");

}

