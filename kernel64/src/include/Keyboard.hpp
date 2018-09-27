#ifndef __KEYBOARD_HPP__
#define __KEYBOARD_HPP__

#define KEYBOARD_ACK    0xFA

bool KernelIsKeyOutBufferFull ( void );
bool KernelIsKeyInBufferFull  ( void );
bool KernelActivateKeyboard   ( void );
bool KernelSetKeyboardLED     ( bool capsLock, bool numLock, bool scrollLock );

#endif
