#ifndef COMMANDS_H
#define COMMANDS_H

#include <winscard.h>
#include <windows.h>
#include <cstdint>


inline constexpr DWORD MAX_APDU_SIZE = 255;
inline constexpr DWORD RESPONSE_SIZE = 2;
inline constexpr DWORD UID_SIZE = 4;
inline constexpr BYTE KEY_SIZE = 0x06;
inline constexpr DWORD AUTHCOMMAND_SIZE = 10;
inline constexpr DWORD READCOMMAND_SIZE = 5;
inline constexpr BYTE LOADCOMMAND_SIZE = 0x0B;
inline constexpr DWORD WRITECOMMAND_SIZE = 21;
inline constexpr BYTE  DECINCCOMMAND_SIZE = 0x0B;
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
inline constexpr BYTE  readValueBlock[] = {0xFF, 0xB1, 0x00};
inline constexpr BYTE  incDecCommand1[] = { 0xFF, 0xFC, 0x00, 0x00, 0x06};
inline constexpr BYTE  incDecCommand2[] = { 0x01, 0x00, 0x00, 0x00};
inline constexpr BYTE  INCREMENT_SELECT = 0xC1;
inline constexpr BYTE  DECREMENT_SELECT = 0xC0;
inline constexpr BYTE  TRANSPORT_CONFIG[] = {0x00};


inline constexpr BYTE mask0{ 0x1 }; // hex for 0000 0001
inline constexpr BYTE mask1{ 0x2 }; // hex for 0000 0010
inline constexpr BYTE mask2{ 0x4 }; // hex for 0000 0100
inline constexpr BYTE mask3{ 0x8 }; // hex for 0000 1000
inline constexpr BYTE mask4{ 0x10 }; // hex for 0001 0000
inline constexpr BYTE mask5{ 0x20 }; // hex for 0010 0000
inline constexpr BYTE mask6{ 0x40 }; // hex for 0100 0000
inline constexpr BYTE mask7{ 0x80 }; // hex for 1000 0000
//#Prepare Block as value block (Block No. : 1E, Value : 64000000)
//FF D6 00 1E 10 64 00 00 00 9B FF FF FF 64 00 00 00 00 FF 00 FF
//#Value Increment (Block No. : 1E, Increment by 1)
//FF FC 00 00 06 C1 1E 01 00 00 00
//9000

//#Value Decrement (Block No. : 1E, Decrement by 3)
//FFFC000006C0 1E 03000000

//"\xFF\xD6\x00\x01\x10\x11\x22\x33\x44\x55\x66\x11\x22\x33\x44\x55\x66\x33\x44\x55\x66"
// 0xFF,  0x86,  0x00, 0x00,  0x05,  0x00, 0x00,  0x04, 0x60, 0x00 };


#endif // COMMANDS_H
