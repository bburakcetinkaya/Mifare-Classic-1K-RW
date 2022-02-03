#include "Headers/scardoperations.h"
#include "Headers/apducommand.h"
#include "Headers/connect.h"
#include <QDebug>


SCardOperations::SCardOperations()
{
    m_keyA[KEY_SIZE] = {}
   ,m_keyB[KEY_SIZE] = {};
}
void SCardOperations::setKeyA( const QString _keyA )
{
    QByteArray _keyABytes = QByteArray::fromHex(_keyA.toLatin1());
    for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
    {
        m_keyA[i] = _keyABytes[i];
    }
}

BYTE* SCardOperations::getKeyA()
{

    return  m_keyA;
}

void SCardOperations::setKeyB( const QString _keyB )
{
    QByteArray _keyBBytes = QByteArray::fromHex(_keyB.toLatin1());
    for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
    {
        m_keyB[i] = _keyBBytes[i];
    }
}

BYTE* SCardOperations::getKeyB()
{
    return m_keyB;
}








