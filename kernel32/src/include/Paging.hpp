#ifndef __PAGING_HPP__
#define __PAGING_HPP__

#define PAGE_FLAGS_P            0b0000000001
#define PAGE_FLAGS_RW           0b0000000010
#define PAGE_FLAGS_US           0b0000000100
#define PAGE_FLAGS_PWT          0b0000001000
#define PAGE_FLAGS_PCD          0b0000010000
#define PAGE_FLAGS_A            0b0000100000
#define PAGE_FLAGS_D            0b0001000000
#define PAGE_FLAGS_PS           0b0010000000
#define PAGE_FLAGS_G            0b0100000000
#define PAGE_FLAGS_PAT          0b1000000000
#define PAGE_FLAGS_EXB          0x80000000       // 63th bit
#define PAGE_FLAGS_DEFAULT      PAGE_FLAGS_P | PAGE_FLAGS_RW

#define PAGE_TABLESIZE      0x1000
#define PAGE_MAXENTRYCOUNT  512
#define PAGE_DEFAULTSIZE    0x200000

#pragma pack( push, 1 )

typedef struct pageTableEntryStruct {
    DWORD attributeAndLowerBase;
    DWORD upperBaseAndEXB;
} PML4TENTRY, PDPTENTRY, PDENTRY, PTENTRY;

#pragma pack( pop )

void KernelInitializePageTables ( void );
void KernelSetPageEntryData     ( PTENTRY& ptEntry, DWORD upperAddress, DWORD lowerAddress, DWORD lowerFlags, DWORD upperFlags);

#endif
