#ifndef AVR_TYPES_H
#define AVR_TYPES_H

/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * This module will provide a way to define common types
 */

// an unsigned 8-bit integer type
typedef unsigned char uint8_t;

// an unsigned 8-bit pointer type
typedef uint8_t *uint8_ptr_t;

// a signed 8-bit integer type
typedef signed char int8_t;

// a signed 8-bit pointer type
typedef signed char *int8_ptr_t;

// an unsigned 16-bit integer type
typedef unsigned short uint16_t;

// an unsigned 16-bit pointer type
typedef unsigned short *uint16_ptr_t;

// an unsigned 32-bit integer type
typedef unsigned long uint32_t;

// an unsigned 32-bit pointer type
typedef unsigned long *uint32_ptr_t;

// a void pointer type
typedef void *void_ptr_t;

// a null pointer constant
typedef void *null_ptr_t;

// a pointer to a pointer that points to uint8_t
typedef uint8_t **uint8_ptr_ptr_t;

#endif // AVR_TYPES_H