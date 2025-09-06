global stage2_entry
extern init_idt32
extern gdt_descriptor
extern idt_descriptor
extern _start
extern init_pic
extern terminal_clear
extern load_kernel

bits 16
section .text
stage2_entry:
    ; start 32 bit protected mode
    lgdt [tmp_gdt_descriptor]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp 08h:start32

bits 32
start32:
    ; load the rest of the kernel
    call load_kernel

    ; correct the gdt
    lgdt [gdt_descriptor]

    ; start basic paging so we can jump to kernel

    ; jump to start, never return

    ;;; Everything beyond here should probably be in kernel

    ; clear the terminal
    call terminal_clear

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

tmp_gdt:
    dd 0
    dd 0
    
    dw 0xFFFF
    dw 0
    db 0
    db 0b10011010
    db 0b11001111
    db 0

    dw 0xFFFF
    dw 0
    db 0
    db 0b10010010
    db 0b11001111
    db 0

tmp_gdt_descriptor:
    dw tmp_gdt_descriptor - tmp_gdt - 1
    dd tmp_gdt
