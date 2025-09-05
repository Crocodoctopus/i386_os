#include "paging.h"

union PageDirectoryEntry page_directory[1024] __attribute__((aligned(4096)));

void init_page_directory() {
  for (usize i = 0; i < 1024; i++) {
    page_directory[i] = (union PageDirectoryEntry) { 0 };
  }

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
