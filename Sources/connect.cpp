#include "Headers\connect.h"
#include "Headers\commands.h"
#include <winscard.h>
#include <cstdio>
#include <QByteArray>
#include <QString>
#include <QList>
#include <QDebug>

SCardConnection* SCardConnection::instance = NULL;
SCardConnection* SCardConnection::getInstance()
{
   if (instance == NULL) {
       instance = new SCardConnection();
   }
   return(instance);
}
SCardConnection* SCardConnection::getInstanceNew()
{
    if(instance != NULL){
       delete instance;
    }
    instance = new SCardConnection();
    return instance;
}
SCardConnection::SCardConnection()
{
    m_readerList = {}
   ,m_hContext = 0
   ,m_pmszReaders = NULL
   ,m_lRet = 0
   ,m_dwAP = 0
   ,m_cch = SCARD_AUTOALLOCATE
   ,m_hCard = 0
   ,m_cbSend = 0
   ,m_cbRecv = MAX_APDU_SIZE
   ,m_blockNum = 0x00
;
}
LONG SCardConnection::establishContext()
{
   m_lRet = SCardEstablishContext(SCARD_SCOPE_USER, 0, 0, &m_hContext);
   return m_lRet;
}
void SCardConnection::disconnectReader()
{   
    m_pmszReaders = NULL;
    SCardFreeMemory( m_hContext, m_pmszReaders );
    SCardReleaseContext(m_hContext);
}
LONG SCardConnection::setReaderLists()
{
    m_lRet = SCardListReaders(m_hContext, NULL, (LPTSTR)&m_pmszReaders, &m_cch);

    return m_lRet;
}
LPTSTR SCardConnection::getReaderLists()
{
    return m_pmszReaders;
}
LONG SCardConnection::connectCard()
{
   m_lRet = SCardConnect(m_hContext, m_pmszReaders,SCARD_SHARE_SHARED, SCARD_PROTOCOL_Tx, &m_hCard, &m_dwAP);
   return m_lRet;
}
LONG SCardConnection::disconnectCard()
{
    m_lRet = SCardDisconnect(m_hCard,SCARD_LEAVE_CARD);
    return m_lRet;

}
LONG SCardConnection::setCardUID()
{
    memcpy(m_pbSend, readUIDCommand, sizeof(readUIDCommand));
    m_cbSend = sizeof(readUIDCommand);
    m_cbRecv = MAX_APDU_SIZE;

    if((m_lRet = SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv,&m_cbRecv)) != SCARD_S_SUCCESS)
    return m_lRet;

    if(m_cbRecv == RESPONSE_SIZE)
        SCardConnection::setResponse(m_pbRecv);
    else
        SCardConnection::setResponse(m_pbRecv+UID_SIZE);

         for (DWORD i = 0; i < m_cbRecv-RESPONSE_SIZE; i++)
             {
                    m_cardUID[i] = m_pbRecv[i];
             }
    return m_lRet;

}
QString SCardConnection::getCardUID()
{
    QByteArray UID =  QByteArray(reinterpret_cast<char*>(m_cardUID), sizeof(m_cardUID)).toHex(' ').toUpper();
    QString UIDstring = QString(UID).toUpper();

    return UIDstring;
}
LONG SCardConnection::loadKey(BYTE *loadCommand)// will have a byte ptr return type to handle response
{
    BYTE command[LOADCOMMAND_SIZE] = {};
    for(int i = 0; i<static_cast<int>(LOADCOMMAND_SIZE); i++) command[i] = *(loadCommand+i);

    memcpy(m_pbSend, command, LOADCOMMAND_SIZE);
    m_cbSend = LOADCOMMAND_SIZE;
    m_cbRecv = MAX_APDU_SIZE;
    m_lRet = SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv);

    SCardConnection::setResponse(m_pbRecv);
    return m_lRet;
}
LONG SCardConnection::authenticate(BYTE *authCommand)
{
   BYTE command[AUTHCOMMAND_SIZE];
   for(int i = 0; i<static_cast<int>(AUTHCOMMAND_SIZE); i++)
       command[i] = *(authCommand+i);
   memcpy(m_pbSend, command, AUTHCOMMAND_SIZE); m_cbSend = AUTHCOMMAND_SIZE; m_cbRecv = MAX_APDU_SIZE;
   m_lRet = SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv);

   SCardConnection::setResponse(m_pbRecv);
   return m_lRet;
}
LONG SCardConnection::readDataBlock(BYTE *readCommand)
{
    BYTE command[READCOMMAND_SIZE] = {};
    for(int i = 0; i<static_cast<int>(READCOMMAND_SIZE); i++) command[i] = *(readCommand+i);

    for(int i = 0; i<static_cast<int>(MAX_APDU_SIZE); i++) m_pbRecv[i] = 0x00; // clear recieve var

    memcpy(m_pbSend, command, READCOMMAND_SIZE); m_cbSend = READCOMMAND_SIZE; m_cbRecv = MAX_APDU_SIZE;
    m_lRet = SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv);

    if(m_cbRecv == RESPONSE_SIZE)
        SCardConnection::setResponse(m_pbRecv);
    else
    {
        SCardConnection::setResponse(m_pbRecv+BLOCK_SIZE);

        m_blockAsByte =  QByteArray(reinterpret_cast<char*>(m_pbRecv), BLOCK_SIZE).toHex(' ').toUpper();
        m_blockDataString = QString(m_blockAsByte).toUpper();
    }
    return m_lRet;
}
QByteArray SCardConnection::getBlockAsByte()
{
    return m_blockAsByte;
}
LONG SCardConnection::readValueBlock(BYTE* readValueBlockCommand)
{
    BYTE command[READCOMMAND_SIZE] = {};
    for(int i = 0; i<static_cast<int>(READCOMMAND_SIZE); i++) command[i] = *(readValueBlockCommand+i);

    for(int i = 0; i<static_cast<int>(MAX_APDU_SIZE); i++) m_pbRecv[i] = 0x00; // clear recieve var

    memcpy(m_pbSend, command, READCOMMAND_SIZE); m_cbSend = READCOMMAND_SIZE; m_cbRecv = MAX_APDU_SIZE;
    m_lRet = SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv);

    if(m_cbRecv == RESPONSE_SIZE)
        SCardConnection::setResponse(m_pbRecv);
    else
    {
        SCardConnection::setResponse(m_pbRecv+4);

       BYTE byteValue[4];
//       m_value;
       for(DWORD i = 0; i<4 ; i++)
           byteValue[3-i] = m_pbRecv[i];

       QByteArray calcHelper;
       for(int i = 0; i<4; i++)
       {

       calcHelper.append(byteValue[i]);
       }
       qDebug() << "calcHelper: "<<calcHelper;
       QString calc = QString(calcHelper.toHex());
       qDebug() << "calc: "<<calc;
       bool ok;
       m_value = (calc.toLong(&ok,16));
       qDebug() << "m_value: "<<m_value;

    }
    return m_lRet;

}
LONG SCardConnection::incrDecrValueBlock(BYTE* incrDecrCommand)
{
    BYTE command[INCDECCOMMAND_SIZE] = {};
    for(int i = 0; i<static_cast<int>(INCDECCOMMAND_SIZE); i++) command[i] = *(incrDecrCommand+i);

    for(int i = 0; i<static_cast<int>(MAX_APDU_SIZE); i++) m_pbRecv[i] = 0x00; // clear recieve var

    memcpy(m_pbSend, command, INCDECCOMMAND_SIZE); m_cbSend = INCDECCOMMAND_SIZE; m_cbRecv = MAX_APDU_SIZE;
    m_lRet = SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv);


    SCardConnection::setResponse(m_pbRecv);

    return m_lRet;
}
QString SCardConnection::getReadDataBlockString()
{
    return m_blockDataString;
}
long int SCardConnection::getValue()
{
    return m_value;
}

