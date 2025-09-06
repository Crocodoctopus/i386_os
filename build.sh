# Create necessary folders.
mkdir -p bin
mkdir -p tmp

CFLAGS="-O2 -ffreestanding -nostdlib -nostartfiles -m32 -fno-pie -fno-asynchronous-unwind-tables"

# Create various obj files.
nasm -O2 -f elf32 boot/stage1.asm -o tmp/stage1.o
nasm -O2 -f elf32 boot/stage2.asm -o tmp/stage2.o
gcc -c boot/ata.c -o tmp/ata.o $CFLAGS
nasm -O2 -f elf32 kernel/isr.asm -o tmp/isr.o
gcc -O2 -c kernel/gdt.c -o tmp/gdt.o $CFLAGS
gcc -O2 -c kernel/main.c -o tmp/main.o $CFLAGS
gcc -O2 -c kernel/pic.c -o tmp/pic.o $CFLAGS
gcc -O2 -c kernel/idt.c -o tmp/idt.o $CFLAGS
gcc -O2 -c kernel/interrupt_handler.c -o tmp/interrupt_handler.o $CFLAGS
gcc -O2 -c kernel/util.c -o tmp/util.o $CFLAGS
gcc -O2 -c kernel/paging.c -o tmp/paging.o $CFLAGS
gcc -O2 -c kernel/terminal.c -o tmp/terminal.o $CFLAGS

#for FILE in tmp/*.o; do
#  objcopy -R .note* -R .comment $FILE
#done
  
# Link.
ld -T linker.lnk -o bin/kernel.bin tmp/idt.o tmp/main.o tmp/isr.o tmp/gdt.o tmp/interrupt_handler.o tmp/util.o tmp/pic.o tmp/terminal.o

# Delete tmp folder.
# rm tmp -r
