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
    SCardConnection* connect =SCardConnection::getInstance();
    LPTSTR readerList;

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
                ui->UIDframe->setEnabled(false);
                ui->tabs->setEnabled(false);
            }
        else
            {
            readerList = connect->getReaderLists();
            QString readerListStr = (QString::fromWCharArray(readerList));
            qDebug() << readerListStr;

            if( readerListStr != NULL )
                {
                    ui->connectedReaderName->setText(readerListStr);
                    ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : green; }");
                    ui->UIDframe->setEnabled(true);
                    ui->disconnectReader->setEnabled((true));
                    ui->connectReader->setEnabled(false);
                    ui->Commands->setEnabled(choice::set);
                    ui->commandTextWindow->setEnabled(true);
                    ui->commandTextWindow->append("ReaderConnect()");
                }

            }
    }
}
void MainWindow::on_disconnectReader_clicked()
{
    SCardConnection* connect =SCardConnection::getInstance();
    connect->disconnectReader();
    ui->connectedReaderName->clear();
    ui->commandTextWindow->append("ReaderDisconnectConnect()");
    ui->disconnectReader->setEnabled(false);
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
    ui->SBframe->setEnabled(choice::set);
    ui->keyAframe->setEnabled(choice::set);
    ui->keyBframe->setEnabled(choice::set);
    ui->tabs->setEnabled(choice::set);
    ui->Operations->setEnabled(choice::set);
    ui->disconnectUID->setEnabled(choice::set);
    ui->RAW->setEnabled(choice::set);
    ui->Utility->setEnabled(choice::clear);
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
    ui->keyAframe->setEnabled(choice::clear);
    ui->keyBframe->setEnabled(choice::clear);
    ui->RWframe->setEnabled(choice::clear);
    ui->SBframe->setEnabled(choice::clear);
    ui->tabs->setEnabled(choice::clear);
    ui->disconnectUID->setEnabled(choice::clear);
    ui->statusA->clear();
    ui->statusB->clear();
    ui->statusRW->clear();
    ui->commandTextWindow->append("UIDDisconnect()");
    ui->tabs->setCurrentIndex(0);
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
        }
    else
        {
            ui->statusA->setText("Key loaded.");
            ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : green; }");
            ui->commandTextWindow->append("KeyALoadToNonVolatileMemory()");
        }
}
void MainWindow::on_loadTo0B_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};
    MainWindow::setKeyA();
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
    BYTE *response = connect->getResponse();
    LONG lRet = connect->loadKey(apdu.getLoadKeyCommand());
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
            ui->statusB->setText("Failed to load key!");
            ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : red; }");

        }
    else
        {
            ui->statusB->setText("Key loaded.");
            ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : green; }");
            ui->commandTextWindow->append("KeyBLoadToNonVolatileMemory()");
        }

}
void MainWindow::on_loadTo1B_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};
    MainWindow::setKeyA();
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

        }
    else
        {
            ui->statusB->setText("Key loaded.");
            ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : green; }");
            ui->commandTextWindow->append("KeyBLoadToNonVolatileMemory()");
        }
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
       qDebug() << "asdf" <<*(response) << SUCCESS_RESPONSE[0];
     }
    else
    {
        ui->statusA->setText("Authenticated.");
        ui->statusA->setStyleSheet("QLabel#statusA {font-weight: bold; color : green; }");
        ui->RWframe->setEnabled(choice::set);
        ui->Utility->setEnabled(choice::set);
        ui->VBframe->setEnabled(choice::set);
        ui->ACframe->setEnabled(choice::set);
        ui->utilityBlock->setText(blockString);
        ui->commandTextWindow->append("AuthenticateWithKeyA()");
        qDebug() << "bcdgef"<<*(response) << SUCCESS_RESPONSE[0];
    }

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

            }
        else
        {
            ui->statusB->setText("Authenticated.");
            ui->statusB->setStyleSheet("QLabel#statusB {font-weight: bold; color : green; }");
            ui->RWframe->setEnabled(choice::set);
            ui->Utility->setEnabled(choice::set);
            ui->VBframe->setEnabled(choice::set);
            ui->ACframe->setEnabled(choice::set);
            ui->utilityBlock->setText(blockString);
            ui->commandTextWindow->append("AuthenticateWithKeyB()");
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
            ui->ACframe->setEnabled(true);
            ui->commandTextWindow->append("ReadBlock()");

}
void MainWindow::on_writeBlock_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    QString blockString = (ui->blockSelect->text());
    connect->setBlockNum(blockString);
    if((connect->getBlockNum()+1)%4 == 0 )
        {
            ui->statusRW->setText("Cannot read to sector trailer!");
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


    ui->statusRAW->setText("Done.");
    ui->statusRAW->setStyleSheet("QLabel#statusRAW {font-weight: bold; color : green; }");
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
    QVector<QStringList> dataList{};
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
        return dataList;


            QProgressDialog progress;
            progress.setMinimum(0);
            progress.setMaximum(64);
            progress.setLabelText("         Reading data...         ");
            progress.setCancelButton(0);
            progress.resize(250,60);
            progress.setWindowFlags( Qt::CustomizeWindowHint );
            progress.setWindowModality(Qt::ApplicationModal);
            progress.setFixedSize(progress.geometry().width(),progress.geometry().height());


//            QList<QPushButton *> L=progress.findChildren<QPushButton *>();
//            L.at(0)->hide();
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

                    for(int j = 4 ; j>0 ; j-- )
                    {
                        for(DWORD k = 0 ; k<BLOCK_SIZE ; k++ )recievedData.push_front(" \0 ");
                        i++;
                    }
                }

            }
            apdu.setReadCommand(connect->getBlockNum());
            recievedData = "";
            lRet = connect->readDataBlock(apdu.getReadCommand());
            response = connect->getResponse();
            if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
                {
                    for(DWORD k = 0 ; k<BLOCK_SIZE-1 ; k++ )
                        recievedData.append(" \0 ");
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
    QStringList columnHeaders = {"Sector","Block","B0","B1","B2","B3","B4","B5"
                             ,"B6","B7","B8","B9","B10","B11","B12","B13","B14","B15" };
    QFont font; font.setBold(true);

    ui->rawDataTable->clear();
//    ui->rawDataTable->insertRow( 0 );
//    for(DWORD column = 0; column<BLOCK_SIZE+(DWORD)2; column++)
//    ui->rawDataTable->insertColumn(column);
//    ui->rawDataTable->setVerticalHeaderLabels(columnHeaders);
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
                         ui->rawDataTable->item(row,column);
                         ui->rawDataTable->setItem(row,column,new QTableWidgetItem((dataList[row-1]).at(column)));
                         if((row)%4 ==0) ui->rawDataTable->item(row,column)->QTableWidgetItem::setBackground(QColor(QRgb(0xF7F4F2)));
                        }

                 }
            }
        }
    }
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

