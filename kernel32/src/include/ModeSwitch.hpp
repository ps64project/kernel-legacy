#ifndef __MODESWITCH_HPP__
#define __MODESWITCH_HPP__

const DWORD CPUID_READ        = 0x00000000;
const DWORD CPUID_READ_EXTEND = 0x80000001; 

extern "C"
void KernelReadCPUID (DWORD cpuidEax, DWORD* eax, DWORD* ebx, DWORD* ecx, DWORD* edx); 

void KernelSwitch64Bit( void );

#endif
