#ifndef COMMANDS_H
#define COMMANDS_H

#include <winscard.h>
#include <windows.h>


inline constexpr DWORD MAX_APDU_SIZE = 255;
inline constexpr DWORD RESPONSE_SIZE = 2;
inline constexpr DWORD UID_SIZE = 4;
inline constexpr DWORD KEY_SIZE = 6;
inline constexpr BYTE  readUIDCommand[] = {0xFF, 0xCA, 0x00, 0x00, 0x00};



#endif // COMMANDS_H
