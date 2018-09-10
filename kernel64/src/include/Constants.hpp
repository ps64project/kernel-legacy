#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__


#define   CON_BLACK       0x00
#define   CON_BLUE        0x01
#define   CON_GREEN       0x02
#define   CON_CYAN        0x03
#define   CON_RED         0x04
#define   CON_MAGENTA     0x05
#define   CON_BROWN       0x06
#define   CON_LIGHT_GRAY  0x07
#define   CON_DRAK_GRAY   0x08
#define   CON_LIGHT_BLUE  0x09
#define   CON_LIGHT_GREEN 0x0A
#define   CON_LIGHT_CYAN  0x0B
#define   CON_LIGHT_RED   0x0C
#define   CON_PINK        0x0D
#define   CON_YELLOW      0x0E
#define   CON_WHITE       0x0F

constexpr inline BYTE _CONSOLE_ATTRIBUTE(
        const BYTE foreground, 
        const BYTE background
        ) noexcept {
    return (background << 4) | foreground;
}

#endif
