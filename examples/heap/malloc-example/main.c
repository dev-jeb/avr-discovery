/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose: Here we will explore the malloc/free implementation and try to
 * write a program that will help us debug the implementation.
 *
 *
 * @important_notes:
 */

#include "common.h"
#include "malloc.h"
#include "panic.h"
#include "types.h"
#include "usart.h"

uint8_t error_msg_1[] = "Memory allocation failed";
uint8_t error_msg_2[] = "Header size is incorrect";
uint8_t error_msg_3[] = "Header allocated is incorrect";
uint8_t error_msg_4[] = "Header active is incorrect";
uint8_t error_msg_5[] = "Buffer is incorrect";
uint8_t error_msg_6[] = "All tests pass";
uint8_t error_msg_7[] = "Header active should be set to 0 by free";
uint8_t error_msg_8[] = "Double Free Detected";
uint8_t error_msg_9[] = "Freeing unallocated block";

int main(void) {
  // Initialize the USART module
  usart0_init(103);

  // Allocate size=0 memory block
  // this should cause a panic by malloc
  uint8_ptr_t ptr;
  if (malloc(0, &ptr, 39) == -1) {
    // defined in crt.s
    usart0_transmit_bytes(error_msg_1, STRLEN(error_msg_1));

    usart0_transmit_byte(CARRIAGE_RETURN);

    usart0_transmit_byte(NEW_LINE);
  };

  if (malloc(1, &ptr, 44) == -1) {
    usart0_transmit_bytes(error_msg_1, STRLEN(error_msg_1));
    usart0_transmit_byte(CARRIAGE_RETURN);
    usart0_transmit_byte(NEW_LINE);
    // defined in crt.s
  };

  // check to ensure the header is correct
  uint16_ptr_t header = ((uint16_t *)(ptr - 2));

  // size should be one
  if ((*header & 0xffe0) >> 5 != 1) {
    usart0_transmit_bytes(error_msg_2, STRLEN(error_msg_2));
    usart0_transmit_byte(CARRIAGE_RETURN);
    usart0_transmit_byte(NEW_LINE);
  }

  // allocated should be three
  if ((*header & 0x07) != 3) {
    usart0_transmit_bytes(error_msg_3, STRLEN(error_msg_3));
    usart0_transmit_byte(NEW_LINE);
    usart0_transmit_byte(CARRIAGE_RETURN);
  }

  // active should be one
  if ((*header & 0x08) >> 3 != 1) {
    usart0_transmit_bytes(error_msg_4, STRLEN(error_msg_4));
    usart0_transmit_byte(NEW_LINE);
    usart0_transmit_byte(CARRIAGE_RETURN);
  }

  // buffer should be 0x03
  if (*(ptr + 1) != 0x03) {
    usart0_transmit_bytes(error_msg_5, STRLEN(error_msg_5));
    usart0_transmit_byte(NEW_LINE);
    usart0_transmit_byte(CARRIAGE_RETURN);
  }

  // Free the memory
  if (free(ptr) == -1) {
    usart0_transmit_bytes(error_msg_9, STRLEN(error_msg_9));
    usart0_transmit_byte(NEW_LINE);
    usart0_transmit_byte(CARRIAGE_RETURN);
  };

  if (free(ptr) == -1) {
    usart0_transmit_bytes(error_msg_8, STRLEN(error_msg_8));
    usart0_transmit_byte(NEW_LINE);
    usart0_transmit_byte(CARRIAGE_RETURN);
  };

  // header active should be 0
  if ((*header & 0x08) >> 3 != 0) {
    usart0_transmit_bytes(error_msg_7, STRLEN(error_msg_7));
    usart0_transmit_byte(NEW_LINE);
    usart0_transmit_byte(CARRIAGE_RETURN);
  }
  // else we are good
  usart0_transmit_bytes(error_msg_6, STRLEN(error_msg_6));
  usart0_transmit_byte(NEW_LINE);
  usart0_transmit_byte(CARRIAGE_RETURN);
}