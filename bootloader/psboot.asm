;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Filename : psldr.asm                           ;
; Author : P.Knowledge, 2016-                    ;
; Data since : 20171208 15:43, KST               ;
; Purpose : PS64 16-bit Realmode Bootloader      ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[ORG 0x00]
[BITS 16]
    
SECTION     .text
            jmp 0x07C0:BEGIN

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Environment Values                             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

TOTALSECTORCOUNT: dw 10

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Bootloader Procedure                           ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


BEGIN:      mov ah, 2
            mov bh, 1
            mov dh, 1
            mov dl, 8

            int 10h

            ; initialize data segment register with bootloader begin address
            mov ax, 0x07C0
            mov ds, ax
            mov ax, 0xB800
            mov es, ax

            ; create 64Kilobytes stack
            mov ax, 0x0000
            mov ss, ax
            mov sp, 0xFFFE
            mov bp, 0xFFFE

INITSI:     mov  si, 0
CLEARSCR:   mov  BYTE[es:si], 0

            add  si, 2
 
            cmp  si, 80 * 25 * 2
            jl   CLEARSCR

LOADOSIMG:  mov  ax, 0
            ; Drive #
            mov  dl, 0 
            int  0x13
            jc   DISKERR

            ; PS64 starts from 0x1000
            mov  si, 0x1000
            mov  es, si
            mov  bx, 0x0000

            mov  di, word[TOTALSECTORCOUNT]

READ:       cmp  di, 0
            je   LOAD
            sub  di, 0x1

            ; BIOS service 2, read 1 sector
            mov  ah, 0x02
            mov  al, 0x1

            mov  ch, byte[TRACKNO]
            mov  cl, byte[SECTORNO]
            mov  dh, byte[HEADNO]
            mov  dl, 0x00
            int  0x13
            jc   DISKERR2

            add  si, 0x0020
            mov  es, si

            mov  al, byte[SECTORNO]
            add  al, 0x01
            mov  byte[SECTORNO], al
            cmp  al, 19
            jl   READ

            xor  byte[HEADNO], 0x01
            mov  byte[SECTORNO], 0x01

            cmp  byte[HEADNO], 0x00
            jne  READ

            add  byte[TRACKNO], 0x01
            jmp  READ

            
LOAD:       push 0x00
            push 0x00
            push DONE
            push 0x33
            call PRINTSTR
            add  sp, 7

            ; Start PS64
            jmp 0x1000:0x0000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Functions                                     ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; DISKERR()                        ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

DISKERR:    push 0x0C    
            push DISKERRMSG
            push 1
            push 1
            call PRINTSTR
            jmp  $

DISKERR2:   push 0x0C
            push DISKREADERR
            push 0
            push 0
            call PRINTSTR
            jmp  $

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; PRINTSTR(color, msg, xpos, ypos) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PRINTSTR:   push bp
            mov  bp, sp

            push es
            push si
            push di
            push ax
            push cx
            push dx

            mov  ax, 0xB800
            mov  es, ax

            mov  ax, word[bp + 4]   ; ypos
            mov  si, 160
            mul  si
            mov  di, ax
 
            mov  ax, word[bp + 6]   ; xpos
            mov  si, 2
            mul  si
            add  di, ax
 
            mov  si, word[bp + 8]   ; msg
            mov  al, byte[bp + 10]  ; color            
 
MSGLOOP:    mov  cl, byte[si]
            cmp  cl, 0
            je   CLEAR
 
            cmp  cl, 0x10
            je   LINEFEED
 
            mov  byte[es:di], cl
            mov  byte[es:di+1], al
 
            add  si, 1
            add  di, 2

            jmp  MSGLOOP
 
LINEFEED:   add  si, 1
            add  di, 160
            jmp  MSGLOOP
 
CLEAR:      pop  dx
            pop  cx
            pop  ax
            pop  di
            pop  si
            pop  es
            pop  bp
            ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; TYPESTR(msg)                     ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

TYPESTR:    push bp
            mov  bp, sp

            push es
            push si
            push di
            push ax
            push cx
            push dx

            mov ah, 0x0E

            mov si, DONE
TYPELOOP:   mov cl, byte[si]
            cmp cl, 0
            je ENDTYPE

            mov al, cl
            int 0x10
            add si, 1
            jmp TYPELOOP

ENDTYPE:    pop  dx
            pop  cx
            pop  ax
            pop  di
            pop  si
            pop  es
            pop  bp
            ret

        
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Data                                           ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

DONE:       db 'PSBOOT BOOTLOADER VER1.00, BY 0X00000FF', 0x00
DISKERRMSG: db 'DISK INIT ERROR!', 0
DISKREADERR:db 'DISK READ EEROR!', 0

SECTORNO:   db 0x02
HEADNO:     db 0x00
TRACKNO:    db 0x00

NOTATION:   times 510 - ( $ - $$ ) db 0xFF
            dw 0xAA55
