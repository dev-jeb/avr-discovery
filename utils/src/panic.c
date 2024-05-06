#include "panic.h"

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
void panic(void (*func)(void_ptr_t), void_ptr_t arg1) {
  // call user defined function with the passed argument
  func(arg1);
};