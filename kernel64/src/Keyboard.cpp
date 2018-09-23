#include <Types.hpp>
#include <Instructions.hpp>

bool KernelIsKeyOutBufferFull ( void ) {
    return KernelPortInByte( 0x64 ) & 0x01;
}

bool KernelIsKeyInBufferFull  ( void ) {
    return KernelPortInByte( 0x64 ) & 0x02;
}

bool KernelActivateKeyboard   ( void ) {
    KernelPortOutByte( 0x64, 0xAE );

    for ( unsigned i = 0; i < 0xFFFF; ++i ) {
        if ( ! KernelIsKeyInBufferFull() ) break;
    }

    KernelPortOutByte( 0x60, 0xF4 );

    for ( unsigned j = 0; j < 100; ++j ) {
        for ( unsigned i = 0; i < 0xFFFF; ++i ) {
            if ( KernelIsKeyOutBufferFull() ) break; 
        }

        if ( KernelPortInByte( 0x60 ) == 0xFA ) {
            return true;
        }
    }

    return false;
}
