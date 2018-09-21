#include <Types.hpp>
#include <Console.hpp>

void KernelStop();

void KernelDebug( int x, int y, const char* str) {
    auto scr = (volatile WORD*) CON_GRAPHIC_MEM;

    scr += (y * 80) + x;

    for ( unsigned i = 0; str[i]; ++i ) {
        scr[i] = CON_LIGHT_GREEN << 8 | str[i];
    }
}

void KernelStart() {
    KernelConsolePrint("Hello 64Bit!");
    KernelStop();

}

void KernelStop() {
    while ( true ) ;
}

