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
    static  SCardConnection* getInstance();
    LONG    establishContext();
    void    disconnectReader();

    void    clearpmszReaders();
    LONG    setReaderLists();
    LPTSTR  getReaderLists();
    LONG    connectCard();
    LONG    disconnectCard();
    LONG    setCardUID();
    QString getCardUID();
    QString getReadDataBlockString();


    BYTE    getBlockNum();
    void    setBlockNum(const QString &blockAsString);

    LONG    authenticate(BYTE *authCommand);
    LONG    readDataBlock(BYTE *readCommand);
    LONG    loadKey(BYTE *loadCommand);
    LONG    writeDataBlock(BYTE *writeCommand);

    void    setResponse(BYTE* response);
    BYTE*   getResponse();

    LONG    readValueBlock(BYTE* readValueBlockCommand);
    long int getValue();

    QByteArray getBlockAsByte();

    LONG incrDecrValueBlock(BYTE* command);




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
    QString         m_blockDataString;
    QList<QString>  m_readerList;
    BYTE            m_response[RESPONSE_SIZE];
    QString         m_valueBlockAsString;
    long int        m_value;
    QByteArray      m_blockAsByte;
};

#endif // CONNECT_H
