// PS64 32bit Protected Mode Kernel Start

#include <Types.hpp>
#include <Constants.hpp>
#include <Paging.hpp>
#include <ModeSwitch.hpp>
#include <Bootstrap.hpp>

void KernelStart() {
    KernelPrints(0, 0, "PHILOSOPHER'S STONE :: DEV ALPHA, 0.1", CON_MAGENTA);
    KernelPrints(0, 1, "=====================================");
    KernelPrints(0, 2, "32Bit Protected Mode SUCCESS!!", CON_LIGHT_GREEN);

    bool isMemoryEnough = KernelCheckMemorySize();
    KernelDiagMsgPrint(0, 3, "Minimum Memory Requirement Check....", isMemoryEnough);
    if (!isMemoryEnough) {
        KernelPrints(0, 5, "* Memory size check failed, PS64 requires 64MB or larger system memory.", CON_LIGHT_RED);
        KernelPrints(0, 6, "*** System STOP ::  ERROR_INSUFFICIENT_MEMORY", CON_LIGHT_RED);
        KernelStop();
    }

    KernelDiagMsgPrint(0, 4, "IA-32e Kernel Area Initialization...", KernelInit64Area());
    
    KernelInitializePageTables();
    KernelDiagMsgPrint(0, 5, "IA-32e Page Table Initialization....", true);

    KernelPrints(0, 6, "[ Processor Information ]");
    KernelCheckProcessor();

    KernelPrints(0, 10, "Copying IA-32e Kernel Image and Switching...");
    CopyAndSwitchIA32e();
}

