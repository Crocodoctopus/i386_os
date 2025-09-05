#include "int.h"

#include "util.h"
#include "pic.h"

struct __attribute__((packed)) InterruptState {
  //u32 edi, esi, ebp, kern_esp, ebx, edx, ecx, eax;
  u32 interrupt, error;
  u32 eip, cs, eflags;
  u32 esp, ss; // these may not have been pushed
};

char data[12] = { 0 };
int j = 0;
void __attribute((cdecl)) interrupt_handler(struct InterruptState *state) {
  *(u16*)(0xB8000 + 2 * j) = 0x0F00 | '*';
  j++;

  // Handle IRQ from external devices.
  if (state->interrupt >= 32) {
    pic_send_eoi(state->interrupt - 32);
  }
}