void MainWindow::on_valueBlockWrite_clicked()
{
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    QString _valueBlock;
    _valueBlock.append ( (ui->valueBlockInit->toPlainText()).toUtf8() );
    QString valueHexStr;
    valueHexStr.setNum(_valueBlock.toInt(),16);
    if(valueHexStr.length() %2)   valueHexStr.insert(0,QLatin1String("0"));
    valueHexStr = valueHexStr.toUpper();
    QByteArray blockHexByteArray = QByteArray::fromHex(valueHexStr.toLatin1());
    BYTE valueNum[4];
    for(int i=0; i<4; i++)
    valueNum[i] = blockHexByteArray[i];

    QString blockString = (ui->blockSelect->text());
    connect->setBlockNum(blockString);
    apdu.setValueBlockCommand(connect->getBlockNum(),valueNum);
    BYTE *response;
    LONG lRet = connect->writeDataBlock(apdu.getWriteCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
      ui->statusVB->setText("Failed to format as value block!");
      ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
      ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");
      return;
    }
    ui->statusVB->setText("Succesfully formated as value block.");
    ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : green; }");
    ui->commandTextWindow->append("FormatAsValueBlockWithInıtial()");

}
void MainWindow::on_readVB_clicked()
{//mathematical operations should be added
    APDUCommand apdu{};
    SCardConnection* connect = SCardConnection::getInstance();
    QString blockString = (ui->blockSelect->text());
    connect->setBlockNum(blockString);
    apdu.setReadValueBlockCommand(connect->getBlockNum());
    QString receivedData;
    BYTE *response;
    LONG lRet = connect->readDataBlock(apdu.getReadCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
        receivedData = "Fail!";

    }
    else receivedData = connect->getReadDataBlockString();
//    int value = 0;
//    for(int i=0;i<4;i++)
//        value = value + (recievedData.number(i)).toInt();
    ui->textVB->setText(/*QString(value)*/receivedData);


}
void MainWindow::on_decVB_clicked()
{
    APDUCommand apdu{};
    SCardConnection* connect = SCardConnection::getInstance();
    QString blockString = (ui->blockSelect->text());
    connect->setBlockNum(blockString);
    apdu.setIncDecCommand(DECREMENT_SELECT, connect->getBlockNum());
    connect->loadKey(apdu.getIncrDecrCommand());
}
void MainWindow::on_incVB_clicked()
{
    APDUCommand apdu{};
    SCardConnection* connect = SCardConnection::getInstance();
    QString blockString = (ui->blockSelect->text());
    connect->setBlockNum(blockString);
    apdu.setIncDecCommand(INCREMENT_SELECT, connect->getBlockNum());
    connect->loadKey(apdu.getIncrDecrCommand());
}

