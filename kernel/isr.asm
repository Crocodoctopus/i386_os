; Generate code stubs for all interrupts
; 
global isr32_stub_address_table
extern interrupt_handler

section .text
%macro isr32_err_stub 1
isr32_%+%1:
    push %1
    jmp isr32_common
%endmacro

%macro isr32_noerr_stub 1
isr32_%+%1:
    push 42
    push %1
    jmp isr32_common
%endmacro

; 32 reserved internal isr
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

; remaining 224 external isr
%assign i 32
%rep 244
isr32_noerr_stub i
%assign i i+1
%endrep

isr32_common:
    push esp
    call interrupt_handler
    add esp, 12
    iret
    
; generate lookup table to for all isr
ALIGN 4
isr32_stub_address_table:
%assign i 0
%rep 256
    dd isr32_%+i
%assign i i+1
%endrep
