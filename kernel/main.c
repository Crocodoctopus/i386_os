extern void _start(void);

void _start(void) {
  *(unsigned short*)0xb8000 = 0x0F41;
  return;
}
