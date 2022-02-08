#include "Headers/apducommand.h"
#include "Headers/commands.h"
#include <cstdio>
#include <QDebug>
#include <bitset>

APDUCommand::APDUCommand()
{
     m_AuthCommand[AUTHCOMMAND_SIZE] = {}
    ,m_ReadCommand[READCOMMAND_SIZE] = {}
    ,m_WriteCommand[WRITECOMMAND_SIZE] = {};

}

void APDUCommand::setLoadKeyCommand(const BYTE* key, const BYTE storageAddress)
{//printf("loadcommand: ");
    for( int i=0; i<static_cast<int>(LOADCOMMAND_SIZE); i++)
    {
        switch (i)
        {
        case 0:       case 1:       case 2:
            m_LoadKeyCommand[i] = loadKeyCommand[i];
            break;
        case 3:
            m_LoadKeyCommand[i] = storageAddress;
            break;
        case 4:
            m_LoadKeyCommand[i] = (BYTE)KEY_SIZE;
            break;
        case 5:       case 6:       case 7:       case 8:       case 9:       case 10:
            m_LoadKeyCommand[i] = *(key+i-5);
            break; //0xFF, 0x82, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
         }
        qDebug() << m_LoadKeyCommand[i];
    //printf("%X ",m_LoadKeyCommand[i]);
    }
}
BYTE* APDUCommand::getLoadKeyCommand()
{
    return m_LoadKeyCommand;
}

void APDUCommand::setAuthCommand(const BYTE block, const BYTE keySelect)
{
    for( int i=0; i<static_cast<int>(AUTHCOMMAND_SIZE); i++)
    {
        switch (i)
        {
        case 0:       case 1:       case 2:       case 3:       case 4:        case 5:          case 6:
            m_AuthCommand[i] = authCommand[i];
            break;
        case 7:
            m_AuthCommand[i] = (BYTE)block;
            break;
        case 8:
            m_AuthCommand[i] = keySelect;
            break;
        case 9:
            m_AuthCommand[i] = 0x00;
            break;
         }
        //qDebug() <<m_AuthCommand[i];

    }
}
BYTE* APDUCommand::getAuthCommand()
{
    //for(int i = 0 ; i<static_cast<int>(AUTHCOMMAND_SIZE); i++)
    //printf("%X ",m_AuthCommand[i]);
    return m_AuthCommand;
}

void APDUCommand::setReadCommand(const BYTE block)
{
    for( int i=0; i<static_cast<int>(READCOMMAND_SIZE); i++)
    {
        switch (i)
        {
        case 0:       case 1:       case 2:
            m_ReadCommand[i] = readBlockDataCommand[i];
            break;
        case 3:
            m_ReadCommand[i] = block;
            break;
        case 4:
            m_ReadCommand[i] = BLOCK_SIZE;
            break;
         }
        qDebug() << m_ReadCommand[i];
    }
}//FF B1 00 01 04
void APDUCommand::setReadValueBlockCommand(const BYTE block)
{
    for( int i=0; i<static_cast<int>(READCOMMAND_SIZE); i++)
    {
        switch (i)
        {
        case 0:       case 1:       case 2:
            m_ReadCommand[i] = readValueBlock[i];
            break;
        case 3:
            m_ReadCommand[i] = block;
            break;
        case 4:
            m_ReadCommand[i] = 0x04;
            break;
         }
        //qDebug() << m_ReadCommand[i];
    }
}
BYTE* APDUCommand::getReadCommand()
{
    return m_ReadCommand;
}

void APDUCommand::setWriteCommand(const BYTE block, const BYTE *writeCmd)
{    
    for( int i=0; i<static_cast<int>(WRITECOMMAND_SIZE); i++)
    {
        switch (i)
        {
        case 0:       case 1:       case 2:
            m_WriteCommand[i] = writeBlockDataCommand[i];
            break;
        case 3:
            m_WriteCommand[i] = block;
            break;
        case 4:
            m_WriteCommand[i] = BLOCK_SIZE;
            break;
        case 5:       case 6:       case 7:     case 8:
        case 9:       case 10:      case 11:    case 12:
        case 13:      case 14:      case 15:    case 16:
        case 17:      case 18:      case 19:    case 20:
            m_WriteCommand[i] = *(writeCmd+i-5);
            break;
         }
        printf("%X ",m_WriteCommand[i]);
    }

}
void APDUCommand::setValueBlockCommand(const BYTE block,const BYTE *value)
{
     for( int i=0; i<static_cast<int>(WRITECOMMAND_SIZE); i++)
     {
         switch (i)
         {
         case 0:       case 1:       case 2:
             m_WriteCommand[i] = writeBlockDataCommand[i];
             break;
         case 3:
             m_WriteCommand[i] = block;
             break;
         case 4:
             m_WriteCommand[i] = BLOCK_SIZE;
             break;
         case 5:       case 6:       case 7:     case 8:
             m_WriteCommand[i] = *(value+i-5);
             break;
         case 9:       case 10:      case 11:    case 12:
             m_WriteCommand[i] = ~(*(value+i-9));
             break;
         case 13:      case 14:      case 15:    case 16:
             m_WriteCommand[i] = *(value+i-13);
             break;
         case 17:
             m_WriteCommand[i] = 0x00;
             break;
         case 18:
             m_WriteCommand[i] = ~(0x00);
             break;
         case 19:
             m_WriteCommand[i] = 0x00;
             break;
         case 20:
             m_WriteCommand[i] = ~(0x00);
             break;
          }
      }
 }
void APDUCommand::setIncDecCommand(const BYTE selection, const BYTE block)
{//printf("loadcommand: ");
    for( int i=0; i<static_cast<int>(LOADCOMMAND_SIZE); i++)
    {////FF FC 00 00 06 C1 1E 01 00 00 00
        switch (i)
        {
        case 0:       case 1:       case 2:     case 3:     case 4:
            m_IncrDecrCommand[i] = incDecCommand1[i];
            break;
        case 5:
            m_IncrDecrCommand[i] = selection;
            break;
        case 6:
            m_IncrDecrCommand[i] = block;
            break;
        case 7:       case 8:       case 9:       case 10:
            m_IncrDecrCommand[i] = incDecCommand2[i-7];
            break;
         }
        qDebug() << m_IncrDecrCommand[i];

    //printf("%X ",m_LoadKeyCommand[i]);
    }
}

 BYTE* APDUCommand::getWriteCommand()
{
    return m_WriteCommand;
}
BYTE* APDUCommand::getIncrDecrCommand()
{
    return m_IncrDecrCommand;
}
