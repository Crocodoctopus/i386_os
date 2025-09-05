#pragma once

#include "int.h"

inline void outb(u16 port, u8 data) {
  asm volatile ("outb %b0, %w1"
    :
    : "a"(data), "Nd"(port)
    : "memory");
}
inline void outw(u16 port, u16 data) {
  asm volatile ("outw %b0, %w1"
    :
    : "a"(data), "Nd"(port)
    : "memory");
}
inline void outl(u16 port, u32 data) {
  asm volatile ("outl %b0, %w1"
    :
    : "a"(data), "Nd"(port)
    : "memory");
}

inline u8 inb(u16 port) {
  u8 ret;
  asm volatile ("inb %w1, %b0"
    : "=a"(ret)
    : "Nd"(port)
    : "memory");
  return ret;
}
inline u16 inw(u16 port) {
  u16 ret;
  asm volatile ("inb %w1, %b0"
    : "=a"(ret)
    : "Nd"(port)
    : "memory");
  return ret;
}
inline u32 inl(u16 port) {
  u32 ret;
  asm volatile ("inb %w1, %b0"
    : "=a"(ret)
    : "Nd"(port)
    : "memory");
  return ret;
}

inline void io_wait(void) {
  outb(0x80, 0);
}

