extern void _start(void);

const unsigned char msg[] = "Hello world!";

void _start(void) {
  unsigned short *ptr = (unsigned short*)0xb8000;
  for (unsigned char i = 0; i < sizeof(msg); i++) {
    *(ptr + i) = msg[i] | 0x0F00;
  }
  return;
}
