#include "pic.h"

void pic_send_eoi(u8 irq) {
  if (irq > 7)
    outb(PIC2_COMMAND_PORT, PIC_EOI);
  outb(PIC1_COMMAND_PORT, PIC_EOI);
}

void init_pic(void) {
  outb(PIC1_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);
  io_wait();
  outb(PIC2_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);
  io_wait();
  outb(PIC1_DATA_PORT, 0x20); // interrupt offset
  io_wait();
  outb(PIC2_DATA_PORT, 0x28); // interrupt offset
  io_wait();
  outb(PIC1_DATA_PORT, 0x4);
  io_wait();
  outb(PIC2_DATA_PORT, 0x2);
  io_wait();

  outb(PIC1_DATA_PORT, ICW4_8086);
  io_wait();
  outb(PIC2_DATA_PORT, ICW4_8086);
  io_wait();

  outb(PIC1_DATA_PORT, 0);
  io_wait();
  outb(PIC2_DATA_PORT, 0);
  io_wait();
}
