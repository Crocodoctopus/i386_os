extern void _start(void);

#include "terminal.h"
#include "util.h"
#include "pic.h"
#include "idt.h"
#include "paging.h"

static inline void hlt(void) {
  __asm__ volatile("hlt" ::: "memory");
}

static inline void sti(void) {
  __asm__ volatile("sti" ::: "memory");
}

static inline void set_idt(struct IDT32Descriptor *idtr) {
  __asm__ volatile("lidt %0"
    :
    : "m"(*idtr)
    : "memory");
}

extern u8 kernel_stack[];

__attribute__((noreturn)) void _start(void) {    
  char buf[50] = { 0 };

  //
  terminal_clear();

  // Initialize idt32.
  init_idt32();
  set_idt(&idt_descriptor);

  // Initialize programmable interrupt chip.
  init_pic();

  // Interrupts can now be properly handled.
  sti();

  // Print some debug stuff.
  format(buf, 50, "&_start: %X\nstack: %X\n", &_start, kernel_stack); 
  terminal_write(buf, 50);

  // TODO
  while (1) {
    hlt();
  }
}
