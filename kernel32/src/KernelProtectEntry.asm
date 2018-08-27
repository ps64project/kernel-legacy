;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Filename : kernelEntry.asm                     ;
; Author : P.Knowledge, 2016-                    ;
; Data since : 20180823 16:28, KST               ;
; Purpose : PS64 32-bit Protection Mode Entry    ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[ORG 0x00]
[BITS 16]

SECTION .text

START:
    mov ax, 0x1000       ; set Entry Point as 0x10000

    mov ds, ax
    mov es, ax

    cli                  ; Prevent interrupt
    lgdt [GDTR]          ; Load GDT

    mov  eax, 0x4000003B ; PG=0, CD=1, NW=0, AM=0, WP=0, NE=1, ET=1, TS=1, EM=0, MP=1, PE=1
    mov  cr0, eax        ; SET CR0, Enable Protection Mode

    jmp dword 0x08: ( PROTECTEDMODE - $$ + 0x10000 )
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; Disable Paging, Disable Cache, Internal FPU, Disable Align Check
    ; Enable 32-bit Protected Mode
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
[BITS 32]

PROTECTEDMODE:
    ; set Data Segment address
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Create stack, 64KB Size, 0x0000-0xFFFF
    mov ss, ax
    mov esp, 0xFFFE
    mov ebp, 0xFFFE

    ; Complete Protection Mode, Load Kernel

    jmp dword 0x08: 0x10200

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Functions                                      ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PRINTMESSAGE:
    push ebp
    mov ebp, esp
    push esi
    push edi
    push eax
    push ecx
    push edx

    mov eax, dword [ ebp + 12 ]
    mov esi, 160
    mul esi
    mov edi, eax

    mov eax, dword [ ebp + 8 ]
    mov esi, 2
    mul esi
    add esi, eax

    mov esi, dword [ ebp + 16 ]

.MESSAGELOOP:
    mov cl, byte [ esi ]

    cmp cl, 0
    je .MESSAGEEND

    mov byte [ edi + 0xB8000 ], cl

    add esi, 1
    add edi, 2
    jmp .MESSAGELOOP

.MESSAGEEND:
    pop edx
    pop ecx
    pop eax
    pop edi
    pop esi
    pop ebp
    ret



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Data                                           ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

align 8, db 0
dw    0x0000

GDTR:
    dw  GDTEND - GDT - 1
    dd ( GDT - $$ + 0x10000 )

GDT:
    NULLDescriptor:
        dw 0x0000
        dw 0x0000
        db 0x00
        
        db 0x00
        db 0x00
        db 0x00
        
    CODESEGMENT:
        dw  0xFFFF ; Segment Size Limit
        dw  0x0000 ; Base
        db  0x00   ; Base
    
        ; <High 4 Bits>
        ; P(Present) indicates such segment is valid or not, 1 is valid, 0 is invalid.
        ; DPL(Descriptor Privilege Level) is level that is required to access this descriptor.
        ; ranges 0 to 3, Highest to Lowest. 
        ;
        ; <Low 4 Bits>
        ; Data Segment => 0x00 ~ 0x07,
        ; Code Segment => 0x08 ~ 0x0F
        db  0x9A  ; P=1, DPL=0, Code Segment (Executable/Read)
    
        ; G(Granularity) is multiplied with segment size field.
        ; when G is set to 1, 4KB multipled to segment size so that use memory to 4GB.
        ; D(Data Operation Size) indicates this segment is for 32bit or 16bit.
        ; 1 means 32bit, 0 means 16bit.
        ; L is used in IA-32e Mode, indicates this segment is for 64bit or 32bit.
        ; 1 means 64bit, 0 means 32bit.
        db  0xCF  ; G=1, D=1, L=0, Limit [19:16]
        db  0x00  ; Base

    DATASEGMENT:
        dw  0xFFFF
        dw  0x0000
        db  0x00

        db  0x92  ; P=1, DPL=0, Data Segment (Read/Write)
        db  0xCF  ; G=1, D=1, L=0, Limit [19:16]
        db  0x00

GDTEND:

LOADOK: db 'Kernel Load OKAY', 0x00

times   512 - ($ - $$)  db 0x00


