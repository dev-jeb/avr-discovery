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
 *
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

#include "avr-arch.h"
#include "types.h"

// Power Reduction Register
// ensure USART0 is not powered down
#define PRR *(volatile uint8_t *)0x64
#define PRUSART0 1

/**
 * USART I/O Data Register
 * The USART Transmit Data Buffer Register and USART Receive Data Buffer
 * Registers share the same I/O address referred to as USART Data Register or
 * UDRn. The Transmit Data Buffer Register (TXB) will be the destination for
 * data written to the UDRn Register location. Reading the UDRn Register
 * location will return the contents of the Receive Data Buffer Register (RXB)
 */
#define UDR0 *(volatile uint8_t *)0xC6

// Baud Rate Register High
#define UBRR0H *(volatile uint8_t *)0xC5
// Baud Rate Register Low
#define UBRR0L *(volatile uint8_t *)0xC4

/**
 * USART Control and Status Register 0 A
 */
#define UCSR0A *(volatile uint8_t *)0xC0
// Multi-processor Communication Mode
#define MPCM0 0
// Double the USART Transmission Speed
#define U2X0 1
// USART Parity Error
// always set this bit to zero if you are writing to this register
#define UPE0 2
// Data OverRun
// always set this bit to zero if you are writing to this register
#define DOR0 3
// Frame Error
// always set this bit to zero if you are writing to this register
#define FE0 4
// USART Data Register Empty
#define UDRE0 5
// USART Transmit Complete
#define TXC0 6
// USART Receive Complete
#define RXC0 7

/**
 * USART Control and Status Register 0 B
 */
#define UCSR0B *(volatile uint8_t *)0xC1
// Transmit Data Bit 8
// this is the ninth bit of the received character when using 9-bit data
#define TXB80 0
// Receive Data Bit 8
// this is the ninth bit of the received character when using 9-bit data
#define RXB80 1
// Character Size
// the UCSZn2 bits combined with the UCSZn1:0 bit in UCSRnC sets the number of
// data bits (Character SiZe) in a frame the Receiver and Transmitter use.
#define UCSZ02 2
// Transmitter Enable
#define TXEN0 3
// Receiver Enable
#define RXEN0 4
// USART Data Register Empty Interrupt Enable
#define UDRIE0 5
// TX Complete Interrupt Enable
#define TXCIE0 6
// RX Complete Interrupt Enable
#define RXCIE0 7

/**
 * USART Control and Status Register 0 C
 */
#define UCSR0C *(volatile uint8_t *)0xC2
// Clock Polarity
// This bit is used for synchronous mode only. Write this bit to zero when
// asynchronous mode is used. The UCPOLn bit sets the relationship between data
// output change and data input sample, and the synchronous clock (XCKn)
#define UCPOL0 0
// Character Size
#define UCSZ00 1
#define UCSZ01 2
// Stop Bit Select
#define USBS0 3
// Parity Mode
#define UPM00 4
#define UPM01 5
// USART Mode Select
#define UMSEL00 6
#define UMSEL01 7

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

#endif // AVR_USART_H