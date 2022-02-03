#include "Headers/apducommand.h"
#include "Headers/commands.h"

APDUCommand::APDUCommand()
{
    m_AuthCommand[AUTHCOMMAND_SIZE] = {};
}
void APDUCommand::setAuthCommand(const BYTE block, const BYTE* key, const BYTE keySelect)
{
    for( int i=0; i<static_cast<int>(AUTHCOMMAND_SIZE); i++)
    {
        switch (i)
        {
        case 0:       case 1:       case 2:       case 3:       case 4:        case 5:          case 6:
            m_AuthCommand[i] = authCommand[i];
            break;
        case 7:
            m_AuthCommand[i] = block;
            break;
        case 8:
            m_AuthCommand[i] = keySelect;
            break;
        case 9:       case 10:       case 11:       case 12:       case 13:       case 14:
            m_AuthCommand[i] = *(key+i-9);
            break;

         }
    }
}
BYTE* APDUCommand::getAuthCommand()
{
    return m_AuthCommand;
}

void APDUCommand::setReadCommand(const BYTE block)
{
    for( int i=0; i<static_cast<int>(AUTHCOMMAND_SIZE); i++)
    {
        switch (i)
        {
        case 0:       case 1:       case 2:
            m_ReadCommand[i] = readBlockDataCommand[i];
            break;
        case 3:
            m_ReadCommand[i] = block;
        case 4:
            m_ReadCommand[i] = BLOCK_SIZE;
         }
    }
}
BYTE* APDUCommand::getReadCommand()
{
    return m_ReadCommand;
}

void APDUCommand::setWriteCommand()
{

}
BYTE* APDUCommand::getWriteCommand()
{
    return m_WriteCommand;
}
