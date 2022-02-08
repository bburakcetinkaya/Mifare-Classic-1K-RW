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
SCardConnection::SCardConnection()
{
    m_readerList ={}
   ,m_hContext = 0
   ,m_pmszReaders = NULL
   ,m_lRet = 0
   ,m_dwAP = 0
   ,m_cch = SCARD_AUTOALLOCATE
   ,m_hCard = 0
   ,m_cbSend = 0
   ,m_cbRecv = MAX_APDU_SIZE
   ,m_cardUID[UID_SIZE] = {}
   ,m_blockNum = 0x00
   ,m_pbSend[MAX_APDU_SIZE] = {}
   ,m_pbRecv[MAX_APDU_SIZE] = {} ;
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
void SCardConnection::setReaderLists()
{
    m_lRet =SCardListReaders(m_hContext, NULL, (LPTSTR)&m_pmszReaders, &m_cch);
}
LPTSTR SCardConnection::getReaderLists()
{
    return m_pmszReaders;
}
void SCardConnection::connectCard()
{
   SCardConnect(m_hContext, m_pmszReaders,SCARD_SHARE_SHARED, SCARD_PROTOCOL_Tx, &m_hCard, &m_dwAP);
}
void SCardConnection::disconnectCard()
{
    SCardDisconnect(m_hCard,SCARD_LEAVE_CARD);    
}
void SCardConnection::setCardUID()
{
    memcpy(m_pbSend, readUIDCommand, sizeof(readUIDCommand));
    m_cbSend = sizeof(readUIDCommand);
    m_cbRecv = MAX_APDU_SIZE;

    if((m_lRet = SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv,&m_cbRecv)) == SCARD_S_SUCCESS)
    {
        if(m_cbRecv>2)
            {
                for (DWORD i = 0; i < m_cbRecv-2; i++)
                {
                    m_cardUID[i] = m_pbRecv[i];
                }
            }
    }
    if(m_lRet != SCARD_S_SUCCESS || m_cbRecv <= 2)
    {
        for (DWORD i = 0; i < UID_SIZE; i++)
        {
            m_cardUID[i] = 0x00;
        }
    }
}
QString SCardConnection::getCardUID()
{
    QByteArray UID =  QByteArray(reinterpret_cast<char*>(m_cardUID), sizeof(m_cardUID)).toHex(' ').toUpper();
    QString UIDstring = QString(UID).toUpper();
    qDebug() << UIDstring;
    return UIDstring;
}
LONG SCardConnection::loadKey(BYTE *loadCommand)// will have a byte ptr return type to handle response
{
    BYTE command[LOADCOMMAND_SIZE] = {};
    for(int i = 0; i<static_cast<int>(LOADCOMMAND_SIZE); i++)
        {
            command[i] = *(loadCommand+i);
        }
    memcpy(m_pbSend, command, LOADCOMMAND_SIZE);
    m_cbSend = LOADCOMMAND_SIZE;
    m_cbRecv = MAX_APDU_SIZE;
    m_lRet = SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv);
    if( m_pbRecv[0] == SUCCESS_RESPONSE[0] && m_pbRecv[1] == SUCCESS_RESPONSE[1] )
        return m_lRet;
    return 55;

}
LONG SCardConnection::authenticate(BYTE *authCommand)
{
   BYTE command[AUTHCOMMAND_SIZE];
   for(int i = 0; i<static_cast<int>(AUTHCOMMAND_SIZE); i++)
       command[i] = *(authCommand+i);
   memcpy(m_pbSend, command, AUTHCOMMAND_SIZE);
   m_cbSend = AUTHCOMMAND_SIZE;
   m_cbRecv = MAX_APDU_SIZE;
   m_lRet=SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv);
       if( m_pbRecv[0] == SUCCESS_RESPONSE[0] && m_pbRecv[1] == SUCCESS_RESPONSE[1] )
           return m_lRet;
       return !SCARD_S_SUCCESS;

}
QString SCardConnection::readDataBlock(BYTE *readCommand)
{
    BYTE command[READCOMMAND_SIZE] = {};
    for(int i = 0; i<static_cast<int>(READCOMMAND_SIZE); i++)
        command[i] = *(readCommand+i);
    memcpy(m_pbSend, command, READCOMMAND_SIZE);
    m_cbSend = READCOMMAND_SIZE;
    m_cbRecv = MAX_APDU_SIZE;
    // clear recieve var
    for(int i = 0; i<static_cast<int>(MAX_APDU_SIZE); i++)
        m_pbRecv[i] = {};
    SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv);

    if(m_cbRecv == BLOCK_SIZE+RESPONSE_SIZE)
    {
        QByteArray blockAsByte =  QByteArray(reinterpret_cast<char*>(m_pbRecv), BLOCK_SIZE+RESPONSE_SIZE).toHex(' ').toUpper();
        QString blockString = QString(blockAsByte).toUpper();
        return blockString;
    }
    return "";
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
        command[i] = *(writeCommand+i);
    memcpy(m_pbSend, command, WRITECOMMAND_SIZE);
    m_cbSend = WRITECOMMAND_SIZE;
    m_cbRecv = MAX_APDU_SIZE;
    m_lRet=SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv);
    return m_lRet;

}
void SCardConnection::clearpmszReaders()
{
 SCardFreeMemory(m_hContext,m_pmszReaders);
}
BYTE SCardConnection::getpbRecv()
{
    return *m_pbRecv;
}
BYTE SCardConnection::getpbSend()
{
    return *m_pbSend;
}
DWORD SCardConnection::getcbRecv()
{
    return m_cbRecv;
}
DWORD SCardConnection::getcbSend()
{
    return m_cbSend;
}
