# Create necessary folders.
mkdir -p bin
mkdir -p tmp

# Create various obj files.
nasm -O2 -f elf32 boot/bootloader.asm -o tmp/bootloader.o
gcc -O2 -c kernel/main.c -o tmp/main.o -ffreestanding -nostdlib -nostartfiles -m32 -fno-pie

#nasm -f elf32 stage2/main.asm -o tmp/stage2_main.o
#gcc -m32 -nostdlib kernel/kernel.c -o tmp/kernel.o

# Link.
ld -T linker.lnk -o bin/kernel.bin

# Delete tmp folder.
rm tmp -r
