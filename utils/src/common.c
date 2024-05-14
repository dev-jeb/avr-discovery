#include "types.h"

void str_copy(uint8_ptr_t dest, uint8_ptr_t src) {
  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
};