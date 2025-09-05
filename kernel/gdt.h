// https://wiki.osdev.org/Global_Descriptor_Table

#pragma once

#include "int.h"

struct __attribute__((packed)) GDTEntry {
  u16 low_limit;
  u32 low_base : 24;
  u8 access;
  u8 high_limit : 4;
  u8 flags : 4;
  u8 high_base;
};

struct __attribute__((packed)) GDT32Descriptor {
  u16 size;
  u32 offset;
};

/*
struct __attribute__((packed)) GDTEntry {
  u16 low_limit;
  u32 low_base : 24;
  u8 access_p : 1;
  u8 access_dpl : 1;
  u8 access_s : 1;
  u8 access_e : 1;
  u8 access_dc : 1;
  u8 access_rw : 1;
  u8 access_a : 1;
  u8 high_limit : 4;
  u8 flags_g : 1;
  u8 flags_db : 1;
  u8 flags_l : 1;
  u8 flags_reserved : 1;
  u8 high_base;
};
*/
