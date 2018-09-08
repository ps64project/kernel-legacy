#include <Types.hpp>
#include <Paging.hpp>

void KernelInitializePageTables ( void ) {
    PML4TENTRY* PML4TEntry;
    PDPTENTRY*  PDPTEntry;
    PDENTRY*    PDEntry;
    DWORD       MappingAddress;

    PML4TEntry = ( PML4TENTRY* ) 0x100000;
    KernelSetPageEntryData( *PML4TEntry , 0x00, 0x101000, PAGE_FLAGS_DEFAULT, 0 );
    for ( unsigned i = 1; i < PAGE_MAXENTRYCOUNT ; ++i ) {
        KernelSetPageEntryData( PML4TEntry[i], 0, 0, 0, 0 );
    }

    PDPTEntry = ( PDPTENTRY* ) 0x101000;
    for ( unsigned i = 0; i < 64; ++i ) {
        KernelSetPageEntryData( PDPTEntry[i], 0, 0, 0, 0);
    }

    PDEntry = ( PDENTRY* ) 0x102000;
    MappingAddress = 0;
    for ( unsigned i = 0; i < ( PAGE_MAXENTRYCOUNT << 6 ); ++i ) {
        KernelSetPageEntryData( PDEntry[i], ( i * (PAGE_DEFAULTSIZE >> 20) ) >> 12, MappingAddress, 
                PAGE_FLAGS_DEFAULT | PAGE_FLAGS_PS, 0 );
        MappingAddress += PAGE_DEFAULTSIZE;
    }
}

void KernelSetPageEntryData    ( 
        PTENTRY& entry, 
        DWORD    upperAddress, 
        DWORD    lowerAddress, 
        DWORD    lowerFlags, 
        DWORD    upperFlags
    ) { 
    entry.attributeAndLowerBase = lowerAddress | lowerFlags;
    entry.upperBaseAndEXB = upperAddress | upperFlags;
}
