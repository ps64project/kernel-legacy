// PS64 Kernel Start

#include <Types.hpp>
#include <Constants.hpp>

const void* VGABUFFER    =  (const void*)  0xB8000;

void KernelPrints          (const int, const int, const char*, const BYTE = 0x07);
bool KernelCheckMemorySize ();
bool KernelInit64Area      ();

void KernelStart() {
    KernelPrints(0, 0, "PHILOSOPHER'S STONE :: DEV ALPHA, 0.1", CON_MAGENTA);
    KernelPrints(0, 1, "=====================================");

    KernelPrints(0, 2, "32Bit Protected Mode SUCCESS!!", CON_LIGHT_GREEN);

    KernelPrints(0, 3, "Minimum Memory Requirement Check.... [      ]");
    if (!KernelCheckMemorySize()) {
        KernelPrints(38, 3, "FAILED", CON_LIGHT_RED);
        KernelPrints(0, 4, "MEMORY FAILURE, System Halt!");

        while (true) ;
    }
    KernelPrints(38, 3, " OKAY ", CON_LIGHT_GREEN);

    KernelPrints(0, 4, "IA-32e Kernel Area Initialization... [      ]");
    if (!KernelInit64Area()) {
        KernelPrints(38, 4, "FAILED", CON_LIGHT_RED);
        while (true) ;
    }

    KernelPrints(38, 4, " OKAY ", CON_LIGHT_GREEN);

    KernelPrints(0, 5, "IA-32e Page Table Initialization.... [      ]");
    KernelPrints(38, 5, "FAILED", CON_LIGHT_RED);

    KernelPrints(0, 8, "SYSTEM FAILURE", _CONSOLE_ATTRIBUTE(CON_WHITE, CON_LIGHT_RED));

    while (true) ;
}

void KernelPrints(
        const int xPos, 
        const int yPos, 
        const char* str,
        const BYTE color 
     ) {
   CHARACTER* screen = (CHARACTER*) VGABUFFER;

   screen += (yPos * 80) + xPos;
   for (int i = 0; str[ i ]; ++i ) {
       screen[ i ].Character = str[ i ];
       screen[ i ].Attribute = color;
   }
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

