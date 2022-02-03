#include "Headers\connect.h"
#include "Headers\commands.h"
#include <winscard.h>
#include <cstdio>
#include <QByteArray>
#include <QString>
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
    m_hContext = 0
   ,m_pmszReaders = NULL
   ,m_lRet = 0
   ,m_dwAP = 0
   ,m_cch = SCARD_AUTOALLOCATE
   ,m_hCard = 0
   ,m_cbSend = 0
   ,m_cbRecv = MAX_APDU_SIZE
   ,m_cardUID[UID_SIZE] = {}
   ,m_pbSend[MAX_APDU_SIZE] = {}
   ,m_pbRecv[MAX_APDU_SIZE] = {} ;
}
LONG SCardConnection::establishContext()
{
   m_hContext = NULL;
   m_lRet = SCardEstablishContext(SCARD_SCOPE_USER, 0, 0, &m_hContext);
   return m_lRet;
}

void SCardConnection::setReaderLists(const bool choice)
{
       if(m_pmszReaders != NULL)
       {
            m_pmszReaders = NULL;
            if(choice) SCardListReaders(m_hContext, NULL, (LPTSTR)&m_pmszReaders, &m_cch );
           // m_pmszReaders = m_pmszReaders + wcslen((wchar_t *)m_pmszReaders) + 1; // for acr122u picc
       }
       else
       {
           if(choice) SCardListReaders(m_hContext, NULL, (LPTSTR)&m_pmszReaders, &m_cch );
          // m_pmszReaders = m_pmszReaders + wcslen((wchar_t *)m_pmszReaders) + 1; // for acr122u picc
       }
}
LPTSTR SCardConnection::getReaderLists()
{
    return m_pmszReaders;
}
void SCardConnection::connectCard()
{
   SCardConnect(m_hContext, m_pmszReaders,SCARD_SHARE_SHARED, SCARD_PROTOCOL_Tx, &m_hCard, &m_dwAP);
}
void SCardConnection::setCardUID()
{
    memcpy(m_pbSend, readUIDCommand, sizeof(readUIDCommand));
    m_cbSend = sizeof(readUIDCommand);
    m_cbRecv = MAX_APDU_SIZE;
    if(SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv,&m_cbRecv) == SCARD_S_SUCCESS)
    {
        qDebug() << "success";
        for (DWORD i = 0; i < m_cbRecv-2; i++)
        {
            m_cardUID[i] = m_pbRecv[i];
        }
    }
    else
    {
        for (DWORD i = 0; i < UID_SIZE; i++)
        {
            m_cardUID[i] = 0x00;
        }
        qDebug() << "failed"; }
}
QString SCardConnection::getCardUID()
{
    QByteArray UID =  QByteArray(reinterpret_cast<char*>(m_cardUID), sizeof(m_cardUID)).toHex(' ').toUpper();
    //QString UID = QString::fromUtf8(m_cardUID);
    QString UIDstring = QString(UID).toUpper();
    qDebug() << UIDstring;
    return UIDstring;
}
void SCardConnection::authenticate(BYTE *authCommand)
{
   BYTE command[AUTHCOMMAND_SIZE];
   for(int i = 0; i<static_cast<int>(AUTHCOMMAND_SIZE); i++)
       command[i] = *(authCommand+i);
   memcpy(m_pbSend, command, AUTHCOMMAND_SIZE);
   m_cbSend = AUTHCOMMAND_SIZE;
   m_cbRecv = MAX_APDU_SIZE;
   if ((SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv)) != SCARD_S_SUCCESS)
   {
        printf("fuck");
       return;
   }
   else printf("authentication of sector %d is completed \n",(command[7])/4);

}
void SCardConnection::readDataBlock(BYTE *readCommand)
{
    BYTE command[READCOMMAND_SIZE];
    for(int i = 0; i<static_cast<int>(READCOMMAND_SIZE); i++)
        command[i] = *(readCommand+i);
    memcpy(m_pbSend, command, READCOMMAND_SIZE);
    m_cbSend = READCOMMAND_SIZE;
    m_cbRecv = MAX_APDU_SIZE;
    if (SCardTransmit(m_hCard, SCARD_PCI_T1, m_pbSend, m_cbSend, NULL, m_pbRecv, &m_cbRecv) != SCARD_S_SUCCESS)
        return;

    printf("\nBlock 02: ");
    for (DWORD i = 0 ; i < m_cbRecv; i++) //-2
    {
        printf("%02X ", m_pbRecv[i]);

    }
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
