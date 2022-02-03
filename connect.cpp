#include "connect.h"
#include "commands.h"
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
