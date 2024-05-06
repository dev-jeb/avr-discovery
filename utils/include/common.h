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

/**
 * Define a function that return the length of a null terminated string
 */
#define STRLEN(string)                                                         \
  ({                                                                           \
    uint32_t length = 0;                                                       \
    while (string[length] != '\0') {                                           \
      length++;                                                                \
    }                                                                          \
    length;                                                                    \
  })

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