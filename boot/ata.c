#include "ata.h"

inline void outb(u16 port, u8 data) {
  asm volatile ("outb %b0, %w1"
    :
    : "a"(data), "Nd"(port)
    : "memory");
}

inline u8 inb(u16 port) {
  u8 ret;
  asm volatile ("inb %w1, %b0"
    : "=a"(ret)
    : "Nd"(port)
    : "memory");
  return ret;
}

inline u16 inw(u16 port) {
  u16 ret;
  asm volatile ("inw %w1, %w0"
    : "=a"(ret)
    : "Nd"(port)
    : "memory");
  return ret;
}

inline void io_wait(void) {
  outb(0x80, 0);
}

#include "../kernel/terminal.h"
#include "../kernel/util.h"

extern u32 KERNEL_SRC[]; 
extern u32 KERNEL_DST[]; 
extern u32 KERNEL_LEN[]; 

char b[30] = { 0 };
void load_kernel(void) {
  u16 kernel_src = (u32)KERNEL_SRC;
  u16 kernel_dst = (u32)KERNEL_DST;
  u16 kernel_len = (u32)KERNEL_LEN;
  
  format(b, 30, "%i %i %i\n", kernel_src, kernel_dst, kernel_len);
  terminal_write(b, 30);

  // Set to LBA mode.always already knows that the device is in that c
  outb(0x1F6, 0x40);

  // we want to read 0x200 to 0x400000
  u8 lba0 = kernel_src >> 0;
  u8 lba1 = kernel_src >> 8;
  u8 lba2 = kernel_src >> 16;
  u8 lba3 = kernel_src >> 24;
  u8 lba4 = 0; //v >> 32;
  u8 lba5 = 0; //v >> 40;

  // 4 sector size
  outb(0x1F2, (u8)(kernel_len >> 8));
  outb(0x1F3, lba3);
  outb(0x1F4, lba4);
  outb(0x1F5, lba5);
  outb(0x1F2, (u8)kernel_len);
  outb(0x1F3, lba0);
  outb(0x1F4, lba1);
  outb(0x1F5, lba2);
  outb(0x1F7, 0x24);

  // Begin read sequence
  u16 *dst = (u16*)0x400000;
  for (u32 i = 0; i < kernel_len; i++) {
    // Wait for data to be available.
    union AtaStatusRegister status = { 0 };
    do {
      status.raw = inb(0x1F7);
    } while (status.bsy == 1 && status.drq == 0);

    // Transfer
    for (u16 j = 0; j < 0x100; j++) {
      *dst++ = inw(0x1F0);
    }
  }
}
