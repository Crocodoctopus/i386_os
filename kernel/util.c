#include "util.h"

#include <stdarg.h>

i32 format(char *buffer, const usize n, const char *format, ...) {
  if (format == 0) return -1;
  if (buffer == 0) return -2;
  if (n == 0) return -3;

  va_list args;
  va_start(args, format);
  
  const char *const buffer_end = buffer + n;
  #define BUFFER_REM ((usize)(buffer_end - buffer))

  //
  while (BUFFER_REM > 1 && *format) {
    switch (*format) {
      // The format string cursor is over a null, exit.
      case 0: break; // Impossible case.

      // The format string cursor is over a format symbol...
      case '%':
        switch (*(format + 1)) {
          case 0:
            goto single_print;

          case 'i': {
            i32 arg = va_arg(args, i32);

            // Calculate number of digits, store them in a temp buffer
            char digits[11]; // "-2147483648" is the longest algorithm can produce
            char *digits_cursor = digits;
            i32 num = ABS(arg);
            do {
              *digits_cursor++ = num % 10 + 0x30;
              num /= 10;
            } while (num != 0);
            
            // Place - if applicable.
            if (arg < 0) {
              *digits_cursor++ = '-';
            }
            
            // Calculate how many digits can be copied into the output buffer
            u32 digits_to_copy = MIN(BUFFER_REM - 1, digits_cursor - digits);

            // Copy the digits from temp buffer to final buffer
            for (u32 i = 0; i < digits_to_copy; i++) {
              *buffer++ = *--digits_cursor;
            }

            format += 2;
          } break;
          
          case 'x':
          case 'X': {
            u32 hex_offset = (*(format + 1) == 'x'
              ? 'a' : 'A') - 10;
            u32 arg = va_arg(args, u32);

            // Calculate number of digits, store them in a temp buffer
            char digits[8]; // "-2147483648" is the longest algorithm can produce
            char *digits_cursor = digits;
            do {
              char digit = arg % 16;
              digit = digit < 10
                ? digit + '0'
                : digit + hex_offset;
              *digits_cursor++ = digit;
              arg /= 16;
            } while (arg != 0);
                        
            // Calculate how many digits can be copied into the output buffer
            u32 digits_to_copy = MIN(BUFFER_REM - 1, digits_cursor - digits);

            // Copy the digits from temp buffer to final buffer
            for (u32 i = 0; i < digits_to_copy; i++) {
              *buffer++ = *--digits_cursor;
            }

            format += 2;
          } break;

          default:
            goto single_print;
        };

        break;

      // The format string cursor is over a plain character, copy it.
      default:
      single_print:
        *buffer++ = *format++;
        break;
    }
  }

  // Make last buffer position null
  *buffer = '\0';
}
