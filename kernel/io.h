#pragma once

#include "int.h"

static inline void outb(u16 port, u8 data) {
  __asm__ volatile ("outb %b0, %w1"
    :
    : "a"(data), "Nd"(port)
    : "memory");
}
static inline void outw(u16 port, u16 data) {
  __asm__ volatile ("outw %w0, %w1"
    :
    : "a"(data), "Nd"(port)
    : "memory");
}
static inline void outl(u16 port, u32 data) {
  __asm__ volatile ("outl %d0, %w1"
    :
    : "a"(data), "Nd"(port)
    : "memory");
}

static inline u8 inb(u16 port) {
  u8 ret;
  __asm__ volatile ("inb %w1, %b0"
    : "=a"(ret)
    : "Nd"(port)
    : "memory");
  return ret;
}
static inline u16 inw(u16 port) {
  u16 ret;
  __asm__ volatile ("inw %w1, %w0"
    : "=a"(ret)
    : "Nd"(port)
    : "memory");
  return ret;
}
static inline u32 inl(u16 port) {
  u32 ret;
  __asm__ volatile ("inl %w1, %d0"
    : "=a"(ret)
    : "Nd"(port)
    : "memory");
  return ret;
}

static inline void io_wait(void) {
  outb(0x80, 0);
}

