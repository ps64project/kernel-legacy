#ifndef __PS2_KEYBOARD_HPP__
#define __PS2_KEYBOARD_HPP__

/*******************************************************************
 * PS/2 interface keyboard header
 * this file include keyboard commands and functions
 *******************************************************************/

//special bytes
#define PS2KEY_ECHO     0xEE
#define PS2KEY_ACK      0xFA
#define PS2KEY_STP      0xAA  // SelfTestPassed(after reset or power up)
#define PS2KEY_STF1     0xFC  // SelfTestFailed
#define PS2KEY_STF2     0xFD  // SelfTestFailed
#define PS2KEY_RESEND   0xFE
#define PS2KEY_ERR1     0x00  // also 0xFF key detection error or buffer overrun

//commands
#define PS2KEY_SETLED   0xED
#define PS2KEY_SCANCODE 0xF0
#define PS2KEY_ID       0xF2
#define PS2KEY_DELAY    0xF3  // Set yypematic rate and delay
#define PS2KEY_EnSCAN   0xF4  // Enable scan code
#define PS2KEY_DisSCAN  0xF5
#define PS2KEY_SETDEF   0xF6  // Set default parameters
#define PS2KEY_RESET    0xFF

bool KernelIsKeyOutBufferFull ( void );
bool KernelIsKeyInBufferFull  ( void );
bool KernelActivateKeyboard   ( void );
bool KernelSetKeyboardLED     ( bool capsLock, bool numLock, bool scrollLock );

#endif
