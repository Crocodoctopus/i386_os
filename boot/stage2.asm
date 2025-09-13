global stage2_entry
extern init_idt32
extern gdt_descriptor
extern idt_descriptor
extern _start
extern init_pic
extern terminal_clear
extern load_kernel
extern init_page_directory
extern PAGE_DIRECTORY_PHYS
extern kernel_stack

%define BIT(x) (1 << x)

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
    ; set data and stack segment
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    
    ; load the rest of the kernel
    call load_kernel

    ; start basic paging
    call init_page_directory

    mov eax, cr4
    or eax, BIT(4) ; page size extension
    mov cr4, eax

    mov eax, PAGE_DIRECTORY_PHYS
    mov cr3, eax

    mov eax, cr0
    or eax, BIT(31) | BIT(1)
    mov cr0, eax
    
    ; correct the gdt
    lgdt [gdt_descriptor]

    ; move stack to final position
    add esp, kernel_stack + 0x1000

    ; jump to start, never return
    jmp _start

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
