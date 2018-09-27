#include <Instructions.hpp>

BYTE KernelPortInByte (QWORD portNo) {
    BYTE result = 0x00;
    
    __asm__ __volatile__ (
        "movq %1, %%rdx   \n\t"
        "movq $0, %%rax    \n\t"
        "inb %%dx, %%al  \n\t"
        "movb %%al, %0"
        : "=g" (result) 
        : "g" (portNo)
    );

    return result;
}

void KernelPortOutByte (QWORD portNo, QWORD data) {
    __asm__ __volatile__ (
        "movq %0, %%rdx  \n\t"
        "movq %1, %%rax  \n\t"
        "outb %%al, %%dx \n\t"
        : :
        "g" (portNo), "g" (data)
    );
}
