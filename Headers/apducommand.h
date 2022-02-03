#ifndef APDUCOMMAND_H
#define APDUCOMMAND_H
#include <windows.h>

class APDUCommand
{
public:
    APDUCommand();
    void setAPDUCommand();
    BYTE getAPDUCommand();

private:
    BYTE m_command;

};

#endif // APDUCOMMAND_H
