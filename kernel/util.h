#pragma once

#include "int.h"

i32 format(char *buffer, const usize n, const char *format, ...);

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define ABS(a) (a < 0 ? -a : a)
