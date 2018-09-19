#include <ModeSwitch.hpp>
#include <Types.hpp>

void CopyKernel64 () {
    WORD kernel32Size = *((WORD* ) 0x7C05);
    WORD kernelTotalSize = *((WORD* ) 0x7C07);

    BYTE* kernel64Start = ( BYTE* ) ( 0x10000 + kernel32Size * 512 );

    for (DWORD kernelOffset = 0;
               kernelOffset < (DWORD)( kernelTotalSize - kernel32Size ) * 512;
               ++kernelOffset) {
        *( ( BYTE* ) ( 0x200000 + kernelOffset ) ) = *(kernel64Start + kernelOffset);
        *( kernel64Start + kernelOffset ) = 0;
    }
}

