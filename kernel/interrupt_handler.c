#include "int.h"

struct __attribute__((packed)) InterruptState {
  u32 ds;
  u32 edi, esi, ebp, kern_esp, ebx, edx, ecx, eax;
  u32 interrupt, error;
  u32 eip, cs, eflags, esp, ss;
};

void __attribute((cdecl)) interrupt_handler(struct InterruptState *state) {
  // Print "Hello world!"
  const char data[] = "Hello world!";
  for (u8 i = 0; i < sizeof(data) - 1; i++) {
    *(u16*)(0xB8000 + 2 * i) = 0x0F00 | data[i];
  }
}
