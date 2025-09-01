extern void _start(void);

unsigned short v = 0x0F42;

void _start(void) {
  *(unsigned short*)0xb8000 = v;
  return;
}
