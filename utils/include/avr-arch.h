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
 * Here we define some inline functions.
 */

// clear the global interrupt enable bit
static inline __attribute__((always_inline)) void cli() { asm volatile("cli"); }

// set the global interrupt enable bit
static inline __attribute__((always_inline)) void sei() { asm volatile("sei"); }

#endif // AVR_ARCH_H