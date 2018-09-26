#include <Types.hpp>
#include <Console.hpp>
#include <Diagnostics.hpp>


void KernelDiagMsgPrint ( 
        const char* msg, 
        const bool status 
    )
{
    KernelConsolePrint(msg);
    
    KernelConsolePrint( " [");
    
    if (status) {
        KernelConsolePrint(" OKAY ", CON_LIGHT_GREEN);
    } else {
        KernelConsolePrint("FAILED", CON_LIGHT_RED); 
    }

    KernelConsolePrint("]\n");
}

