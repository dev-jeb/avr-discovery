#include "types.h"

uint16_t strlen(uint8_ptr_t str) {
  uint16_t len = 0;
  while (*str != '\0') {
    len++;
    str++;
  }
  return len;
}

void str_copy(uint8_ptr_t dest, uint8_ptr_t src) {
  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
};