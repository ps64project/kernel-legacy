#include <Types.hpp>
#include <Instructions.hpp>
#include <Keyboard.hpp>

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

        if ( KernelPortInByte( 0x60 ) == KEYBOARD_ACK ) {
            return true;
        }
    }

    return false;
}

bool KernelSetKeyboardLED     ( 
        bool capsLock, 
        bool numLock, 
        bool scrollLock 
    ) {
    unsigned i, j;

    for ( i = 0; i < 0xFFFF; ++i ) {
        if ( ! KernelIsKeyInBufferFull() ) break;
    }

    KernelPortOutByte( 0x60, 0xED );
    for ( i = 0; i < 0xFFFF; ++i ) {
        if ( ! KernelIsKeyOutBufferFull() ) break;
    }

    for ( j = 0; j < 100; ++j ) {
        for ( i = 0; i < 0xFFFF; ++i ) {
            if ( KernelIsKeyOutBufferFull() ) break;
        }

        if ( KernelPortInByte( 0x60 ) == KEYBOARD_ACK ) break;
    }

    if ( j >= 100 ) return false;

    KernelPortOutByte( 0x60, (capsLock << 2) | (numLock << 1) | scrollLock );
    for ( i = 0; i < 0xFFFF; ++i ) {
        if ( ! KernelIsKeyInBufferFull() ) break;
    }

    for ( j = 0; j < 100; ++j ) {
        for ( i = 0; i < 0xFFFF; ++i ) {
            if ( KernelIsKeyOutBufferFull() ) break;
        }

        if ( KernelPortInByte( 0x60 ) == KEYBOARD_ACK ) break;
    }

    if ( j >= 100 ) return false;

    return true;
}
