#ifndef COMMANDS_H
#define COMMANDS_H

#include <winscard.h>
#include <windows.h>


inline constexpr DWORD MAX_APDU_SIZE = 255;
inline constexpr DWORD RESPONSE_SIZE = 2;
inline constexpr DWORD UID_SIZE = 4;
inline constexpr BYTE KEY_SIZE = 0x06;
inline constexpr DWORD AUTHCOMMAND_SIZE = 10;
inline constexpr DWORD READCOMMAND_SIZE = 5;
inline constexpr BYTE LOADCOMMAND_SIZE = 0x0B;
inline constexpr DWORD WRITECOMMAND_SIZE = 21;
inline constexpr BYTE  BLOCK_SIZE = 0x10;
inline constexpr BYTE  V_MEMORY = 0x00;
inline constexpr BYTE  NV_MEMORY = 0x01;
inline constexpr BYTE  KEYA_SELECT = 0X60;
inline constexpr BYTE  KEYB_SELECT = 0X61;
inline constexpr BYTE  readUIDCommand[] = {0xFF, 0xCA, 0x00, 0x00, 0x00};
inline constexpr BYTE  loadKeyCommand[] = {0xFF, 0x82, 0x00};
inline constexpr BYTE  authCommand[] = {0xFF, 0x86, 0x00, 0x00, 0x05, 0x00, 0x00};
inline constexpr BYTE  readBlockDataCommand[] = {0xFF, 0xB0, 0x00};
inline constexpr BYTE  writeBlockDataCommand[] = {0xFF, 0xD6, 0x00};
inline constexpr BYTE  SUCCESS_RESPONSE[] = {0x90,0x00};


//"\xFF\xD6\x00\x01\x10\x11\x22\x33\x44\x55\x66\x11\x22\x33\x44\x55\x66\x33\x44\x55\x66"
// 0xFF,  0x86,  0x00, 0x00,  0x05,  0x00, 0x00,  0x04, 0x60, 0x00 };


#endif // COMMANDS_H
