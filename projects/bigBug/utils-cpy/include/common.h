#ifndef AVR_COMMON_H
#define AVR_COMMON_H

/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * This module will provide a way to define common macros
 **/

#include "types.h"

/**
 * @function:
 * strlen
 * @arguments: str - a pointer to a string
 * @return: uint16_t - the length of the string
 * @description:
 * This function will return the length of the string pointed to by str.
 */
uint16_t strlen(uint8_ptr_t str);

/**
 * @function:
 * str_copy
 * @arguments: dest, src
 * @return: void
 * @description:
 * This function will copy the null teminaed string pointed to by src to the
 * location pointed to by dest ensuring it is still null terminated.
 */
void str_copy(uint8_ptr_t dest, uint8_ptr_t src);

/**
 * Define some useful macros that operate on individual bits
 * in a register.
 */

// Set a bit in a register to 0
#define DISABLE(REGISTER, BIT) (REGISTER) &= ~(1 << BIT)
// Set a bit in a register to 1
#define ENABLE(REGISTER, BIT) (REGISTER) |= (1 << BIT)
// Toggle a bit in a register
#define TOGGLE(REGISTER, BIT) (REGISTER) = (REGISTER) ^ (1 << BIT)
// Toggle BIT in REGISTER twice
#define TRIGGER(REGISTER, BIT)                                                 \
  do {                                                                         \
    TOGGLE(REGISTER, BIT);                                                     \
    TOGGLE(REGISTER, BIT);                                                     \
  } while (0)
// Check if a bit in a register is 1
#define IS_SET(REGISTER, BIT) (REGISTER & (1 << BIT)) > 0

#endif // AVR_COMMON_H