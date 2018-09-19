#include <Types.hpp>
#include <Instructions.hpp>
#include <Console.hpp>

void KernelStop();

void KernelStart() {
    KernelConsoleClear();
    KernelConsolePrint("Hello PS64!");

    KernelStop();

}

void KernelStop() {
    while ( true ) ;
}

