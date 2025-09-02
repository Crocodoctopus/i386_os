global stage2_entry
extern _start

extern init_idt32;
extern idt;
extern idt_descriptor;

bits 16
section .stage2.text
stage2_entry:
    mov sp, 0x8000
    
    ; start 32 bit protected mode
    lgdt [gdt_desc]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp 08h:start32

bits 32
start32:
    ; initialize and set idt
    call init_idt32
    lidt [idt_descriptor]
    
    int3
    mov word [0xb8000], 0x0F36
end:
    hlt
    jmp end

; create stubs for each interrupt
%macro isr32_err_stub 1
global isr32_%1
isr32_%1:
    push %1
    jmp isr32_common
%endmacro

%macro isr32_noerr_stub 1
global isr32_%1
isr32_%1:
    push 0
    push %1
    jmp isr32_common
%endmacro

extern interrupt_handler
isr32_noerr_stub 0
isr32_noerr_stub 1
isr32_noerr_stub 2
isr32_noerr_stub 3
isr32_noerr_stub 4
isr32_noerr_stub 5
isr32_noerr_stub 6
isr32_noerr_stub 7
isr32_err_stub   8
isr32_noerr_stub 9
isr32_err_stub   10
isr32_err_stub   11
isr32_err_stub   12
isr32_err_stub   13
isr32_err_stub   14
isr32_noerr_stub 15
isr32_noerr_stub 16
isr32_err_stub   17
isr32_noerr_stub 18
isr32_noerr_stub 19
isr32_noerr_stub 20
isr32_noerr_stub 21
isr32_noerr_stub 22
isr32_noerr_stub 23
isr32_noerr_stub 24
isr32_noerr_stub 25
isr32_noerr_stub 26
isr32_noerr_stub 27
isr32_noerr_stub 28
isr32_noerr_stub 29
isr32_err_stub   30
isr32_noerr_stub 31
isr32_common:
    pusha

    ; push single segment register
    xor eax, eax
    mov ax, ds
    push eax

    mov ax, 0x8
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    push esp
    call interrupt_handler
    add esp, 4

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8
    iret

    
section .stage2.data
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
