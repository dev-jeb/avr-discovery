#ifndef AVR_PANIC_H
#define AVR_PANIC_H

/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * This module will provide a way to panic the system. This will help add
 * transparency to the microcontroller's state. The idea is to call panic when a
 * bad state has occurred and serially transmit the error message to a host
 */

#include "types.h"

/**
 * @function_name:
 * panic
 *
 * @params: func pointer - a function the will be passed the error message. The
 * func must be defined to take an argument of type void_ptr_t. THis allows for
 * the user to pass their arbitrary panic handler whatever information they
 * need.
 * @params: arg1 - a void_ptr_t that will be passed to the user defined panic
 * function.
 */
void panic(void (*func)(void_ptr_t), void_ptr_t arg1);

#endif // AVR_PANIC_H