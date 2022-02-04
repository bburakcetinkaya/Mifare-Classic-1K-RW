#include "Headers\mainwindow.h"
#include "Headers\connect.h"
#include "ui_mainwindow.h"
#include "Headers\commands.h"
#include "Headers/scardoperations.h"
#include "Headers/apducommand.h"
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
struct RWblocks
{
    QTextEdit *edit;
    QLabel *label;
    QWidget *widget;
};

QVector<RWblocks> RWVector;

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
    }
    else
    {
        connect->setReaderLists(choice::set);
        readerList = connect->getReaderLists();
        QString readerListS = (QString::fromWCharArray(readerList));
//        oldReaderList = readerList;
//        if(oldReaderList == readerList)  return; // reference object referrence return
        if( readerList != NULL )
        {

            ui->connectedReaderName->setText(readerListS);
            ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : green; }");
        }
        else
        {
            ui->connectedReaderName->setText("Connection Failed");
            ui->connectedReaderName->setStyleSheet("QLabel#connectedReaderName {font-weight: bold; color : red; }");
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
    ui->UID->setStyleSheet("QLineEdit#UID {color : black; }");
    }
    else
    {
    ui->UID->setText("Failed!");
    ui->UID->setStyleSheet("QLineEdit#UID {font-weight: bold; color : red; }");
    }
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
    BYTE keyA[KEY_SIZE];
    QByteArray _keyABytes = QByteArray::fromHex(_keyA.toLatin1());
    for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
    {
        keyA[i] = _keyABytes[i];
    }
    SCardConnection* connect = SCardConnection::getInstance();
    SCardOperations scrdops{};
    APDUCommand apdu{};

    scrdops.setKeyA(_keyA);
    BYTE storageAddress = 0x00;
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


void MainWindow::on_authWithKeyA_clicked()
{
    QString _keyA;
    _keyA.append ( (ui->keyA5->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA4->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA3->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA2->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA1->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA0->toPlainText()).toUtf8() );
    BYTE keyA[KEY_SIZE];
    QByteArray _keyABytes = QByteArray::fromHex(_keyA.toLatin1());
    for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
    {
        keyA[i] = _keyABytes[i];
    }
    SCardConnection* connect = SCardConnection::getInstance();
    APDUCommand apdu{};
    QString blockString =(ui->blockSelect->text());
    connect->setBlockNum(blockString);

//const BYTE block, const BYTE keySelect, const BYTE storageAddress
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

