# Create necessary folders.
mkdir -p bin
mkdir -p tmp

# Create various obj files.
nasm -O2 -f elf32 boot/stage1.asm -o tmp/stage1.o
nasm -O2 -f elf32 boot/stage2.asm -o tmp/stage2.o
nasm -O2 -f elf32 kernel/isr.asm -o tmp/isr.o
nasm -O2 -f elf32 kernel/gdt.asm -o tmp/gdt.o
gcc -O2 -c kernel/main.c -o tmp/main.o -ffreestanding -nostdlib -nostartfiles -m32 -fno-pie
gcc -O2 -c kernel/interrupt.c -o tmp/interrupt.o -ffreestanding -nostdlib -nostartfiles -m32 -fno-pie

# Link.
ld -T linker.lnk -o bin/kernel.bin tmp/interrupt.o tmp/main.o tmp/isr.o tmp/gdt.o

# Delete tmp folder.
rm tmp -r
