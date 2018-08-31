#ifndef __TYPES_HPP__
#define __TYPES_HPP__

using   BYTE    =   unsigned char;
using   WORD    =   unsigned short;
using   DWORD   =   unsigned int;
using   QWORD   =   unsigned long;
using   BOOL    =   BYTE;

const   BYTE    NULL      =   0;

#pragma pack( push, 1 )

typedef struct kCharacterStruct {
    BYTE Character;
    BYTE Attribute;
} CHARACTER;

#pragma pack( pop )

typedef struct pageTableEntryStruct {
    DWORD AttributeAndLowerBase;
    DWORD UpperBaseAndEXB;
} PML4ENTRY, PDPENTRY, PDENTRY, PTENTRY;


#endif
