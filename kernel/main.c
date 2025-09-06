extern void _start(void);

#include "terminal.h"
#include "util.h"

  char buf[20] = { 0 };
void _start(void) {
  format(buf, 20, "%i w\n", &_start);
  terminal_write(buf, 20);
  return;
  
}
