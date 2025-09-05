#pragma once

#include "int.h"

#define TERMINAL_WIDTH 80
#define TERMINAL_HEIGHT 25
#define VGA_TEXT_BUFFER ((u16*)(0xB8000))

struct Terminal {
  u8 cursor_x;
  u8 cursor_y;
};

void terminal_write(const char *buffer, usize n);
void terminal_clear(void);
