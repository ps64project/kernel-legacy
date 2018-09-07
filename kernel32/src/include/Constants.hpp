#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// Textmode :: Text color attributes

constexpr BYTE CON_BLACK       = 0x00;
constexpr BYTE CON_BLUE        = 0x01;
constexpr BYTE CON_GREEN       = 0x02;
constexpr BYTE CON_CYAN        = 0x03;
constexpr BYTE CON_RED         = 0x04;
constexpr BYTE CON_MAGENTA     = 0x05;
constexpr BYTE CON_BROWN       = 0x06;
constexpr BYTE CON_LIGHT_GRAY  = 0x07;
constexpr BYTE CON_DRAK_GRAY   = 0x08;
constexpr BYTE CON_LIGHT_BLUE  = 0x09;
constexpr BYTE CON_LIGHT_GREEN = 0x0A;
constexpr BYTE CON_LIGHT_CYAN  = 0x0B;
constexpr BYTE CON_LIGHT_RED   = 0x0C;
constexpr BYTE CON_PINK        = 0x0D;
constexpr BYTE CON_YELLOW      = 0x0E;
constexpr BYTE CON_WHITE       = 0x0F;

constexpr inline BYTE _CONSOLE_ATTRIBUTE(
        const BYTE foreground, 
        const BYTE background
        ) noexcept {
    return (background << 4) | foreground;
}

#endif
