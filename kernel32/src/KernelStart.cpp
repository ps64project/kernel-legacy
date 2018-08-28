// PS64 Kernel Start

#include <Types.hpp>

const void* VGABUFFER    =  (const void*)  0xB8000;

void KernelPrints          (const int, const int, const char*);
bool KernelCheckMemorySize ();
bool KernelInit64Area      ();

void KernelStart() {
    KernelPrints(0, 2, "PS64 Kernel Started...");

    KernelPrints(0, 3, "Minimum Memory Requirement Check...  [      ]");
    if (!KernelCheckMemorySize()) {
        KernelPrints(38, 3, "FAILED");
        KernelPrints(0, 4, "MEMORY FAILURE, System Halt!");

        while (true) ;
    }
    KernelPrints(39, 3, "OKAY!");

    KernelPrints(0, 4, "IA-32e Kernel Area Initialization... [      ]");
    if (!KernelInit64Area()) {
        KernelPrints(38, 4, "FAILED");
        while (true) ;
    }

    KernelPrints(39, 4, "OKAY!");

    while (true) ;
}

void KernelPrints(
        const int xPos, 
        const int yPos, 
        const char* str
     ) {
   CHARACTER* screen = (CHARACTER*) VGABUFFER;

   screen += (yPos * 80) + xPos;
   for (int i = 0; str[ i ]; ++i )
       screen[ i ].Character = str[ i ];
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

