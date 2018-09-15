#ifndef __INSTRUCTIONS_HPP__
#define __INSTRUCTIONS_HPP__

inline void __x86_out_b(const WORD port, const BYTE val) {
/*
    __asm__ __volatile__ (
        "mov %1, %%al \n\t"
        "mov %0, %%dx \n\t"
        "out %%dx, %%ax" : :
        "n" (port), "n" (val)
    );
*/
}


#endif
