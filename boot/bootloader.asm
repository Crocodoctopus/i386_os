%define ENDL 0x0D, 0x0A

extern _start 

bits 16
section .boot.text
start16:
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 7C00h

    ; start 32 bit protected mode
    cli
    lgdt [gdt_desc]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp 08h:start32
    
bits 32
start32:
    mov word [0xB8000], 0x0F41
    ;call _start
    jmp $

gdt_start:
    dd 0
    dd 0

    ; 32 bit code segment
    dw 0xFFFF
    dw 0
    db 0
    db 0b10011010
    db 0b11001111
    db 0

    ; 32 bit data segment
    dw 0xFFFF
    dw 0
    db 0
    db 0b10010010
    db 0b11001111
    db 0

gdt_desc:
    dw gdt_desc - gdt_start - 1
    dd gdt_start

data:
    times 510-($-$$) db 0
    dw 0xAA55
