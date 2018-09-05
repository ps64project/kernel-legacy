#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// Textmode :: Text color attributes

const BYTE CON_BLACK       = 0x00;
const BYTE CON_BLUE        = 0x01;
const BYTE CON_GREEN       = 0x02;
const BYTE CON_CYAN        = 0x03;
const BYTE CON_RED         = 0x04;
const BYTE CON_MAGENTA     = 0x05;
const BYTE CON_BROWN       = 0x06;
const BYTE CON_LIGHT_GRAY  = 0x07;
const BYTE CON_DRAK_GRAY   = 0x08;
const BYTE CON_LIGHT_BLUE  = 0x09;
const BYTE CON_LIGHT_GREEN = 0x0A;
const BYTE CON_LIGHT_CYAN  = 0x0B;
const BYTE CON_LIGHT_RED   = 0x0C;
const BYTE CON_PINK        = 0x0D;
const BYTE CON_YELLOW      = 0x0E;
const BYTE CON_WHITE       = 0x0F;

constexpr inline BYTE _CONSOLE_ATTRIBUTE(
        const BYTE foreground, 
        const BYTE background
        ) noexcept {
    return (background << 4) | foreground;
}

// Page Entry :: Attributes 

const DWORD PAGE_FLAGS_P     = 1;
const DWORD PAGE_FLAGS_RW    = 1 << 1;
const DWORD PAGE_FLAGS_US    = 1 << 2;
const DWORD PAGE_FLAGS_PWT   = 1 << 3;
const DWORD PAGE_FLAGS_PCD   = 1 << 4;
const DWORD PAGE_FLAGS_A     = 1 << 5;
const DWORD PAGE_FLAGS_D     = 1 << 6;
const DWORD PAGE_FLAGS_PS    = 1 << 7;
const DWORD PAGE_FLAGS_G     = 1 << 8;
const DWORD PAGE_FLAGS_PAT   = 1 << 11;

#endif
