extern void _start(void);

#include "terminal.h"
#include "util.h"
#include "pic.h"
#include "idt.h"

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

char buf[30] = { 0 };
__attribute__((noreturn)) void _start(void) {
  // 
  terminal_clear();

  // Initialize idt32 and
  init_idt32();
  set_idt(&idt_descriptor);
  
  init_pic();

  sti();

  format(buf, 30, "&_start: %i\n", &_start); 
  terminal_write(buf, 30);

  while (1) {
    hlt();
  }
}
