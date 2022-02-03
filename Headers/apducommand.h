#ifndef APDUCOMMAND_H
#define APDUCOMMAND_H
#include "Headers/commands.h"
#include <windows.h>

class APDUCommand
{
public:
    APDUCommand();
    void setAuthCommand(const BYTE block, const BYTE* key, const BYTE keySelect);
    BYTE* getAuthCommand();

    void setReadCommand(const BYTE block);
    BYTE* getReadCommand();

    void setWriteCommand();
    BYTE* getWriteCommand();

private:
    BYTE m_AuthCommand[AUTHCOMMAND_SIZE];
    BYTE m_ReadCommand[AUTHCOMMAND_SIZE];
    BYTE m_WriteCommand[AUTHCOMMAND_SIZE];


};

#endif // APDUCOMMAND_H
