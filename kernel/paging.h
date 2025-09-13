// https://wiki.osdev.org/Paging

#pragma once

#include "int.h"

union PageDirectoryEntry {
  struct PageDirectoryEntry4mb {
    usize p : 1;
    usize rw : 1;
    usize us : 1;
    usize pwt : 1;
    usize pcd : 1;
    usize a : 1;
    usize d : 1;
    usize one : 1; // Always 1
    usize g : 1;
    usize : 3;
    usize pat : 1;
    usize address_39_32 : 8;
    usize zero : 1;
    usize address_31_22 : 10;
  } page_size_4mb;
  struct PageDirectoryEntry4kb {
    usize p : 1;
    usize rw : 1;
    usize us : 1;
    usize pwt : 1;
    usize pcd : 1;
    usize a : 1;
    usize : 1;
    usize zero : 1;
    usize : 4;
    usize address_31_12: 20;
  } page_size_4kb;
  struct {
    usize : 7;
    usize size : 1;
    usize : 24;
  };
};

extern union PageDirectoryEntry page_directory[1024];
