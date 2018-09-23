#include <Types.hpp>
#include <Console.hpp>
#include <Keyboard.hpp>

void KernelStop();

void KernelStart() {
    KernelConsolePrint("Entering IA-32e Mode Successful!\n", CON_LIGHT_GREEN);
    KernelConsolePrint("Initializing Keyboard Controller....");
    if ( KernelActivateKeyboard() ) {
        KernelConsolePrint("FAILED\n", CON_LIGHT_RED);
        KernelConsolePrint("** Failed to Initializing Keryboard, System STOP", CON_LIGHT_RED);
        KernelStop();
    }
    KernelConsolePrint("SUCCESS\n", CON_LIGHT_GREEN);

    // TODO : Start Keyboard Controller 


    KernelStop();

}

void KernelStop() {
    while ( true ) ;
}

