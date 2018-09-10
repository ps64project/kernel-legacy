#ifndef __INSTRUCTIONS_HPP__
#define __INSTRUCTIONS_HPP__

template <typename T>
inline void __x86_out(const WORD port, const T val) {
    asm(
        "out %0, %1" : :
        "r" (port), "r" (val)
    );
}


#endif
