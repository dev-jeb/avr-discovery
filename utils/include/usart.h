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
 * 1. determine the clock frequency of your controller. (Here I use 16MHz)
 * 1. Use the table in the datasheet to determine the value to be written to the
 * UBRRnH:L register. Here is is 103
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
 * 3. Optional Parity Bit: Can be added for error checking (odd or even parity).
 * 4. Stop Bit(s): One or more stop bits follow the data bits, indicating the
 *    end of the byte.
 **/

#define NEW_LINE '\n'
#define CARRIAGE_RETURN '\r'
// !!this is not a uint8_t!!
// use usartn_transmit_bytes(&CLEAR_SCREEN)
#define CLEAR_SCREEN "\033[2J"

/**
 * @function:
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
 **/
void usart0_init(uint16_t ubrr_register_value);

/**
 * @function:
 * usart0_transmit_byte
 * @purpose:
 * Asynchronously transmit a byte over the USART0 module.
 * @param: byte to transmit
 */
void usart0_transmit_byte(uint8_t data);

/**
 * @function:
 * usart0_transmit_bytes
 * @purpose:
 * Asynchronously transmit a null terminated sequence of bytes over the USART0
 * module.
 * @param: pointer to data
 * @note: undefined behaviour when terminator not present
 */
void usart0_transmit_bytes(uint8_ptr_t ptr);

#endif // AVR_USART_H