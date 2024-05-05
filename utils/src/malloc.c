#include "panic.h"
#include "types.h"
#include "usart.h"

/**
 * @implementation_details:
 * __HEAP_START is a symbol defined in the custom linker script used throughout
 * this project. It is the address of the first byte after the bss section in
 * sram. Remember, after the data and bss sections that our main program
 * expects.
 */
extern uint8_ptr_t __HEAP_START;

/**
 * @implementation_details:
 * __HEAP_END is a static symbol defined here. We will use this to point to the
 * next 2 byte aligned address after the memory block allocated the farthest
 * from the start of the heap.
 *
 * static so it is not visible outside this module.
 */
static uint8_ptr_t __HEAP_END = 0x0000;

/**
 * @implementation_details:
 * before we begin implemntation of malloc I would like make use of the panic
 * module to help us debug our malloc implementation. The function provided by
 * the module... panic() expects a function pointer to a function that takes a
 * void_ptr_t as an argument. This will allow us to define whatever panic
 * handler we want.
 *
 * Here we will transmit an error message to the host via serial.
 */
void panic_handler(void_ptr_t arg1) {
  // cast the void_ptr_t to a char_ptr_t
  uint8_ptr_t error_msg = (uint8_ptr_t)arg1;
  // Initialize the USART module
  usart0_init(103);
  // send the error message over the USART module
  usart0_transmit_string(error_msg);
}

/**
 * @implementation_details:
 *
 */
int malloc(uint16_t size, uint8_ptr_ptr_t ptr, uint16_t line) {
  // if size is 0 we will panic
  if (size == 0) {
    uint8_t start_msg[16] = "Error on line 0x";
    uint8_t line_number[2];
    line_number[0] = (uint8_t)line >> 8;
    line_number[1] = (uint8_t)line;
    uint8_t error_msg[18] = ": malloc size is 0";
    panic(panic_handler, (void_ptr_t)&line_number);
    return -1;
  }

  // check if heap is initialized
  if (__HEAP_END == 0x0000) {
    __HEAP_END = __HEAP_START;
  }

  return 0;
}