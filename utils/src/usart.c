#include "avr-arch.h"
#include "types.h"

void usart0_init(uint16_t ubrr_register_value) {
  /*ensure usart0 is not powered down*/
  PRR &= ~(1 << PRUSART0);
  /*Set baud rate */
  UBRR0H = (uint8_t)(ubrr_register_value >> 8);
  UBRR0L = (uint8_t)ubrr_register_value;
  /* Enable transmitter */
  UCSR0B = (1 << TXEN0);
  /* Set frame format: 8data, 2stop bit, no parity */
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void usart0_transmit_byte(uint8_t ptr) {
  /* wait for the data buffer to be empty */
  while (!(UCSR0A & (1 << UDRE0))) {
  };
  /* Put data into buffer, sends the data */
  UDR0 = ptr;
}

void usart0_transmit_bytes(uint8_ptr_t ptr) {
  // !!caution!!
  // do not increment pointer directly
  // <op>++ is sugar for <op> += 1;
  uint32_t index = 0;
  while (*(ptr + index)) {
    usart0_transmit_byte(*(ptr + index));
    index++;
  }
}