#include <Types.hpp>
#include <Console.hpp>

void KernelStop();

void KernelDebug( int x, int y, const char* str) {
    CHARACTER* scr = ( CHARACTER* ) CON_GRAPHIC_MEM;

    scr += (y * 80) + x;

    for ( unsigned i = 0; str[i]; ++i ) {
        scr[i].Character = str[i];
        scr[i].Attribute = CON_LIGHT_GREEN;
    }
}

void KernelStart() {
    KernelConsoleClear();
    KernelStop();

}

void KernelStop() {
    while ( true ) ;
}

