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
 * 1. Set the system clock frequency (__F_CPU) in the runtime
 * environment to the actual frequency of the system clock.
 * You can do this in crt.s on line 233. You will need to rebuild that file
 * and then you can build the project. In version 1.2 the system clock
 * frequency is set to 16MHz.
 * 2. Use the table in the datasheet to determine the value to be written to the
 * UBRRnH:L register to set the baud rate. Here we default to 9600 baud rate
 * assuming the system clock frequency is 16MHz. From the datasheet UBRRnH:L =
 * 103
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
#define TAB '\t'

/**
 * @macro:
 * USART0_CLEAR_SCREEN
 *
 * @purpose:
 * This function will clear the screen of the terminal.
 */
#define USART0_CLEAR_SCREEN usart0_transmit_string((uint8_ptr_t) "\033[2J")

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
 */
void usart0_init(uint16_t ubrr_regiser_value);

/**
 * @function:
 * usart0_transmit_byte
 *
 * @purpose:
 * Asynchronously transmit a byte over the USART0 module.
 *
 * @param: uint8_t data (byte to be serially transmitted)
 */
void usart0_transmit_byte(uint8_t data);

/**
 * @function:
 * usart_send_string
 *
 * @purpose:
 * Asynchronously transmit a  null terminated string over the USART module.
 *
 * @param: uint8_ptr_t *data (pointer to the string to be serially transmitted)
 */
void usart0_transmit_string(uint8_ptr_t data);

/**
 * @function:
 * usart0_transmit_version
 *
 * @purpose:
 * Transmit the version of the crt.s used to compile the program.
 */
void usart0_transmit_version(void);

/**
 * @function:
 *
 */
void usart0_transmit_bytes(uint8_ptr_t buf, uint16_t sz);

#endif // AVR_USART_H