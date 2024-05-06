#include "usart.h"
#include "avr-arch.h"
#include "types.h"

void usart0_init(uint16_t ubrr_register_value) {
  /*Set baud rate */
  UBRR0H = (uint8_t)(ubrr_register_value >> 8);
  UBRR0L = (uint8_t)ubrr_register_value;
  // Enable transmitter
  UCSR0B = (1 << TXEN0);
  // Set frame format: 8data, 2stop bit
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void usart0_transmit_byte(uint8_t data) {
  // Wait for empty transmit buffer
  while (!(UCSR0A & (1 << UDRE0))) {
  };
  // Put data into buffer, sends the data
  UDR0 = data;
}

void usart0_transmit_string(uint8_ptr_t data) {
  while (*data != '\0') {
    usart0_transmit_byte(*data);
    data += 1;
  }
}

void usart0_transmit_version(void) {
  extern uint8_t __crt_version_string;
  usart0_transmit_string((uint8_ptr_t)&__crt_version_string);
}

void usart0_transmit_bytes(uint8_ptr_t buf, uint16_t sz) {
  for (uint16_t i = 0; i < sz; i++) {
    usart0_transmit_byte(buf[i]);
  }
};