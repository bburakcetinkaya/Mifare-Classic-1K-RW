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
void SCardConnection::setEstablishContext()
{
   m_hContext = NULL;
   m_lRet = SCardEstablishContext(SCARD_SCOPE_USER, 0, 0, &m_hContext);
}
LONG SCardConnection::getEstablishContext()
{
    return m_lRet;
}
void SCardConnection::setReaderLists(bool choice)
{
       m_pmszReaders = NULL;
       if(choice) SCardListReaders(m_hContext,
                                   NULL,
                                   (LPTSTR)&m_pmszReaders,
                                   &m_cch );
       else m_pmszReaders = NULL;
}
LPTSTR SCardConnection::getReaderLists()
{
    return m_pmszReaders;
}
void SCardConnection::connectCard()
{


//    m_lRet = SCardEstablishContext(SCARD_SCOPE_USER, 0, 0, &m_hContext);
//    SCardListReaders(m_hContext,
//                                       NULL,
//                                       (LPTSTR)&m_pmszReaders,
//                                       &m_cch );
    m_lRet = SCardConnect(m_hContext,
                          m_pmszReaders,
                          SCARD_SHARE_SHARED,
                          SCARD_PROTOCOL_Tx,
                          &m_hCard,
                          &m_dwAP);
}
void SCardConnection::setCardUID()
{
    m_pbRecv[MAX_APDU_SIZE] = {};
    memcpy(m_pbSend, readUIDCommand, sizeof(readUIDCommand));
    m_cbSend = sizeof(readUIDCommand);
    m_cbRecv = MAX_APDU_SIZE;
    if ((m_lRet = SCardTransmit(m_hCard,
                                SCARD_PCI_T1,
                                m_pbSend,
                                m_cbSend,
                                NULL,
                                m_pbRecv,
                                &m_cbRecv)) == SCARD_S_SUCCESS)
    {
        for (DWORD i = 0; i < m_cbRecv; i++)
        {
            m_cardUID[i] = m_pbRecv[i];
            printf("%02X",m_pbRecv[i]);
        }
    }
}
QString SCardConnection::getCardUID()
{
    QByteArray UID =  QByteArray(reinterpret_cast<char*>(m_cardUID), sizeof(m_cardUID)).toHex(' ');
    QString UIDS = QString(UID).toUpper();
    qDebug() << UIDS;
    return UIDS;
}
