// PS64 32bit Protected Mode Kernel Start

#include <Types.hpp>
#include <Constants.hpp>
#include <Paging.hpp>
#include <ModeSwitch.hpp>

const void* VGABUFFER    =  (const void*)  0xB8000;
      
DWORD KernelPrints          (const int, const int, const char*, const BYTE = 0x07);
void  KernelDiagMsgPrint    (const int, const int, const char*, const bool);
bool  KernelCheckMemorySize ();
bool  KernelInit64Area      ();
void  KernelCheckProcessor  ();
void  KernelStop            ();

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

DWORD KernelPrints(
        const int    xPos, 
        const int    yPos, 
        const char*  str,
        const BYTE   color 
     ) {
    DWORD      i      = 0;
    CHARACTER* screen = (CHARACTER*) VGABUFFER;
    
    screen += (yPos * 80) + xPos;
    for (i = 0; str[ i ]; ++i ) {
        screen[ i ].Character = str[ i ];
        screen[ i ].Attribute = color;
    }
    
    return i + 1;
}

void KernelDiagMsgPrint (
        const int    xPos,
        const int    yPos,
        const char*  msg,
        const bool   status
    ) {
    auto printedCount = KernelPrints(xPos, yPos, msg);
    KernelPrints(xPos + printedCount, yPos, "[");
    
    if (status) {
        KernelPrints(xPos + printedCount + 1, yPos, " OKAY ", CON_LIGHT_GREEN);
    } else {
        KernelPrints(xPos + printedCount + 1, yPos, "FAILED", CON_LIGHT_RED);
    }

    KernelPrints(xPos + printedCount + 7, yPos, "]");
}

bool KernelCheckMemorySize() {
    DWORD*  currentAddress = ( DWORD * ) 0x100000;

    while ( ( DWORD ) currentAddress < 0x4000000 ) {
        *currentAddress = 0xABCDEFAB;

        if (*currentAddress ^ 0xABCDEFAB) {
            return false;
        }

        currentAddress += 0x100000 >> 2;
    }

    return true;
}

bool KernelInit64Area() {
    DWORD*  currentAddress = ( DWORD* ) 0x100000;

    while ( ( DWORD ) currentAddress < 0x600000 ) {
        *currentAddress = 0x00;

        if ( *currentAddress ) {
            return false;    
        }

        ++currentAddress;
    }
    
    return true;
}

void KernelCheckProcessor() {
    char  cpuIDStr[13] = { 0, };
    DWORD cpuIDEAX     = 0;
    DWORD cpuIDEBX     = 0;
    DWORD cpuIDECX     = 0;
    DWORD cpuIDEDX     = 0;

    KernelReadCPUID(CPUID_READ, &cpuIDEAX,
            (DWORD*)cpuIDStr, (DWORD*)(cpuIDStr + 8), (DWORD*)(cpuIDStr + 4));

    KernelPrints(0, 7, "* Vendor: ");
    KernelPrints(10, 7, cpuIDStr);

    KernelReadCPUID(CPUID_READ_EXTEND, &cpuIDEAX, &cpuIDEBX, &cpuIDECX, &cpuIDEDX);
    
    bool compat = cpuIDEDX & (1 << 29);
    KernelDiagMsgPrint(0, 8, "* IA-32e Compatibility....", compat);
    if (!compat) {
        KernelPrints(0, 9, "*** CPU Compatibility Check Failure, SYSTEM HALT!", CON_LIGHT_RED);
        KernelStop();
    }
}

void KernelStop() {
    while (true) ;
}