void SCardConnection::setBlockNum(const QString &blockAsString)
{
    QString blockHexStr;
    blockHexStr.setNum(blockAsString.toInt(),16);
    if(blockHexStr.length() %2)   blockHexStr.insert(0,QLatin1String("0"));
    blockHexStr = blockHexStr.toUpper();
    QByteArray blockHexByteArray = QByteArray::fromHex(blockHexStr.toLatin1());
    m_blockNum = blockHexByteArray[0];
}
BYTE SCardConnection::getBlockNum()
{
    return m_blockNum;
}
LONG SCardConnection::writeDataBlock(BYTE *writeCommand)
{
    BYTE command[WRITECOMMAND_SIZE] = {};
    for(int i = 0; i<static_cast<int>(WRITECOMMAND_SIZE); i++)
        {
            command[i] = *(writeCommand+i);
            qDebug() << command[i];
        }
    memcpy(m_pbSend, command, WRITECOMMAND_SIZE); m_cbSend = WRITECOMMAND_SIZE; m_cbRecv = MAX_APDU_SIZE;
    m_lRet = SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv);
    SCardConnection::setResponse(m_pbRecv);
    return m_lRet;
}
void SCardConnection::setResponse(BYTE* response)
{qDebug() << "set response";
    for(DWORD i = 0 ; i<RESPONSE_SIZE ; i++)
    {
        m_response[i] = *(response+i);

    qDebug() << Qt::hex << m_response[i];
}}
BYTE* SCardConnection::getResponse()
{
    return m_response;
}

