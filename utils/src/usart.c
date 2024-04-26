#include "usart.h"
#include "types.h"

void usart_init() {
  /*Set baud rate */
  UBRR0H |= (uint8_t)(MYUBRR >> 8);
  UBRR0L |= (uint8_t)MYUBRR;
  // Enable receiver and transmitter
  UCSR0B = (1 << TXEN0);
  // Set frame format: 8data, 2stop bit
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void usart_send_char(uint8_t data) {
  // Wait for empty transmit buffer
  while (!(UCSR0A & (1 << UDRE0))) {
  };
  // Put data into buffer, sends the data
  UDR0 = data;
}

void usart_send_string(uint8_ptr_t data) {
  while (*data) {
    usart_send_char(*data++);
  }
}