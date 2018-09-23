#include <Instructions.hpp>

BYTE KernelPortInByte (BYTE portNo) {
    BYTE result = 0x00;
    
    __asm__ __volatile__ (
        "mov %0, %%rdx   \n\t"
        "mov 0, %%rax    \n\t"
        "in %%dx, %%al"
        : "=g" (result) 
        : "g" (portNo)
    );
}

void KernelPortOutByte (BYTE portNo, BYTE data) {
    __asm__ __volatile__ (
        "mov %0, %%rdx  \n\t"
        "mov %1, %%rax  \n\t"
        "out %%al, %%dx \n\t"
        : :
        "g" (portNo), "g" (data)
    );
}
