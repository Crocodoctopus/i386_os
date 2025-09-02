#include "gdt.h"

struct GDTEntry gdt[3] = {
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

struct GDT32Descriptor gdt_descriptor = {
  .size = (u16)sizeof(gdt),
  .offset = (u32)gdt,
};
