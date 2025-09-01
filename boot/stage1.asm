extern STAGE2_SRC ; as sector
extern STAGE2_DST ; as ptr
extern STAGE2_SIZE ; in sectors
extern stage2_entry

bits 16
section .stage1.text
stage1_entry:
    cli
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 7C00h

    ; load the rest of the kernel into memory    
    mov ah, 2 ; read operation
    mov al, STAGE2_SIZE ; sectors to read
    mov ch, 0
    mov cl, STAGE2_SRC
    mov dh, 0
    ;mov dl, X ; 
    mov bx, STAGE2_DST
    int 0x13

    ; jump to stage 2
    jmp stage2_entry

    ; jump to "stage2"

    ; set idt table
    ;lidt [idt_desc]    

section .stage1.data

section .stage1.signature
    dw 0xAA55

