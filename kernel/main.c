extern void _start(void);

#include "terminal.h"
#include "util.h"

void _start(void) {
  char buf[20] = { 0 };
  terminal_write(buf, 20);
  format(buf, 20, "%i w\n", &_start);
  terminal_write(buf, 20);
  return;
}
