global stage2_entry
extern init_idt32;
extern gdt_descriptor;
extern idt_descriptor;
extern _start
extern init_pic;
extern terminal_clear;
extern load_kernel;

bits 16
section .text
stage2_entry:
    ; start 32 bit protected mode
    lgdt [gdt_descriptor]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp 08h:start32

bits 32
start32:
    ;
    call terminal_clear

    call load_kernel

    ; initialize and set idt
    call init_idt32
    lidt [idt_descriptor]

    ; initialize pic
    call init_pic;

    ; enable interrupts
    sti

    ;
    call _start
end:
    hlt
    jmp end
