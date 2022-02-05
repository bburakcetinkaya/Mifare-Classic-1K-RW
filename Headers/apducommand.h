#ifndef APDUCOMMAND_H
#define APDUCOMMAND_H
#include "Headers/commands.h"
#include <windows.h>

class APDUCommand
{
public:
    APDUCommand();
    void setAuthCommand(const BYTE block, const BYTE keySelect, const BYTE storageAddress);
    BYTE* getAuthCommand();

    void setReadCommand(const BYTE block);
    BYTE* getReadCommand();

    void setWriteCommand(const BYTE block, const BYTE *writeCmd);
    BYTE* getWriteCommand();

    void setLoadKeyCommand(const BYTE* key, const BYTE storageAddress);
    BYTE* getLoadKeyCommand();

private:
    BYTE m_AuthCommand[AUTHCOMMAND_SIZE];
    BYTE m_ReadCommand[READCOMMAND_SIZE];
    BYTE m_LoadKeyCommand[LOADCOMMAND_SIZE];
    BYTE m_WriteCommand[WRITECOMMAND_SIZE];


};

#endif // APDUCOMMAND_H
