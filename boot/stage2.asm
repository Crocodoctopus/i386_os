global stage2_entry
extern _start

extern init_idt;
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
    call init_idt
    lidt [idt_descriptor]
    
    int3
    mov word [0xb8000], 0x0F36
end:
    jmp end
    
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
