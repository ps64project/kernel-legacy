#ifndef __SYSCALL_HPP__
#define __SYSCALL_HPP__

inline void outb(const WORD port, const BYTE val) {
    asm ( "outb %0, %1" );
}

#endif
