#ifndef SCARDOPERATIONS_H
#define SCARDOPERATIONS_H

#include <winscard.h>
#include <Headers\commands.h>
#include <QByteArray>
#include <QString>

class SCardOperations
{
public:

    SCardOperations();
    void setKeyA(const QString _keyA);
    BYTE* getKeyA();

    void setKeyB(const QString _keyB);
    BYTE* getKeyB();

private:

    BYTE m_keyA[KEY_SIZE];
    BYTE m_keyB[KEY_SIZE];
};

#endif // SCARDOPERATIONS_H
