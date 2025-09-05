#include "terminal.h"

struct Terminal terminal = {
  .cursor_x = 0,
  .cursor_y = 0,
};

void terminal_write(const char *buffer, const usize n) {
  if (buffer == 0) return;

  for (usize i = 0; i < n; i++) {
    if (*buffer == 0) break;
    u8 c = *buffer++;

    if (c == '\n') {
      terminal.cursor_y++;
      terminal.cursor_x = 0;
      continue;
    }

    // Write to VGA.
    usize index = terminal.cursor_x + terminal.cursor_y * TERMINAL_WIDTH;
    VGA_TEXT_BUFFER[index] = 0x0F00 | c;
    terminal.cursor_x++;

    // Correct cursor.
    if (terminal.cursor_x > TERMINAL_WIDTH) {
      terminal.cursor_x = 0;
      terminal.cursor_y++;
    }
    if (terminal.cursor_y > TERMINAL_HEIGHT) {
      terminal.cursor_y = 0;
    }
  }
}

void terminal_clear(void) {
  for (usize i = 0; i < TERMINAL_WIDTH * TERMINAL_HEIGHT; i++) {
    VGA_TEXT_BUFFER[i] = 0x0000;
  }
  terminal.cursor_x = 0;
  terminal.cursor_y = 0;
}
