/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * Here we will use the universal synchronous and asynchronous receiver and
 * transmitter (USART) to transmit a character
 */

#include "types.h"
#include "usart.h"

int main(void) {
  // Initialize the USART module
  usart_init();
  // Loop forever printing a char every 1 second
  char *str = "Hello, World!";
  usart_send_string((uint8_ptr_t)str);
  return 0;
}