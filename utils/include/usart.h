#ifndef AVR_USART_H
#define AVR_USART_H

/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * THis module will provide a way to interact with the USART module on the AVR.
 **/

#include "types.h"

/**
 * In UART communication, both the sender (transmitter) and the receiver need to
 * agree on the timing of when bits are sent and received. The baud rate defines
 * the rate at which bits are transmitted/received over the communication
 * channel.
 *
 * When the baud rate is set, it determines the time interval between each bit.
 * For example, at a baud rate of 9600 bps, each bit takes approximately 1 /
 * 9600 seconds (104.17 microseconds) to transmit.
 *
 * The clock signal in UART communication is used to time when the receiver
 * samples the incoming bits. Both the transmitter and the receiver synchronize
 * their clocks based on the baud rate. The transmitter sends bits according to
 * its clock, and the receiver samples these bits at specific intervals
 * determined by its clock, synchronized with the baud rate.
 *
 * So, the clock signal ensures that both the transmitter and receiver are
 * synchronized and sampling bits at the correct times, allowing for successful
 * communication. If the clocks of the transmitter and receiver were not
 * synchronized, or if the baud rates did not match, communication errors would
 * likely occur.
 */
/* Baud Rate Register Value
 * When this is loaded into the UBRRH:L register the USART module will be set to
 * the desired baud rate 9600 when the clock frequency is 8MHz. If you change
 * the clock frequency you will need to recalculate the UBRRn value.
 */
#define F_CPU 16000000L
#define BAUD 9600
#define MYUBRR 103

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
void usart_init();

/**
 * @function:
 * usart_send_char
 *
 * @purpose:
 * Asynchronously transmit a byte over the USART module.
 *
 * @param: uint8_t data (byte to be serially transmitted)
 */
void usart_send_char(uint8_t data);

/**
 * @function:
 * usart_send_string
 *
 * @purpose:
 * Asynchronously transmit a  null terminated string over the USART module.
 *
 * @param: uint8_ptr_t *data (pointer to the string to be serially transmitted)
 */
void usart_send_string(uint8_ptr_t data);

#endif // AVR_USART_H