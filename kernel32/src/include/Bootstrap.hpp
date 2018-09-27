#ifndef __BOOTSTRAP_HPP__
#define __BOOTSTRAP_HPP__

DWORD KernelPrints          (const int, const int, const char*, const BYTE = 0x07);
void  KernelDiagMsgPrint    (const int, const int, const char*, const bool);
bool  KernelCheckMemorySize ();
bool  KernelInit64Area      ();
void  KernelCheckProcessor  ();
void  KernelStop            ();

#endif
