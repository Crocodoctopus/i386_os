#include "int.h"

#include "util.h"

struct __attribute__((packed)) InterruptState {
  u32 edi, esi, ebp, kern_esp, ebx, edx, ecx, eax;
  u32 interrupt, error;
  u32 eip, cs, eflags, esp, ss;
};

char data[256] = { 0 };
void __attribute((cdecl)) interrupt_handler(struct InterruptState *state) {
  format(data, 256, "Interrupt: %i", state->interrupt);
  for (u8 i = 0; i < sizeof(data) - 1; i++) {
    *(u16*)(0xB8000 + 2 * i) = 0x0F00 | data[i];
  }
}
