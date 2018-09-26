#include <Types.hpp>
#include <Console.hpp>
#include <Keyboard.hpp>
#include <Diagnostics.hpp>


void KernelStop();

void KernelStart() {
    KernelConsolePrint("Entering IA-32e Mode Successful!\n", CON_LIGHT_GREEN);

    KernelDiagMsgPrint("Initializing Keyboard Controller....", KernelActivateKeyboard());


    KernelStop();

}

void KernelStop() {
    while ( true ) ;
}

