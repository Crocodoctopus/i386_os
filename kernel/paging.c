#include "paging.h"

union PageDirectoryEntry page_directory[1024] __attribute__((aligned(4096), section(".paging_dir")));
