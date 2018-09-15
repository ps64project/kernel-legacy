#include <Types.hpp>
#include <Instructions.hpp>
#include <Console.hpp>

void KernelStop();

void KernelStart() {
    KernelConsolePrint("Hello There! We did it!");
    KernelStop();

}

void KernelStop() {
    while ( true ) ;
}

