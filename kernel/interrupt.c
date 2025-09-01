#include "interrupt.h"

void __attribute__((noreturn)) idt_0(void) {
  __asm__ volatile ("cli; hlt");
  __builtin_unreachable();
}

void __attribute__((noreturn)) idt_1(void) {
  __asm__ volatile ("cli; hlt");
  __builtin_unreachable();
}

void __attribute__((noreturn)) idt_2(void) {
  __asm__ volatile ("cli; hlt");
  __builtin_unreachable();
}

const char data[] = "Hello world!";

void __attribute__((noreturn)) idt_3(void) {
  // Print "Hello world!"
  for (u8 i = 0; i < sizeof(data) - 1; i++) {
    *(u16*)(0xB8000 + 2 * i) = 0x0F00 | data[i];
  }
  __asm__ volatile ("iret");
  __builtin_unreachable();
}

struct IDT32Entry idt[4];
struct IDT32Descriptor idt_descriptor;

void init_idt(void) {
  idt[0] = (struct IDT32Entry) {
    .low_offset = (u32)idt_0,
    .selector = 8,
    .reserved = 0,
    .attributes = 0x8E,
    .high_offset = (u32)idt_0 >> 16,
  };
  idt[1] = (struct IDT32Entry) {
    .low_offset = (u32)idt_1,
    .selector = 8,
    .reserved = 0,
    .attributes = 0x8E,
    .high_offset = (u32)idt_1 >> 16,
  };
  idt[2] = (struct IDT32Entry) {
    .low_offset = (u32)idt_2,
    .selector = 8,
    .reserved = 0,
    .attributes = 0x8E,
    .high_offset = (u32)idt_2 >> 16,
  };
  idt[3] = (struct IDT32Entry) {
    .low_offset = (u32)idt_3,
    .selector = 8,
    .reserved = 0,
    .attributes = 0x8E,
    .high_offset = (u32)idt_3 >> 16,
  };

  idt_descriptor = (struct IDT32Descriptor) {
    .limit = (u16)sizeof(idt),
    .base = (u32)idt,
  };
}

