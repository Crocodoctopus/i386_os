//union PageDirectoryEntry page_directory[1024] __attribute__((aligned(4096)));

#include "../kernel/paging.h"
#include "../kernel/gdt.h"

extern union PageDirectoryEntry page_directory[1024];

struct GDTEntry bootloader_gdt[3] = {
  {
    .low_limit = 0,
    .low_base = 0,
    .access = 0,
    .high_limit = 0,
    .flags = 0,
    .high_base = 0,
  },
  {
    .low_limit = 0xFFFF,
    .low_base = 0,
    .access = 0b10011010,
    .high_limit = 0b1111,
    .flags = 0b1100,
    .high_base = 0,
  },
  {
    .low_limit = 0xFFFF,
    .low_base = 0,
    .access = 0b10010010,
    .high_limit = 0b1111,
    .flags = 0b1100,
    .high_base = 0,
  },
};

struct GDT32Descriptor bootloader_gdt_descriptor = {
  .size = (u16)sizeof(bootloader_gdt),
  .offset = (u32)bootloader_gdt,
};

void init_page_directory() {
  for (usize i = 0; i < 1024; i++) {
    page_directory[i] = (union PageDirectoryEntry) { 0 };
  }

  // Map 1st 4MB chunk of physical ram to 0x0
  page_directory[0].page_size_4mb = (struct PageDirectoryEntry4mb) {
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

  // Map 2nd 4MB chunk of physical ram to 0xF0000000
  u16 base = 0b1111000000;
  page_directory[base].page_size_4mb = (struct PageDirectoryEntry4mb) {
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

