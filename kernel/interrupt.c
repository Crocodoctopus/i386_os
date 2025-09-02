#include "interrupt.h"

void __attribute((cdecl)) interrupt_handler(struct InterruptState *state) {
  // Print "Hello world!"
  const char data[] = "Hello world!";
  for (u8 i = 0; i < sizeof(data) - 1; i++) {
    *(u16*)(0xB8000 + 2 * i) = 0x0F00 | data[i];
  }
}

#define idt32_len 22
struct IDT32Entry idt[idt32_len] = { 0 };
struct IDT32Descriptor idt_descriptor = { 0 };
extern void *isr32_stub_address_table[idt32_len];

void set_idt32_entry(struct IDT32Entry *entry, void *offset, u8 attributes) {
  *entry = (struct IDT32Entry) {
    .low_offset = (u32)offset,
    .selector = 8,
    .reserved = 0,
    .attributes = attributes,
    .high_offset = (u32)offset >> 16,
  };
}

void init_idt32(void) {
  for (u8 i = 0; i < idt32_len; i++)
    set_idt32_entry(idt + i, isr32_stub_address_table[i], 0x8E);  

  idt_descriptor = (struct IDT32Descriptor) {
    .limit = (u16)sizeof(idt),
    .base = (u32)idt,
  };
}

