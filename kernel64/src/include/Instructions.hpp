#ifndef __INSTRUCTIONS_HPP__
#define __INSTRUCTIONS_HPP__

#include <Types.hpp>

BYTE KernelPortInByte(QWORD portNo);
void KernelPortOutByte(QWORD portNo, QWORD data);

#endif
