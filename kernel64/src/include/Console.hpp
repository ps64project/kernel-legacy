#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

#define   CON_GRAPHIC_MEM ( CHARACTER* )0xB8000

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

#define   VGA_HEIGHT      25
#define   VGA_WIDTH       80
#define   VGA_ADDR_MAX    2000

#define   CONSOLE_TRAVERSE                 for(WORD i = 0; i < VGA_ADDR_MAX; ++i)
#define   CONSOLE_TRAVERSE_ALL_QWORD       for(WORD i = 0; i < 500; ++i)

constexpr inline BYTE _CONSOLE_ATTRIBUTE(
        const BYTE foreground, 
        const BYTE background
        ) noexcept {
    return (background << 4) | foreground;
}

constexpr inline WORD _CONSOLE_CHAR(
        const BYTE character,
        const BYTE attribute
        ) noexcept {
    return (attribute << 8) | character;
}

static DWORD __pos = 960;

void KernelConsoleClear() {
    auto graphic = (WORD*)CON_GRAPHIC_MEM;

    CONSOLE_TRAVERSE {
        *(graphic) = 0; 
        ++graphic;
    }

    __pos = 0;
}

void KernelConsolePrint(const char* str, const BYTE attribute = CON_LIGHT_GRAY) {
    auto graphic = ( WORD* ) (CON_GRAPHIC_MEM + __pos); 
    
    for (unsigned i = 0; str[i]; ++i) {
        if (str[i] == '\n') {
            __pos += 80 - (__pos % 80);
            continue;
        }
        
        if (__pos > VGA_ADDR_MAX) {
            __pos = 0;
        }

        *graphic = _CONSOLE_CHAR(str[i], attribute);
        
        ++graphic;
        ++__pos;
    }
}

#endif

