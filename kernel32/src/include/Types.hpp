#ifndef __TYPES_HPP__
#define __TYPES_HPP__

using   BYTE    =   unsigned char;
using   WORD    =   unsigned short;
using   DWORD   =   unsigned int;
using   QWORD   =   unsigned long;
using   BOOL    =   BYTE;

const   BYTE    TRUE    =   1;
const   BYTE    FALSE   =   0;
const   BYTE    NULL    =   0;

#pragma pack( push, 1 )

typedef struct kCharacterStruct {
    BYTE Character;
    BYTE Attribute;
} CHARACTER;

#pragma pack( pop )

typedef struct pageTableEntryStruct {
    BYTE    P           : 1;
    BYTE    RW          : 1;
    BYTE    US          : 1;
    BYTE    PWT         : 1;
    BYTE    PCD         : 1;
    BYTE    A           : 1;
    BYTE    Reserved_1  : 3;
    BYTE    Avail       : 3;
    DWORD   BaseAddress : 28;
    WORD    Reserved_2  : 12 = 0;
    WORD    Avail2      : 11;
    BYTE    EXB         : 1;
} PML4TENTRY, PDPTENTRY, PDENTRY, PTENTRY;

#endif
