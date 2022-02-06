#include "Headers/scardoperations.h"
#include "Headers/apducommand.h"
#include "Headers/connect.h"
#include <QDebug>


SCardOperations::SCardOperations()
{
    m_keyA[KEY_SIZE] = {}
   ,m_keyB[KEY_SIZE] = {};
}
void SCardOperations::setKeyA( const BYTE *_keyA )
{
    for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
    {
        m_keyA[i] = *(_keyA+i);
    }
}

BYTE* SCardOperations::getKeyA()
{

    return  m_keyA;
}

void SCardOperations::setKeyB( const BYTE *_keyB )
{
       for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
    {
        m_keyB[i] = *(_keyB+i);
    }
}

BYTE* SCardOperations::getKeyB()
{
    return m_keyB;
}








