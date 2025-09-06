//union PageDirectoryEntry page_directory[1024] __attribute__((aligned(4096)));

#include "../kernel/paging.h"
#include "../kernel/gdt.h"
#include "../kernel/ata.h"
#include "../kernel/io.h"

extern union PageDirectoryEntry PAGE_DIRECTORY_PHYS[1024];
extern u32 KERNEL_SRC[]; 
extern u32 KERNEL_DST[]; 
extern u32 KERNEL_LEN[]; 

void init_page_directory() {
  for (usize i = 0; i < 1024; i++) {
    PAGE_DIRECTORY_PHYS[i] = (union PageDirectoryEntry) { 0 };
  }

  // Unity map 0x0
  PAGE_DIRECTORY_PHYS[0].page_size_4mb = (struct PageDirectoryEntry4mb) {
    .p = 1,
    .rw = 1,
    .us = 0,
    .pwt = 0, // TODO
    .pcd = 0,
    .a = 0,
    .d = 0,
    .one = 1,
    .g = 1,
    .pat = 0,
    .address_39_32 = 0,
    .zero = 0,
    .address_31_22 = 0, 
  };

  // Map 0xFF000000 to first 0x400000
  PAGE_DIRECTORY_PHYS[0xFF000000 >> 22].page_size_4mb = (struct PageDirectoryEntry4mb) {
    .p = 1,
    .rw = 1,
    .us = 0,
    .pwt = 0, // TODO
    .pcd = 0,
    .a = 0,
    .d = 0,
    .one = 1,
    .g = 1,
    .pat = 0,
    .address_39_32 = 0,
    .zero = 0,
    .address_31_22 = 1, 
  };
}

void load_kernel(void) {
  void *kernel_src = KERNEL_SRC;
  void *kernel_dst = KERNEL_DST;
  u32 kernel_len = (u32)KERNEL_LEN;
  
  // Set to LBA mode.always already knows that the device is in that c
  outb(0x1F6, 0x40);

  // we want to read 0x200 to 0x400000
  u8 lba0 = (u32)kernel_src >> 0;
  u8 lba1 = (u32)kernel_src >> 8;
  u8 lba2 = (u32)kernel_src >> 16;
  u8 lba3 = (u32)kernel_src >> 24;
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
  u16 *dst = (u16*)kernel_dst;
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
