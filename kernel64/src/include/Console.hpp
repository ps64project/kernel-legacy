#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

#define   CON_GRAPHIC_MEM 0xB8000

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
#define   VGA_ADDR_MAX    4000

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
    return character << 8 | attribute;
}

static CHARACTER KernelGraphicBuffer[80][25];

static void KernelConsoleApplyBuffer() {
    auto graphic = (QWORD *) CON_GRAPHIC_MEM,
         buffer  = (QWORD *) KernelGraphicBuffer;

    CONSOLE_TRAVERSE_ALL_QWORD {
        *( graphic + i ) = *( buffer + i );
    }
}

void KernelConsoleClear() {
    CONSOLE_TRAVERSE_ALL_QWORD {
        *( (QWORD*) (KernelGraphicBuffer + 1) ) = 0;
    }

    KernelConsoleApplyBuffer();
}

void KernelConsoleScroll () {
    for (unsigned i = 0; i < 480; ++i) {
        *( (QWORD*) (KernelGraphicBuffer + i) ) = *( (QWORD*) (KernelGraphicBuffer + 20 + i) );
    }

    for (unsigned i = 480; i < 500; ++i) {
        *( (QWORD*) (KernelGraphicBuffer + i) ) = 0;
    }
}

void KernelConsolePrint (const char* str, const BYTE attribute = CON_LIGHT_GRAY) {
    static BYTE ln  = 0, 
                col = 0;

    unsigned pos = ln * VGA_WIDTH + col;

    for (unsigned i = pos; str[i - pos]; ++i) {
        if (ln >= VGA_HEIGHT || pos > VGA_ADDR_MAX) {
            KernelConsoleScroll();
            ln = VGA_HEIGHT;
        }

        *((WORD *) (KernelGraphicBuffer[ln] + col)) = _CONSOLE_CHAR( str[ i-pos ], attribute);
        ++col;

        if (col >= VGA_WIDTH) {
            ln++;
            col = 0;
        }
    }

    KernelConsoleApplyBuffer();

    //__x86_out_b(0x3D4, 0x0F);
    //__x86_out_b(0x3D5, (BYTE) (pos & 0xFF));
    //__x86_out_b(0x3D4, 0x0E);
    //__x86_out_b(0x3D5, (BYTE) ((pos >> 8) & 0xFF));
}

#endif

