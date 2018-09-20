#include <ModeSwitch.hpp>
#include <Types.hpp>


void CopyAndSwitchIA32e () {
    WORD kernel32Size = *((WORD* ) 0x7C05);
    WORD kernelTotalSize = *((WORD* ) 0x7C07);

    DWORD* kernel64Source = ( DWORD* ) ( 0x10000 + ( kernel32Size * 512 ) );
    DWORD* kernel64Destination = (DWORD*) 0x200000;

    for (DWORD i = 0;
               i < (DWORD)( kernelTotalSize - kernel32Size ) * 128;
               ++i) {
        *( kernel64Destination ) = *( kernel64Source );
        *( kernel64Source ) = 0;

        kernel64Destination++;
        kernel64Source++;
    }

    KernelSwitch64Bit();
}

