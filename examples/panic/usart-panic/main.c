/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose: This will be an example of using the panic module to panic the
 * system. It is designed with the strategy pattern in mind. The user can define
 * a function to be called when we panic. This function will be passed
 * the argument that was passed to panic. I would like to expand it to accept an
 * arbitrary number of arguments.
 *
 * @workflow:
 * step 1: Build the program using the `make` command in the development
 * container.
 *
 * step 2: Flash the program to the microcontroller using avrdude from the host
 * using the following command
 *
 * >> avrdude -p atmega328p -c arduino -P /dev/<serial_device> -b <baud> -U \
 *    flash:w:<executable>
 *
 * step 3: Check the output of the program using a serial monitor like minicom
 *
 * >> minicom -D /dev/<serial_device> -b <baud>
 */

#include "panic.h"
#include "types.h"
#include "usart.h"

/**
 * @function_name:
 * panic_handler
 *
 * @params: void_ptr_t - a pointer to the error message
 *
 * @purpose: This function will be called when panic is called. It will be
 * passed the error message and will transmit it over the USART module.
 */
void panic_handler(void_ptr_t arg1) {
  // Initialize the USART module
  usart0_init(103);
  // send the error message over the USART module
  usart0_transmit_bytes((uint8_ptr_t)arg1);
}

/**
 * now we can use our user define panic handler
 */
int main(void) {
  // call panic with the user defined panic handler
  panic(panic_handler, (void_ptr_t) "This is a test!!!");
  return 0;
}

/**
 * @note: the workflow to build, flash and check this programs
 * output is not pretty. This is because on OSX (Mac) you can't access the
 * serial device on the host from the docker development container. This is a
 * known issue. I develop using the tool chain in the container, I step over to
 * my host machine to flash the program and monitor the serial device.
 */