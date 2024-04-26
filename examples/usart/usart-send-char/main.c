/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * Here we will use the universal synchronous and asynchronous receiver and
 * transmitter (USART) to transmit a character
 */

/**
 * @implementation
 * The atmega328p has a Universal Synchronous/Asynchronous Receive Transmit
 * (USART) module that can be used to transmit and receive data. This data is
 * serially transmitted over the TXD pin and received over the RXD pin.
 */

#include "types.h"
#include "usart.h"

int main(void) {
  // Initialize the USART module
  usart_init();
  // we can send a char by calling usart_send_char() function
  usart_send_char('a');
  // we cana also send a null-terminated string by calling usart_send_string()
  char *str = "Hello, World!";
  usart_send_string((uint8_ptr_t)str);
  return 0;
}

/**
 * @notes:
 *
 * You  can use simavr to run the main.elf file. I have yet to find a way to be
 * able to see the actual serial output. However you can see that the USART is
 * configured and see the baud rate and data format running simavr with this
 * command.
 *
 * simavr -v -v -v -f 16000000 -m atmega328p -t main.elf
 */