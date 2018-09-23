#include <Instructions.hpp>

void KernelPortInByte (BYTE portNo) {
    __asm__ __volatile__ (
        "mov %0, %%rdx   \n\t"
        "mov 0, %%rax    \n\t"
        "in %%dx, %%al"
        : :
        "g" (portNo)
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
