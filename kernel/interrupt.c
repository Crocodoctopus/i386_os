#include "interrupt.h"

void __attribute((cdecl)) interrupt_handler(struct InterruptState *state) {
  // Print "Hello world!"
  const char data[] = "Hello world!";
  for (u8 i = 0; i < sizeof(data) - 1; i++) {
    *(u16*)(0xB8000 + 2 * i) = 0x0F00 | data[i];
  }
}

struct IDT32Entry idt[256] = { 0 };
struct IDT32Descriptor idt_descriptor = { 0 };

// I can probably do something better...
extern void isr32_0(void);
extern void isr32_1(void);
extern void isr32_2(void);
extern void isr32_3(void);
extern void isr32_4(void);
extern void isr32_5(void);
extern void isr32_6(void);
extern void isr32_7(void);
extern void isr32_8(void);
extern void isr32_9(void);
extern void isr32_10(void);
extern void isr32_11(void);
extern void isr32_12(void);
extern void isr32_13(void);
extern void isr32_14(void);
extern void isr32_15(void);
extern void isr32_16(void);
extern void isr32_17(void);
extern void isr32_18(void);
extern void isr32_19(void);
extern void isr32_20(void);
extern void isr32_21(void);
extern void isr32_22(void);
extern void isr32_23(void);
extern void isr32_24(void);
extern void isr32_25(void);
extern void isr32_26(void);
extern void isr32_27(void);
extern void isr32_28(void);
extern void isr32_29(void);
extern void isr32_30(void);
extern void isr32_31(void);

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
  set_idt32_entry(idt + 0, isr32_0, 0x8E);
  set_idt32_entry(idt + 1, isr32_1, 0x8E);
  set_idt32_entry(idt + 2, isr32_2, 0x8E);
  set_idt32_entry(idt + 3, isr32_3, 0x8E);
  set_idt32_entry(idt + 4, isr32_4, 0x8E);
  set_idt32_entry(idt + 5, isr32_5, 0x8E);
  set_idt32_entry(idt + 6, isr32_6, 0x8E);
  set_idt32_entry(idt + 7, isr32_7, 0x8E);
  set_idt32_entry(idt + 8, isr32_8, 0x8E);
  set_idt32_entry(idt + 9, isr32_9, 0x8E);
  set_idt32_entry(idt + 10, isr32_10, 0x8E);
  set_idt32_entry(idt + 11, isr32_11, 0x8E);
  set_idt32_entry(idt + 12, isr32_12, 0x8E);
  set_idt32_entry(idt + 13, isr32_13, 0x8E);
  set_idt32_entry(idt + 14, isr32_14, 0x8E);
  set_idt32_entry(idt + 15, isr32_15, 0x8E);
  set_idt32_entry(idt + 16, isr32_16, 0x8E);
  set_idt32_entry(idt + 17, isr32_17, 0x8E);
  set_idt32_entry(idt + 18, isr32_18, 0x8E);
  set_idt32_entry(idt + 19, isr32_19, 0x8E);
  set_idt32_entry(idt + 20, isr32_20, 0x8E);
  set_idt32_entry(idt + 21, isr32_21, 0x8E);
  set_idt32_entry(idt + 22, isr32_22, 0x8E);
  set_idt32_entry(idt + 23, isr32_23, 0x8E);
  set_idt32_entry(idt + 24, isr32_24, 0x8E);
  set_idt32_entry(idt + 25, isr32_25, 0x8E);
  set_idt32_entry(idt + 26, isr32_26, 0x8E);
  set_idt32_entry(idt + 27, isr32_27, 0x8E);
  set_idt32_entry(idt + 28, isr32_28, 0x8E);
  set_idt32_entry(idt + 29, isr32_29, 0x8E);
  set_idt32_entry(idt + 30, isr32_30, 0x8E);
  set_idt32_entry(idt + 31, isr32_31, 0x8E);

  idt_descriptor = (struct IDT32Descriptor) {
    .limit = (u16)sizeof(idt),
    .base = (u32)idt,
  };
}

