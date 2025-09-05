#include "idt.h"

struct IDT32Entry idt[256] = { 0 };
struct IDT32Descriptor idt_descriptor = { 0 };
extern void *isr32_stub_address_table[256];

void set_idt32_entry(struct IDT32Entry *entry, void *offset, u8 gate_type, u8 dpl) {
  *entry = (struct IDT32Entry) {
    .low_offset = (u32)offset,
    .selector = 8,
    .reserved = 0,
    .gate_type = gate_type,
    .zero = 0,
    .dpl = dpl,
    .p = 1,
    .high_offset = (u32)offset >> 16,
  };
}

void init_idt32(void) {
  for (u16 i = 0; i < 256; i++)
    set_idt32_entry(idt + i, isr32_stub_address_table[i], 0xE, 0);  

  idt_descriptor = (struct IDT32Descriptor) {
    .size = (u16)sizeof(idt),
    .offset = (u32)idt,
  };
}

