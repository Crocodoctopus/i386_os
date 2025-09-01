%define ENDL 0x0D, 0x0A

extern _start 
extern KERNEL_SRC ; as sector
extern KERNEL_DST ; as ptr
extern KERNEL_SIZE ; in sectors

bits 16
section .boot.text
start16:
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 7C00h

    ; load the rest of the kernel into memory    
    mov ah, 2 ; read operation
    mov al, KERNEL_SIZE ; sectors to read
    mov ch, 0
    mov cl, KERNEL_SRC
    mov dh, 0
    ;mov dl, X ; 
    mov bx, KERNEL_DST
    int 0x13    

    ; start 32 bit protected mode
    cli
    lgdt [gdt_desc]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp 08h:start32
    
bits 32
start32:
    call _start
end:
    hlt
    jmp end

section .boot.data   
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
        
section .boot.constant
    dw 0xAA55
