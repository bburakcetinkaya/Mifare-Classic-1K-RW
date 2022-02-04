#ifndef COMMANDS_H
#define COMMANDS_H

#include <winscard.h>
#include <windows.h>


inline constexpr DWORD MAX_APDU_SIZE = 255;
inline constexpr DWORD RESPONSE_SIZE = 2;
inline constexpr DWORD UID_SIZE = 4;
inline constexpr DWORD KEY_SIZE = 6;
inline constexpr DWORD AUTHCOMMAND_SIZE = 10;
inline constexpr DWORD READCOMMAND_SIZE = 5;
inline constexpr DWORD LOADCOMMAND_SIZE = 10;
inline constexpr BYTE  BLOCK_SIZE = 0x10;
inline constexpr BYTE  KEYA_SELECT = 0X60;
inline constexpr BYTE  KEYB_SELECT = 0X61;
inline constexpr BYTE  readUIDCommand[] = {0xFF, 0xCA, 0x00, 0x00, 0x00};
inline constexpr BYTE  loadKeyCommand[] = {0xFF, 0x82, 0x00};
inline constexpr BYTE  authCommand[] = {0xFF, 0x86, 0x00, 0x00, 0x05, 0x00, 0x00};
inline constexpr BYTE  readBlockDataCommand[] = {0xFF, 0xB0, 0x00};
inline constexpr BYTE  SUCCESS_RESPONSE[] = {0x90,0x00};

// 0xFF,  0x86,  0x00, 0x00,  0x05,  0x00, 0x00,  0x04, 0x60, 0x00 };


#endif // COMMANDS_H
