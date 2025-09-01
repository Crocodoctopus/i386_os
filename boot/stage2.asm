global stage2_entry
extern _start

bits 16
section .stage2.text
stage2_entry:
    ; load idt
    lidt [idt_desc]
    
    ; start 32 bit protected mode
    lgdt [gdt_desc]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp 08h:start32

bits 32
start32:
    ;sti
    mov eax, 0
    idiv eax
    ;mov word [0xb8000], 0x0F34
    ;call _start
end:
    hlt
    jmp end

idt_0:
    mov word [0xb8000], 0x0F34
    jmp $
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

idt_start:
    dw idt_0
    dw 0x0008
    db 0x00 ; reserved
    db 0x8E; flags
    dw 0x0000
        
idt_desc:
    dw idt_desc - idt_start - 1
    dd idt_start
