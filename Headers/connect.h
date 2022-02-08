#ifndef CONNECT_H
#define CONNECT_H
#include <winscard.h>
#include <Headers\commands.h>
#include <QString>
#include <QList>

enum choice
{
    clear,
    set
};

class SCardConnection
{
public:
    static SCardConnection* getInstance();
    LONG establishContext();
    void disconnectReader();

    void clearpmszReaders();
    void setReaderLists();
    LPTSTR  getReaderLists();
    void connectCard();
    void disconnectCard();
    void setCardUID();
    QString getCardUID();
    BYTE getpbRecv();
    BYTE getpbSend();
    DWORD getcbRecv();
    DWORD getcbSend();

    BYTE getBlockNum();
    void setBlockNum(const QString &blockAsString);

    LONG authenticate(BYTE *authCommand);
    QString readDataBlock(BYTE *readCommand);
    LONG loadKey(BYTE *loadCommand);
    LONG writeDataBlock(BYTE *writeCommand);




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
    BYTE            m_blockNum;
    int             m_readFlag;
    QList<QString>  m_readerList;

};

#endif // CONNECT_H
