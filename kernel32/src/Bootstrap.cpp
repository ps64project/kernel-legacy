#include <Types.hpp>
#include <Constants.hpp>
#include <ModeSwitch.hpp>
#include <Bootstrap.hpp>

static const void* VGABUFFER = (const void*) 0xB8000;

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
