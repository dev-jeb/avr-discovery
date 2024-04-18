/**
 * a general program
 *
 * This will be the program we will load into a page of flash memory. By
 * exploring this file we can deduce the different sections of memory that the
 */

#include "types.h"

// initalized variable are stored in the data section of the object file
uint8_t i_live_in_prog2_data = 0xAA;

// uninitialized variables are stored in the BSS section of the object file
uint8_t i_live_in_prog2_bss;

void prog2_entry() {
  // we must have a runtime stack to store local variables
  uint8_t i_live_on_prog2_stack = 0xBB;
}
