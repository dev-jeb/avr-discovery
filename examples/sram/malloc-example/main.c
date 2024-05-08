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

/**
 * @function:
 * panic_handler
 * @arguments: arg1
 * @return: void
 * @description:
 * This function will be called when a panic occurs. It will print the error
 * message to the USART module.
 */
// void panic_handler(void_ptr_t msg, uint16_t line) {
//   uint16_t msg_len = strlen((uint8_ptr_t)msg);
//   // allocate space for the error message

//   // print the error message
//   usart0_transmit_bytes((uint8_ptr_t)msg, msg_len);
//   // free the memory
// }

int main(void) {
  // Initialize the USART module
  usart0_init(103);

  uint8_t msg[] = "Hello World";

  while (!(UCSR0A & (1 << UDRE0))) {
  };
  // Put data into buffer, sends the data
  UDR0 = msg[0];

  while (!(UCSR0A & (1 << TXC0))) {
  };
  // write a zero to TXC0 to clear the flag
  UCSR0A &= ~(1 << TXC0);

  // Allocate size=0 memory block
  // this should cause a panic by malloc
  // uint8_ptr_t ptr;
  // if (malloc(0, &ptr) == -1) {
  //   // defined in crt.s
  //   uint8_ptr_t msg1 = &"Memory allocation failed";
  //   usart0_transmit_bytes(msg1, strlen(msg1));
  // };

  // if (malloc(1, &ptr) == -1) {
  //   panic(panic_handler, "Memory allocation failed", 63);
  //   // defined in crt.s
  // };

  // // check to ensure the header is correct
  // uint16_ptr_t header = ((uint16_t *)(ptr - 2));

  // // size should be one
  // if ((*header & 0xffe0) >> 5 != 1) {
  //   panic(panic_handler, "Header size is incorrect", 72);
  // }

  // // allocated should be three
  // if ((*header & 0x07) != 3) {
  //   panic(panic_handler, "Header allocated is incorrect", 77);
  // }

  // // active should be one
  // if ((*header & 0x08) >> 3 != 1) {
  //   panic(panic_handler, "Header active is incorrect", 82);
  // }

  // // buffer should be 0x03
  // if (*(ptr + 1) != 0x03) {
  //   panic(panic_handler, "Buffer is incorrect", 97);
  // }

  // // Free the memory
  // // This returns -1 if the block is not allocated
  // if (free(ptr) == -1) {
  //   panic(panic_handler, "Freeing unallocated block", 93);
  // };

  // // now we weill free the same block again. This should set the
  // // MALLOC_ERRNO to DOUBLE_FREE
  // if (free(ptr) == -1) {
  //   panic(panic_handler, "Double Free Detected", 99);
  // };

  // // header active should be 0
  // if ((*header & 0x08) >> 3 != 0) {
  //   panic(panic_handler, "Header active is not 0 after free", 104);
  // }
  // // else we are good
  // panic(panic_handler, "All tests passed", 107);
  // return 0;
}