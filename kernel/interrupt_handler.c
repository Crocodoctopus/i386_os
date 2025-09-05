#include "int.h"

#include "util.h"
#include "pic.h"
#include "terminal.h"

struct __attribute__((packed)) InterruptState {
  //u32 edi, esi, ebp, kern_esp, ebx, edx, ecx, eax;
  u32 interrupt, error;
  u32 eip, cs, eflags;
  u32 esp, ss; // these may not have been pushed
};

char data[12] = { 0 };
void __attribute((cdecl)) interrupt_handler(struct InterruptState *state) {

  // Handle IRQ from external devices.
  if (state->interrupt >= 32) {
    format(data, 12, "IRQ %i ", state->interrupt - 32);
    terminal_write(data, 12);

    if (state->interrupt == 33) {
      inb(0x64);
    }
    
    pic_send_eoi(state->interrupt - 32);
  }
}