void MainWindow::on_utilityKCText_clicked()
{
    TextWindow* txtwnd = TextWindow::getInstance();
    txtwnd->show();
    txtwnd->setTextAreaSelect(3);
    txtwnd->setInputMaxSize(KEY_SIZE);
}
void MainWindow::on_utilityKCFactory_clicked()
{
    ui->utilityKC0->setText("FF");
    ui->utilityKC1->setText("FF");
    ui->utilityKC2->setText("FF");
    ui->utilityKC3->setText("FF");
    ui->utilityKC4->setText("FF");
    ui->utilityKC5->setText("FF");
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
        keySelect = KEYA_SELECT;
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            key[i] = _keyBytes[i];
        }
        scrdops.setKeyA(key);
        apdu.setLoadKeyCommand(scrdops.getKeyA() , V_MEMORY);
    }
    if(usingKey == (ui->utilityUsingKeyB))
    {
        MainWindow::setKeyB();
        QString _key = MainWindow::getKeyB();
        QByteArray _keyBytes = QByteArray::fromHex(_key.toLatin1());
        keySelect = KEYB_SELECT;
        for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
        {
            key[i] = _keyBytes[i];
        }
        scrdops.setKeyB(key);
        apdu.setLoadKeyCommand(scrdops.getKeyB() , V_MEMORY);
    }
    LONG lRet = connect->loadKey(apdu.getLoadKeyCommand());
    BYTE* response;
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
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
                    return;
                }

                apdu.setReadCommand(block);
                lRet = connect->readDataBlock(apdu.getReadCommand());
                response = connect->getResponse();
               if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
                {
                    return;
                }
                QString sectorTrailer = connect->getReadDataBlockString();
                qDebug() << "before change: " <<sectorTrailer;

                MainWindow::setUtilityKey();
                MainWindow::getUtilityKey();
                QString _key = MainWindow::getUtilityKey();
//                QByteArray _keyBytes = QByteArray::fromHex(_key.toLatin1());

