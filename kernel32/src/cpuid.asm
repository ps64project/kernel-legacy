global KernelReadCPUID


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

