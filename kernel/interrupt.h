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
