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
     m_keyA = "FFFFFFFFFFFF"
    ,m_keyB = "FFFFFFFFFFFF";
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
    LONG lRet;

    lRet = connect->establishContext();
    if( lRet != SCARD_S_SUCCESS )
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
    {
        connect->setReaderLists();
        readerList = connect->getReaderLists();
        QString readerListStr = (QString::fromWCharArray(readerList));
        qDebug() << readerList;

        if( readerListStr != NULL )
        {
            ui->connectedReaderName->setText(readerListStr);
            ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : green; }");
            ui->UIDframe->setEnabled(true);
            ui->disconnectReader->setEnabled((true));
            ui->connectReader->setEnabled(false);
        }
        else
        {
            ui->connectedReaderName->setText("Connection Failed");
            ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : red; }");
            ui->UID->clear();
            ui->statusUID->clear();
            ui->UIDframe->setEnabled(false);
            ui->tabs->setEnabled(false);
        }
    }
}
void MainWindow::on_disconnectReader_clicked()
{
    SCardConnection* connect =SCardConnection::getInstance();
    connect->disconnectReader();
    //ui->connectReader->setEnabled(true);
    ui->connectedReaderName->clear();
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
    ui->disconnectUID->setEnabled(choice::set);
    ui->RAW->setEnabled(choice::set);
    ui->Utility->setEnabled(choice::clear);
    ui->Commands->setEnabled(choice::clear);

    }
    else
    {
    ui->UID->clear();
    ui->statusUID->setText("Failed!");
    ui->statusUID->setStyleSheet("QLabel#statusUID {font-weight: bold; color : red; }");
    ui->disconnectUID->setEnabled(choice::clear);
    }
}
void MainWindow::on_disconnectUID_clicked()
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
    ui->disconnectUID->setEnabled(choice::clear);
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
    MainWindow::setKeyA();
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
    MainWindow::setKeyA();
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

    apdu.setAuthCommand(connect->getBlockNum(), KEYA_SELECT);
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
            ui->Commands->setEnabled(choice::set);
            ui->Utility->setEnabled(choice::set);
            ui->ACframe->setEnabled(choice::set);
            ui->VBframe->setEnabled(choice::set);
        }
}
void MainWindow::on_authWithKeyB_clicked()
{

        SCardConnection* connect = SCardConnection::getInstance();
        APDUCommand apdu{};
        QString blockString =(ui->blockSelect->text());
        connect->setBlockNum(blockString);

        apdu.setAuthCommand(connect->getBlockNum(), KEYB_SELECT);

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
    int indexOfSectorTrailer = blockString.toInt();
    if((indexOfSectorTrailer+1)%4 == 0)
    {



    }
    if((indexOfSectorTrailer+1)%4 != 0)
    {
        while((indexOfSectorTrailer+1)%4 != 0)
        {
        indexOfSectorTrailer++;
        }
        connect->setBlockNum(QString::number(indexOfSectorTrailer));
        apdu.setReadCommand(connect->getBlockNum());

        QString sectorTrailer;
        sectorTrailer = (connect->readDataBlock(apdu.getReadCommand()));
        QByteArray byteList = QByteArray::fromHex(sectorTrailer.toLatin1());
        BYTE B8 = byteList.at(8);
        BYTE B7 = byteList.at(7);

        if(  !(B7 & mask6) &&  !(B8 & mask2) &&  !(B8 & mask6)  ) ui->accessCondition->setText("read A/B - write A/B - increment A/B - decrement,transfer,restore A/B [transport config]");
        //   0  0  0
        if(  !(B7 & mask6) &&  !(B8 & mask2) &&   (B8 & mask6) ) ui->accessCondition->setText("read A/B - write B - increment B - decrement,transfer,restore A/B [value block]");
        //   0  0  1
        if(  !(B7 & mask6) &&   (B8 & mask2) &&  !(B8 & mask6) ) ui->accessCondition->setText("read A/B - write (never)- increment (never) - decrement,transfer,restore (never) [r/w]");
        //   0  1  0
        if(  !(B7 & mask6) &&   (B8 & mask2) &&   (B8 & mask6) ) ui->accessCondition->setText("read A/B - write (never)- increment (never) - decrement,transfer,restore A/B [r/w]");
        //   0  1  1
        if(   (B7 & mask6) &&  !(B8 & mask2) &&  !(B8 & mask6) ) ui->accessCondition->setText("read A/B - write B - increment (never) - decrement,transfer,restore (never) [r/w]");
        //   1  0  0
        if(   (B7 & mask6) &&  !(B8 & mask2) &&   (B8 & mask6) ) ui->accessCondition->setText("read A/B - write (never)- increment (never) - decrement,transfer,restore (never) [r/w]");
        //   1  0  1
        if(   (B7 & mask6) &&   (B8 & mask2) &&  !(B8 & mask6) ) ui->accessCondition->setText("read A/B - write (never)- increment (never) - decrement,transfer,restore (never) [value block]");
        //   1  1  0
        if(   (B7 & mask6) &&   (B8 & mask2) &&   (B8 & mask6) ) ui->accessCondition->setText("read (never) - write (never)- increment (never) - decrement,transfer,restore (never) [r/w]");
        //   1  1  1

        ui->accessCondition->setEnabled(true);
        ui->accessConditionChange->setEnabled(true);
        ui->accessConditionComboBox->setEnabled(true);
        ui->accessCondition->setStyleSheet("QLineEdit#accessCondition {font-weight:bold; color:red;}");
        ui->accessCondition_2->clear(); ui->accessCondition_2->setEnabled(false);
        ui->accessConditionChange_2->setEnabled(false);
        ui->accessConditionComboBox_2->setEnabled(false);


    }
    else
    {
        connect->setBlockNum(QString::number(indexOfSectorTrailer));
        apdu.setReadCommand(connect->getBlockNum());

        QString sectorTrailer;
        sectorTrailer = (connect->readDataBlock(apdu.getReadCommand()));
        QByteArray byteList = QByteArray::fromHex(sectorTrailer.toLatin1());
        qDebug() << byteList.at(7) << " " << byteList.at(8);
        BYTE B8 = byteList.at(8);
        BYTE B7 = byteList.at(7);
        //qDebug() << B7 << " " << B8;
        if(  !(B7 & mask7) &&  !(B8 & mask3) && !(B8 & mask7) ) ui->accessCondition_2->setText("KeyA[read(never),write(A)], access-bits[read(A),write(never)], KeyB[read(A),write(A)]");
        //   0  0  0
        if(  !(B7 & mask7) &&  !(B8 & mask3) &&  (B8 & mask7) ) ui->accessCondition_2->setText("KeyA[read(never),write(A)], access-bits[read(A),write(A)], KeyB[read(A),write(A)]");
        //   0  0  1
        if(  !(B7 & mask7) &&   (B8 & mask3) && !(B8 & mask7) ) ui->accessCondition_2->setText("KeyA[read(never),write(never)], access-bits[read(A),write(never)], KeyB[read(A),write(never)]");
        //   0  1  0
        if(  !(B7 & mask7) &&   (B8 & mask3) &&  (B8 & mask7) ) ui->accessCondition_2->setText("KeyA[read(never),write(B)], access-bits[read(A/B),write(B)], KeyB[read(never),write(B)]");
        //   0  1  1
        if(   (B7 & mask7) &&  !(B8 & mask3) && !(B8 & mask7) ) ui->accessCondition_2->setText("KeyA[read(never),write(B)], access-bits[read(A/B),write(never)], KeyB[read(never),write(B)]");
        //   1  0  0
        if(   (B7 & mask7) &&  !(B8 & mask3) &&  (B8 & mask7) ) ui->accessCondition_2->setText("KeyA[read(never),write(never)], access-bits[read(A/B),write(B)], KeyB[read(never),write(never)]");
        //   1  0  1
        if(   (B7 & mask7) &&   (B8 & mask3) && !(B8 & mask7) ) ui->accessCondition_2->setText("KeyA[read(never),write(never)], access-bits[read(A/B),write(never)], KeyB[read(never),write(never)]");
        //   1  1  0
        if(   (B7 & mask7) &&   (B8 & mask3) &&  (B8 & mask7) ) ui->accessCondition_2->setText("KeyA[read(never),write(never)], access-bits[read(A),write(never)], KeyB[read(never),write(never)]");
        //   1  1  1
        ui->accessCondition_2->setEnabled(true);
        ui->accessConditionChange_2->setEnabled(true);
        ui->accessConditionComboBox_2->setEnabled(true);
        ui->accessCondition->setStyleSheet("QLineEdit#accessCondition {font-weight:bold; color:red;}");
        ui->accessCondition->clear(); ui->accessCondition->setEnabled(false);
        ui->accessConditionChange->setEnabled(false);
        ui->accessConditionComboBox->setEnabled(false);

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
    ui->statusRAW->setText("Processing...");
    ui->statusRAW->setStyleSheet("QLabel#statusRAW {font-weight: bold; color : green; }");
    QAbstractButton *keyButton = ui->rawKeySelectGroup->checkedButton();
    QAbstractButton *formatButton = ui->rawFormatSelectGroup->checkedButton();
    QString _keyA = MainWindow::getKeyA();
    QByteArray _keyBytes = QByteArray::fromHex(_keyA.toLatin1());

    Sleep(100);
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
    connect->loadKey(apdu.getLoadKeyCommand());

    for(int i = 0; i<64; i++)
        {
        QString blockStr = QString::number(i);
        connect->setBlockNum(blockStr);
        if(i%4 == 0)
            {
                sectorNum++;
                sectorStr = QString::number(i/4);
                apdu.setAuthCommand(connect->getBlockNum(), keySelect);
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
    return dataList;
}
void MainWindow::printRawTable(const QVector<QStringList> &dataList, const bool formatSelect)
{
    QStringList rawHeaders = {"Sector","Block","B0","B1","B2","B3","B4","B5"
                             ,"B6","B7","B8","B9","B10","B11","B12","B13","B14","B15" };
    ui->rawDataTable->clear();
//    QString textValue = QString::fromLocal8Bit(QByteArray::fromHex((dataList.at(1).join)));
    if(!formatSelect)
    {
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
                     //ui->rawDataTable->back
                 }
                 else
                 {
                     //qDebug() << dataList.at(row-1);
                     if(column == 0 || column == 1)
                     {
                         ui->rawDataTable->item(row,column);
                         ui->rawDataTable->setItem(row,column,new QTableWidgetItem((dataList[row-1]).at(column)));
                     }
                     else
                     {
                         //if(dataList == "")
                         QString dataStr = (dataList[row-1][column]);
                         QString asciiValue = QString::fromLocal8Bit(QByteArray::fromHex(dataStr.toLatin1()));
                         //qDebug() << asciiValue;
                         ui->rawDataTable->item(row,column);
                         ui->rawDataTable->setItem(row,column,new QTableWidgetItem(asciiValue));
                     }
                 }
            }
        }
    }
    else
    {
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
    connect->writeDataBlock(apdu.getWriteCommand());
}
void MainWindow::on_readVB_clicked()
{//mathematical operations should be added
    APDUCommand apdu{};
    SCardConnection* connect = SCardConnection::getInstance();
    QString blockString = (ui->blockSelect->text());
    connect->setBlockNum(blockString);
    apdu.setReadValueBlockCommand(connect->getBlockNum());
    QString recievedData = connect->readDataBlock(apdu.getReadCommand());
//    int value = 0;
//    for(int i=0;i<4;i++)
//        value = value + (recievedData.number(i)).toInt();
    ui->textVB->setText(/*QString(value)*/recievedData);


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
    connect->loadKey(apdu.getLoadKeyCommand());

    for(int i = (ui->sectorBegin->value()); i<=(ui->sectorEnd->value()); i++)
        {
                QString blockStr = QString::number((i*4)+3);
                connect->setBlockNum(blockStr);
                BYTE block = connect->getBlockNum();
                apdu.setAuthCommand(block, keySelect);
                connect->authenticate(apdu.getAuthCommand());
                apdu.setReadCommand(block);
                QString sectorTrailer = connect->readDataBlock(apdu.getReadCommand());
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

