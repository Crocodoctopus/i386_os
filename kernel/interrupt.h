#include "int.h"

struct __attribute__((packed)) IDT32Entry {
  u16 low_offset;
  u16 selector;
  u8 reserved;
  u8 attributes;
  u16 high_offset;
};

struct __attribute__((packed)) IDT32Descriptor {
  u16 limit;
  u32 base;
};

struct __attribute__((packed)) InterruptState {
  u32 ds;
  u32 edi, esi, ebp, kern_esp, ebx, edx, ecx, eax;
  u32 interrupt, error;
  u32 eip, cs, eflags, esp, ss;
};
