[BITS 64]

SECTION .text

extern KernelStart

START:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ss, ax
    mov rsp, 0x6FFF8
    mov rbp, 0x6FFF8

    call KernelStart

    jmp $
