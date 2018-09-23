#include <Types.hpp>
#include <Instructions.hpp>
#include <Console.hpp>

static DWORD __pos = 960;

void KernelConsoleClear() {
    auto graphic = (WORD*)CON_GRAPHIC_MEM;

    CONSOLE_TRAVERSE {
        *(graphic) = 0; 
        ++graphic;
    }

    __pos = 0;
}

void KernelConsolePrint(const char* str, const BYTE attribute) {
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

   KernelPortOutByte(0x3D4, 0x0F);
   KernelPortOutByte(0x3D5, __pos & 0xFF);
   KernelPortOutByte(0x3D4, 0x0E);
   KernelPortOutByte(0x3D5, (__pos >> 8 & 0xFF));
}

