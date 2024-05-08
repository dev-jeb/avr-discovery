#ifndef AVR_USART_H
#define AVR_USART_H

/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * This module will provide a way to interact with the  USART (Universal
 * Synchronous Asynchronous Receiver Transmitter) module on the atmega328p.
 * USART has the capabilities to communicate both synchronously and
 * asynchronously. It can do everything a UART can do and more.
 *
 * @important_notes:
 * when using the USART module, it is up to you to do the following:
 * 1. Use the table in the datasheet to determine the value to be written to the
 * UBRRnH:L register to set the baud rate. Here we default to 9600 baud rate
 * assuming the system clock frequency is 16MHz. From the datasheet UBRRnH:L =
 * 103. Pass the determined value to the usart0_init macro.
 *
 * @bugs: This module has a known bug. See /projects/bigBug/main.c for more
 * information.
 */

#include "avr-arch.h"
#include "types.h"

/**
 * @knowledge:
 * Asynchronous Serial Communication (UART) Overview:
 *
 * UART communication does not require the clocks on both devices to be
 * synchronized, but they must agree on communication parameters like baud rate,
 * data bits, stop bits, and parity.
 *
 * UART Transmission Process:
 * 1. Start Bit: Communication begins with a start bit (always low).
 * 2. Data Bits: The actual data (usually 8 bits) are sent after the start bit.
 * 3. Stop Bit(s): One or more stop bits follow the data bits, indicating the
 * end of the byte.
 * 4. Optional Parity Bit: Can be added for error checking (odd or even parity).
 *
 * Baud Rate: Determines the speed of transmission, indicating the number of
 * bits transmitted per second. Both devices must use the same baud rate for
 * successful communication.
 *
 * Asynchronous Nature: There's no shared clock signal; the receiving device
 * synchronizes its internal clock with the incoming data based on the
 * agreed-upon baud rate, allowing effective communication even without
 * synchronized clocks.
 **/

/**
 * Here are some macros that will be useful when working with the USART module.
 * Such as sending special characters.
 */
#define NEW_LINE '\n'
#define CARRIAGE_RETURN '\r'

/**
 * @macro:
 * usart_init
 *
 * @purpose:
 * This function will ensure the USART module is powered.
 * It will set the UBRRnH:L register so the clock pulses at the desired rate
 * (baud rate) rate. It will enable the transmitter. It will set
 * the frame format to 8 data bits, no parity, 2 stop bit.
 *
 *  The TXCn flag can be used to check that the transmitter has completed
 * all transfers. This flag must be cleared before transmitting new data.
 *
 * The RXCn flag can be used to check that there is no unread data in
 * the receive buffer.
 */
#define usart0_init(ubrr_register_value)                                       \
  {                                                                            \
    /*Set baud rate */                                                         \
    UBRR0H = (uint8_t)(ubrr_register_value >> 8);                              \
    UBRR0L = (uint8_t)ubrr_register_value;                                     \
    /* Enable transmitter */                                                   \
    UCSR0B = (1 << TXEN0);                                                     \
    /* Set frame format: 8data, 2stop bit, no parity */                        \
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);                                     \
  }

/**
 * @macro:
 * usart0_transmit_byte
 * @purpose:
 * Asynchronously transmit a byte over the USART0 module.
 * @param: uint8_t data (byte to be serially transmitted)
 */
#define usart0_transmit_byte(data)                                             \
  {                                                                            \
    /* wait for the data buffer to be empty */                                 \
    while (!(UCSR0A & (1 << UDRE0))) {                                         \
    };                                                                         \
    /* Put data into buffer, sends the data */                                 \
    UDR0 = (uint8_t)data;                                                      \
  }

/**
 * @macro:
 * usart0_transmit_bytes
 * @purpose:
 * Asynchronously transmit a string over the USART0 module.
 * @param: uint8_ptr_t *data (pointer to the string to be serially transmitted)
 * @param: uint16_t sz (size of the buffer)
 * @note: This function has a known bug. See /projects/bigBug/main.c for more
 * information.
 */
#define usart0_transmit_bytes(data, sz)                                        \
  {                                                                            \
    for (uint32_t i = 0; i < sz; i++) {                                        \
      /* wait for the data buffer to be empty */                               \
      while (!(UCSR0A & (1 << UDRE0))) {                                       \
      };                                                                       \
      /* Put data into buffer, sends the data */                               \
      UDR0 = *(data + i);                                                      \
    }                                                                          \
  }

#endif // AVR_USART_H