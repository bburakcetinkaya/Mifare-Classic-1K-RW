#include "Headers/apducommand.h"
#include "Headers/commands.h"
#include <cstdio>

APDUCommand::APDUCommand()
{
    m_AuthCommand[AUTHCOMMAND_SIZE] = {};
    m_ReadCommand[READCOMMAND_SIZE] = {};

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
         }//0xFF,  0x86,  0x00, 0x00,  0x05,  0x00, 0x00,  0x04, 0x60, 0x00
    printf("%X ",m_AuthCommand[i]);
    }
}
BYTE* APDUCommand::getAuthCommand()
{
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
         } //0xFF, 0xB0, 0x00, 0x00, 0x10
        printf("%X ",m_ReadCommand[i]);

    }

}
BYTE* APDUCommand::getReadCommand()
{
    return m_ReadCommand;
}

void APDUCommand::setWriteCommand()
{

}
//BYTE* APDUCommand::getWriteCommand()
//{
//    return m_WriteCommand;
//}
