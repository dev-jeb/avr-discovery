/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose: This will be an example of using the panic module to panic the
 * system. It is designed with the strategy pattern in mind. The user can define
 * function to be called when panic is called. This function will be passed the
 * argument that was passed to panic. I would like to expend it to accept
 * arbitrary number of arguments.
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
  // cast the void_ptr_t to a char_ptr_t
  uint8_ptr_t error_msg = (uint8_ptr_t)arg1;
  // Initialize the USART module
  usart0_init(103);
  // send the error message over the USART module
  usart0_transmit_string(error_msg);
}

/**
 * now we can use our user define panic handler
 */
int main(void) {
  // call panic with the user defined panic handler
  panic(panic_handler, (void_ptr_t) "This is a test panic message");
  return 0;
}

/**
 * @notes:
 *
 * To see this work I run this directly on a physical microcontroller that is
 * connected to a serial terminal. First I build the project. I then go outside
 * of my container on my host machine and run avrdude to flash the
 * microcontroller. I dont do this in the container because I have yet to figure
 * out how to access the serial device from the container. I would also like to
 * find a way to run this using simavr and gdb or some combination to see this
 * serial output in a terminal. I will have to look into this.
 *
 * You  can use simavr to run the main.elf file. I have yet to find a way to be
 * able to see the actual serial output. However you can see that the USART is
 * configured and see the baud rate and data format running simavr with this
 * command.
 *
 * simavr -v -v -v -f 16000000 -m atmega328p -t main.elf
 */