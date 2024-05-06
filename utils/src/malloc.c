#include "avr-arch.h"
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
 * implementation_details:
 * we need a few bit masks to help us interact with the allocated block header.
 * We also need a few flags
 */
static uint16_t MAGIC_NUMBER = 0x0003;
static uint16_t ALLOCATED_MASK = 0x07;
static uint16_t ACTIVE_MASK = 0x08;
static uint16_t ACTIVE_SHIFT = 3;
static uint16_t SIZE_MASK = 0xffe0;
static uint16_t SIZE_SHIFT = 5;

/**
 * @implementation_details:
 * before we begin implemntation of malloc I would like make use of the
 * panic module to help us debug our malloc implementation. The function
 * provided by the module... panic() expects a function pointer to a
 * function that takes a void_ptr_t as an argument. This will allow us to
 * define whatever panic handler we want.
 *
 * Here we will transmit an error message to the host via serial.
 */
static void panic_handler(void_ptr_t arg1) {
  // cast the void_ptr_t to a char_ptr_t
  uint8_ptr_t error_msg = (uint8_ptr_t)arg1;
  // Initialize the USART module
  usart0_init(103);
  // send the error message over the USART module
  usart0_transmit_string(error_msg);
}

/**
 * @function:
 * mergeBytes
 * @arguments: highByte, lowByte
 * @return: uint16_t
 * @description:
 * This function takes two bytes and merges them into a single 16 bit value.
 */
uint16_t mergeBytes(uint8_t highByte, uint8_t lowByte) {
  return (uint16_t)((highByte << 8) | lowByte);
}

/**
 * @function:
 * active_block
 * @arguments: uint8_ptr_t ptr
 * @return: true if the block is active, false otherwise
 */
static uint8_t active_block(uint8_ptr_t ptr) {
  uint16_ptr_t header = (uint16_ptr_t)(ptr - 2);
  return ((*header & ACTIVE_MASK) >> ACTIVE_SHIFT) == 1;
}

/**
 * @function:
 * allocated_block
 * @arguments: uint8_ptr_t ptr
 * @return: true if the block is allocated, false otherwise
 */
static uint8_t allocated_block(uint8_ptr_t ptr) {
  uint16_ptr_t header = (uint16_ptr_t)(ptr - 2);
  return (*header & ALLOCATED_MASK) == MAGIC_NUMBER;
}

/**
 * @function:
 * block_size
 * @arguments: uint8_ptr_t ptr
 * @return: uint16_t
 * @description:
 * This function will return the size of the block pointed to by ptr.
 */
static uint16_t block_size(uint8_ptr_t ptr) {
  uint16_ptr_t header = (uint16_ptr_t)(ptr - 2);
  return (*header & SIZE_MASK) >> SIZE_SHIFT;
}

/**
 * @function:
 * jump_to_next_block
 * @arguments: uint8_ptr_t ptr
 * @return: uint8_ptr_t
 * @description:
 * This function will return a pointer to the next valid block address in the
 * heap given some allocated address. It will ensure two bytes preceding the
 * returned address are free for the header.
 */
static uint8_ptr_t jump_to_next_block(uint8_ptr_t ptr) {
  uint16_t block_sz = block_size(ptr);
  //+1 for buffer
  // +2 mod 2 for aligned address
  // +2 for header
  return (uint8_ptr_t)(((uint16_t)ptr + (uint16_t)block_size + 1 + 2) % 2) + 2;
}

/**
 * @function:
 * check_stack_heap_collision
 * @arguments: void
 * @return: void
 * @description:
 * This function will check if the stack and the heap have collided. We will
 * call this function everytime we allocate memory/free memory. This will
 * helps us out a little when it comes to this issue.
 */
static void check_stack_heap_collision() {
  // 10 bytte buffer zone
  uint8_t buffer = 10;
  // get the stack pointer
  uint16_t stack_pointer = mergeBytes(SPH, SPL);
  // if the stack pointer is less than the heap start address we have a
  // collision
  if (stack_pointer < (uint16_t)__HEAP_END + buffer) {
    uint8_t error_msg[20] = "Stack/Heap collision";
    panic(panic_handler, (void_ptr_t)error_msg);
  }
}

/**
 * @implementation_details:
 * now we need to find the first 2 byte aligned address that is not allocated
 * and there is enough space to allocate the requested size.
 */
static uint8_ptr_t find_free_block(uint16_t size) {
  // from __HEAP_START find first 2 byte aligned address that is not
  // allocated, i.e. it does not have the magic number in the allocated
  // heaader section.
  uint8_ptr_t current = __HEAP_START;
  while (current < __HEAP_END) {
    uint16_ptr_t header = (uint16_ptr_t)current;
    if (allocated_block(current)) {
      if (active_block(current)) {
        // we have found an allocated and active block
        //  we need to skip this block
        current = jump_to_next_block(current);
        continue;
      } else {
        // we have found an allocated but inactive block
        // we can use this block
        if (block_size(current) >= size) {
          return current;
        }
        current = jump_to_next_block(current);
        continue;
      }
    }
  }
  return current;
}

/**
 * @function:
 * initialize_block
 * @arguments: uint8_ptr_t block
 * @return: void
 * @description:
 * This function will initialize the block pointed to by block. It will set the
 * size, active and allocated flags in the header.
 */
static void initialize_block(uint8_ptr_t block, uint16_t size) {
  uint16_ptr_t header = (uint16_ptr_t)(block - 2);
  // set the size
  *header = size << SIZE_SHIFT;
  // set the allocated flag
  *header |= MAGIC_NUMBER;
  // set the active flag
  *header |= 1 << ACTIVE_SHIFT;
  // set the buffer too the magic number
  *(block + size) = MAGIC_NUMBER;
}

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

  // check for stack/heap collision
  check_stack_heap_collision();

  // find a free block
  uint8_ptr_t free_block = find_free_block(size);

  // initialize the block
  initialize_block(free_block, size);

  // set the ptr to the beginning of the payload block
  *ptr = free_block;

  // update the heap end
  __HEAP_END = jump_to_next_block(free_block);

  return 0;
}

/**
 * @function:
 * free
 * @arguments: uint8_ptr_t ptr
 * @return: void
 * @description:
 * This function will free the block pointed to by ptr. It will set the active
 * flag to 0.
 */
void free(uint8_ptr_t ptr) {
  // ensure no stack/heap collision has occured
  check_stack_heap_collision();
  // get the header
  uint16_ptr_t header = (uint16_ptr_t)(ptr - 2);
  if (!allocated_block(ptr)) {
    uint8_t error_msg[20] = "Block not allocated";
    panic(panic_handler, (void_ptr_t)error_msg);
  } else if (!active_block(ptr)) {
    uint8_t error_msg[16] = "double free";
    panic(panic_handler, (void_ptr_t)error_msg);
  } else {
    // set the active flag to 0
    *header &= ~(1 << ACTIVE_SHIFT);
  }
}