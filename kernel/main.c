extern void _start(void);

#include "terminal.h"
#include "util.h"

void _start(void) {
  // Print the beginning of 0x400000
  char buf[5];
  for (u16 i = 0; i < TERMINAL_WIDTH * TERMINAL_HEIGHT / 5; i++) {
    u8 byte = *(u8*)(0x400000 + i);

    format(buf, 5, "%i ", byte);
    terminal_write(buf, 5);
  }
  return;
}