//                for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
//                {
//                    key[i] = _keyBytes[i];
//                }
                if(changeKey == ui->utilityChangeKeyA)
                    {
                        for(int i = 0; i<KEY_SIZE; i++)
                        {
                           sectorTrailer[i] = _key[i];
                        }
                    }
                if(changeKey == ui->utilityChangeKeyB)
                    {
                        for(int i = 0; i<KEY_SIZE; i++)
                        {
                           sectorTrailer[KEY_SIZE - i] = _key[KEY_SIZE - i];
                        }
                    }
                qDebug() <<"after change: " <<sectorTrailer;
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
            ui->accessCondition->setText("Could not read!");
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

        ui->accessCondition->setEnabled(true);
        ui->accessConditionDBChange->setEnabled(true);
        ui->accessConditionDB->setEnabled(true);
        ui->accessCondition->setStyleSheet("QLineEdit#accessCondition {font-weight:bold; color:red;}");
        ui->accessConditionSTRead->clear(); ui->accessConditionSTRead->setEnabled(false);
        ui->accessConditionSTChange->setEnabled(false);
        ui->accessConditionST->setEnabled(false);


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
            ui->accessCondition->setText("Could not read!");
            return;
        }
        sectorTrailer = connect->getReadDataBlockString();
        QByteArray byteList = QByteArray::fromHex(sectorTrailer.toLatin1());
        qDebug() << byteList.at(7) << " " << byteList.at(8);
        BYTE B8 = byteList.at(8);
        BYTE B7 = byteList.at(7);
        //qDebug() << B7 << " " << B8;
        if(  !(B7 & mask7) &&  !(B8 & mask3) && !(B8 & mask7) ) ui->accessConditionSTRead->setText("KeyA[read(never),write(A)], access-bits[read(A),write(never)], KeyB[read(A),write(A)]");
        //   0  0  0
        if(  !(B7 & mask7) &&  !(B8 & mask3) &&  (B8 & mask7) ) ui->accessConditionSTRead->setText("KeyA[read(never),write(A)], access-bits[read(A),write(A)], KeyB[read(A),write(A)]");
        //   0  0  1
        if(  !(B7 & mask7) &&   (B8 & mask3) && !(B8 & mask7) ) ui->accessConditionSTRead->setText("KeyA[read(never),write(never)], access-bits[read(A),write(never)], KeyB[read(A),write(never)]");
        //   0  1  0
        if(  !(B7 & mask7) &&   (B8 & mask3) &&  (B8 & mask7) ) ui->accessConditionSTRead->setText("KeyA[read(never),write(B)], access-bits[read(A/B),write(B)], KeyB[read(never),write(B)]");
        //   0  1  1
        if(   (B7 & mask7) &&  !(B8 & mask3) && !(B8 & mask7) ) ui->accessConditionSTRead->setText("KeyA[read(never),write(B)], access-bits[read(A/B),write(never)], KeyB[read(never),write(B)]");
        //   1  0  0
        if(   (B7 & mask7) &&  !(B8 & mask3) &&  (B8 & mask7) ) ui->accessConditionSTRead->setText("KeyA[read(never),write(never)], access-bits[read(A/B),write(B)], KeyB[read(never),write(never)]");
        //   1  0  1
        if(   (B7 & mask7) &&   (B8 & mask3) && !(B8 & mask7) ) ui->accessConditionSTRead->setText("KeyA[read(never),write(never)], access-bits[read(A/B),write(never)], KeyB[read(never),write(never)]");
        //   1  1  0
        if(   (B7 & mask7) &&   (B8 & mask3) &&  (B8 & mask7) ) ui->accessConditionSTRead->setText("KeyA[read(never),write(never)], access-bits[read(A),write(never)], KeyB[read(never),write(never)]");
        //   1  1  1
        ui->accessConditionSTRead->setEnabled(true);
        ui->accessConditionSTChange->setEnabled(true);
        ui->accessConditionST->setEnabled(true);
        ui->accessConditionSTRead->setStyleSheet("QLineEdit#accessConditionSTRead {font-weight:bold; color:red;}");
        ui->accessCondition->clear(); ui->accessCondition->setEnabled(false);
        ui->accessConditionDBChange->setEnabled(false);
        ui->accessConditionDB->setEnabled(false);

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
        m_sectorTrailer[8] |= (0b1000'0000);
        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 2:
        m_sectorTrailer[6] &= ~(mask7 | mask3);
        m_sectorTrailer[7] &= ~(mask7 | mask3);
        m_sectorTrailer[8] &= ~(mask7 | mask3);

        m_sectorTrailer[6] |= (0b0000'1000);
        m_sectorTrailer[7] |= (0b0000'1000);
        m_sectorTrailer[8] |= (0b1000'1000);
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

        m_sectorTrailer[6] |= (0b1111'0111);
        m_sectorTrailer[7] |= (0b1000'0111);
        m_sectorTrailer[8] |= (0b1000'0000);
        qDebug() <<  index  << " " << m_sectorTrailer[6] << " " << m_sectorTrailer[7] << " " << m_sectorTrailer[8];
        break;
    case 7:
        m_sectorTrailer[6] &= ~(mask7 | mask3);
        m_sectorTrailer[7] &= ~(mask7 | mask3);
        m_sectorTrailer[8] &= ~(mask7 | mask3);

        m_sectorTrailer[6] |= (0b0111'0111);
        m_sectorTrailer[7] |= (0b1000'0111);
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
      //m_sectorTrailer[6] = {0b1111'1111},
      //m_sectorTrailer[7] = {0b0000'0111},
      //m_sectorTrailer[8] = {0b1000'0000};

        m_sectorTrailer[6] &= (mask7 | mask3);
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

        m_sectorTrailer[6] |= (0b0000'0000);
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
    apdu.setWriteCommand(indexOfSectorTrailer,m_sectorTrailer);

    BYTE *response;
    LONG lRet = connect->writeDataBlock(apdu.getReadCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
        ui->statusAC->setText("Could not change the access conditions!");
        return;
    }
}


void MainWindow::on_accessConditionSTChange_clicked()
{
    MainWindow::on_accessConditionDBChange_clicked();
}

