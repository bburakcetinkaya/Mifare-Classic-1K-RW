#include "Headers/apducommand.h"
#include "Headers/commands.h"
#include <cstdio>

APDUCommand::APDUCommand()
{
     m_AuthCommand[AUTHCOMMAND_SIZE] = {}
    ,m_ReadCommand[READCOMMAND_SIZE] = {}
    ,m_WriteCommand[WRITECOMMAND_SIZE] = {};

}
void APDUCommand::setLoadKeyCommand(const BYTE* key, const BYTE storageAddress)
{
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
//        case 4:
//            m_LoadKeyCommand[i] = (BYTE)KEY_SIZE;
        case 4:       case 5:       case 6:       case 7:       case 8:       case 9:
            m_LoadKeyCommand[i] = *(key+i-9);
            break; //0xFF, 0x82, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
         }
    }
}
BYTE* APDUCommand::getLoadKeyCommand()
{
    return m_LoadKeyCommand;
}
void APDUCommand::setAuthCommand(const BYTE block, const BYTE keySelect, const BYTE storageAddress)
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
            m_AuthCommand[i] = storageAddress;
            break;
         }

    }
}
BYTE* APDUCommand::getAuthCommand()
{
    for(int i = 0 ; i<static_cast<int>(AUTHCOMMAND_SIZE); i++)
    printf("%X ",m_AuthCommand[i]);
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
BYTE* APDUCommand::getWriteCommand()
{
    return m_WriteCommand;
}
