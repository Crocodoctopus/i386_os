// https://wiki.osdev.org/Interrupt_Descriptor_Table

#pragma once

#include "int.h"

struct __attribute__((packed)) IDT32Entry {
  u16 low_offset;
  u16 selector;
  u8 reserved;
  u8 gate_type : 4;
  u8 zero : 1;
  u8 dpl : 2;
  u8 p : 1;
  u16 high_offset;
};

struct __attribute__((packed)) IDT32Descriptor {
  u16 size;
  u32 offset;
};

void init_idt32(void);
