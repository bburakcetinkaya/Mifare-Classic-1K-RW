#ifndef CONNECT_H
#define CONNECT_H
#include <winscard.h>
#include <commands.h>
#include <QString>

enum choice
{
    clear,
    set
};

class SCardConnection
{
public:
    static SCardConnection* getInstance();
    void setEstablishContext();
    LONG getEstablishContext();
    void setReaderLists(bool choice);
    LPTSTR getReaderLists();
    void connectCard();
    void setCardUID();
    QString getCardUID();


private:
    static SCardConnection* instance;
    SCardConnection();
    SCARDCONTEXT    m_hContext;
    LPTSTR          m_pmszReaders;
    LONG            m_lRet;
    DWORD           m_dwAP;
    DWORD           m_cch;
    SCARDHANDLE     m_hCard;
    DWORD           m_cbSend;
    DWORD           m_cbRecv;
    BYTE            m_cardUID[UID_SIZE];
    BYTE            m_pbSend[MAX_APDU_SIZE];
    BYTE            m_pbRecv[MAX_APDU_SIZE];

};

#endif // CONNECT_H
