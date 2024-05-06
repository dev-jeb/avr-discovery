#ifndef AVR_ARCH_H
#define AVR_ARCH_H

/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * This module will define the AVR architecture and gives us a
 * more structured way to interact with the microcontroller.
 **/

#include "types.h"

/**
 * 32 x 8 General Purpose Working Registers
 * R0-R31
 */

/**
 * scratch register. This register is used by the compiler for temporary storage
 * therefore this value must be saved before jumping to an interrupt service
 * routine and restored before returning from the interrupt service routine.
 */
#define R0 *(volatile uint8_t *)0x00
/**
 * must always be zero. Sometimes used as temporary register therefore
 * ISR must save,set 0, and restore
 **/
// (call saved)
#define R1 *(volatile uint8_t *)0x01
// (call saved)
#define R2 *(volatile uint8_t *)0x02
// (call saved)
#define R3 *(volatile uint8_t *)0x03
// (call saved)
#define R4 *(volatile uint8_t *)0x04
// (call saved)
#define R5 *(volatile uint8_t *)0x05
// (call saved)
#define R6 *(volatile uint8_t *)0x06
// (call saved)
#define R7 *(volatile uint8_t *)0x07
// (call saved)
#define R8 *(volatile uint8_t *)0x08
// (call saved)
#define R9 *(volatile uint8_t *)0x09
// (call saved)
#define R10 *(volatile uint8_t *)0x0A
// (call saved)
#define R11 *(volatile uint8_t *)0x0B
// (call saved)
#define R12 *(volatile uint8_t *)0x0C
// (call saved)
#define R13 *(volatile uint8_t *)0x0D
// (call saved)
#define R14 *(volatile uint8_t *)0x0E
// (call saved)
#define R15 *(volatile uint8_t *)0x0F
// (call saved)
#define R16 *(volatile uint8_t *)0x10
// (Call saved)
#define R17 *(volatile uint8_t *)0x11
// (call clobbered)
#define R18 *(volatile uint8_t *)0x12
// (call clobbered)
#define R19 *(volatile uint8_t *)0x13
// (call clobbered)
#define R20 *(volatile uint8_t *)0x14
// (call clobbered)
#define R21 *(volatile uint8_t *)0x15
// (call clobbered)
#define R22 *(volatile uint8_t *)0x16
// (call clobbered)
#define R23 *(volatile uint8_t *)0x17
// (call clobbered)
#define R24 *(volatile uint8_t *)0x18
// (call clobbered)
#define R25 *(volatile uint8_t *)0x19
// X register low byte
// (call clobbered)
#define R26 *(volatile uint8_t *)0x1A
// X register high byte
// (call clobbered)
#define R27 *(volatile uint8_t *)0x1B
// Y register low byte
// (call saved)
#define R28 *(volatile uint8_t *)0x1C
// Y register high byte
// (call saved)
#define R29 *(volatile uint8_t *)0x1D
// Z register low byte
// (call clobbered)
#define R30 *(volatile uint8_t *)0x1E
// Z register high byte
// (call clobbered)
#define R31 *(volatile uint8_t *)0x1F

/**
 * Status Register
 */
#define SREG *(volatile uint8_t *)0x5F
// carry flag
#define SREG0 0
// zero flag
#define SREG1 1
// negative flag
#define SREG2 2
// two's complement overflow flag
#define SREG3 3
// signed test flag
#define SREG4 4
// half carry flag
#define SREG5 5
// Scratch bit
// (call clobbered)
// must be saved, restored for interrupts
#define SREG6 6
// global interrupt enable
#define SREG7 7

// External Interrupt Control Register A
#define EICRA *(volatile uint8_t *)0x69
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

// External Interrupt Mask Register
#define EIMSK *(volatile uint8_t *)0x3D
#define INT0 0
#define INT1 1

// PORTD Data Register
#define PORTD *(volatile uint8_t *)0x2B
#define PORTD0 0
#define PORTD1 1
#define PORTD2 2
#define PORTD3 3
#define PORTD4 4
#define PORTD5 5
#define PORTD6 6
#define PORTD7 7

// PORTD data direction register
#define DDRD *(volatile uint8_t *)0x2A
#define DDD0 0
#define DDD1 1
#define DDD2 2
#define DDD3 3
#define DDD4 4
#define DDD5 5
#define DDD6 6
#define DDD7 7

// Port D Input Pins Address
#define PIND *(volatile uint8_t *)0x29
#define PIND0 0
#define PIND1 1
#define PIND2 2
#define PIND3 3
#define PIND4 4
#define PIND5 5
#define PIND6 6
#define PIND7 7

/**
 * uart0
 */
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

#endif // AVR_ARCH_H