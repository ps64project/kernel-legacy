global KernelReadCPUID, KernelSwitch64Bit

SECTION .text


; Read CPUID
; void KernelReadCPUID (DWORD cpuidEax, DWORD* eax, DWORD* ebx, DWORD* ecx, DWORD* edx) 
KernelReadCPUID:
    push ebp
    mov ebp, esp
    push eax
    push ebx
    push ecx
    push edx
    push esi

    mov eax, dword [ ebp + 8 ]
    cpuid

    mov esi, dword [ ebp + 12 ]
    mov dword [ esi ], eax

    mov esi, dword [ ebp + 16 ]
    mov dword [ esi ], ebx

    mov esi, dword [ ebp + 20 ]
    mov dword [ esi ], ecx

    mov esi, dword [ ebp + 24 ]
    mov dword [ esi ], edx

    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    pop ebp
    ret


; Switch 64Bit Mode
; void KernelSwitch64Bit ( void )
KernelSwitch64Bit:
    
    mov eax, cr4
    or eax, 0x20 ; set PAE bit as 1
    mov cr4, eax

    mov eax, 0x100000 ; PML4 Table
    mov cr3, eax ; set PML4 Table Address into CR3 register

    mov ecx, 0xC0000080 ; Address of IA32_EFER MSR Reg.
    rdmsr ; Read IA32_EFER MSR Reg.

    or eax, 0x0100 ; set LME bit as 1
    wrmsr

    
    mov eax, cr0
    or eax, 0xE0000000 ; NW=1, CD=1, PG=1
    xor eax, 0x60000000 ; NW = 0, CD = 0
    mov cr0, eax

    jmp 0x08:0x200000 ; jump into 64bit
    
    jmp $

