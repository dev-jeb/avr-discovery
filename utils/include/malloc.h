#ifndef AVR__MALLOC_H
#define AVR__MALLOC_H

/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * This is a library that provides an implementation of the following functions
 * 1. malloc: Allocates a contigious block of SRAM memory of size bytes,
 * returning a pointer to the beginning of the block.
 * 2. free: Deallocates the memory block pointed to by ptr. If ptr is a null
 * pointer, no operation
 *
 * This library will look to implement a safe allocator that detects common bugs
 * such as out of bounds writes, double frees, and memory leaks. We will do this
 * at the cost of space in SRAM. However, we will try to minimize the memory
 * overhead.
 */

#include "types.h"

/**
 * @implementation_details:
 * When a user calls the function:
 *
 *   void* malloc(uint16_t size);
 *
 * if successful they will receive a 2 byte aligned `ptr` to the beginning of
 * the allocated payload block. The payload block will be of size bytes. The
 * allocated block will have the following structure in memory.
 *
 *          Allocated Block
 *       +------ptr - 2------+
 *       |                   |
 *       |        size       |
 *       |                   |
 *       +------ptr - 1------+
 * bit 0 |        size       |
 *       +-------------------+
 * bit 1 |        size       |
 *       +-------------------+
 * bit 2 |        size(LSB)  |
 *       +-------------------+
 * bit 3 |      reserved     |
 *       +-------------------+
 * bit 4 |       active      |
 *       +-------------------+
 * bit 5 |   allocated flag  |
 *       +-------------------+
 * bit 6 |   allocated flag  |
 *       +-------------------+
 * bit 7 |   allocated flag  |
 *       |        (LSB)      |
 *       +--------ptr--------+
 *       |                   |
 *       |      payload      |
 *       |                   |
 *       +-----ptr + size----+
 *       |                   |
 *       |       buffer      |
 *       |       (0xaa)      |
 *       |                   |
 *       +--ptr + size + 1---+
 *       |                   |
 *       |      padding      |
 *       |      ALIGN(2)     |
 *       +-------------------+
 *
 * @note:
 * LSB: least significant bit
 * ACTIVE: 1 if the blovk is in use, 0 if the block is free. This is used to
 * detect double frees. We will panic if a double free is detected.
 * ALLOCATED: will be a magic number to tell us this is an actual block
 * allocated by us. My favorite number is 3 (0000 0011).
 * BUFFER: will be used to detect out of bounds writes.
 */
/**
 * Notice how we have inserted a 2 byte header, 1 byte tail buffer and ((ptr
 * + size + 1) % 2) padding bytes.
 *
 * The `size` (an 11 bit value interpreted as an
 * uint16_t) is the number of bytes requested by the user (we can cover the
 * entire 2K SRAM in the microcontroller with 11 bits).
 *
 * The allocated flag is used to indicate if the block of
 * memory has been allocated or not. The padding size is used to ensure that
 * the payload is 2 byte aligned.
 */

/**
 * @function:
 * malloc: Allocates a block of size bytes of memory.
 * @param size: Size of the memory block, in bytes.
 * @return: On success a 2 byte aligned pointer to the memory block
 * allocated by the function else -1 if the function fails to allocate the
 * memory block.
 */
int malloc(uint16_t size, uint8_ptr_ptr_t ptr, uint16_t line);

/**
 * @function:
 * free: Deallocates the memory block pointed to by ptr. If ptr is a null
 * pointer, panic.
 *
 * @param ptr: Pointer to the memory block to be deallocated.
 */
void free(uint8_ptr_t ptr);

#endif // AVR__ALLOC_H
