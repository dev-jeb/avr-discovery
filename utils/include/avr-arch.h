#ifndef AVR_ARCH_H
#define AVR_ARCH_H
#endif

#include "types.h"

/**
 * here we will define the default clock speed of the atmega328p
 */
#define F_CPU 8000000UL

/**
 * avr defined interrupt vectors
 */
#define INT0_vect __vector_1
#define INT1_vect __vector_2
#define PCINT0_vect __vector_3
#define PCINT1_vect __vector_4
#define PCINT2_vect __vector_5
#define WDT_vect __vector_6
#define TIMER2_COMPA_vect __vector_7
#define TIMER2_COMPB_vect __vector_8
#define TIMER2_OVF_vect __vector_9
#define TIMER1_CAPT_vect __vector_10
#define TIMER1_COMPA_vect __vector_11
#define TIMER1_COMPB_vect __vector_12
#define TIMER1_OVF_vect __vector_13
#define TIMER0_COMPA_vect __vector_14
#define TIMER0_COMPB_vect __vector_15
#define TIMER0_OVF_vect __vector_16
#define SPI_STC_vect __vector_17
#define USART_RX_vect __vector_18
#define USART_UDRE_vect __vector_19
#define USART_TX_vect __vector_20
#define ADC_vect __vector_21
#define EE_RDY_vect __vector_22
#define ANA_COMP_vect __vector_23
#define TWI_vect __vector_24
#define SPM_RDY_vect __vector_25

/**
 * macro to define an interrupt service routine
 *@param vector: interrupt vector to decalre ISR for
 */
#define ISR(vector) void vector(void)

/**
 * 32 x 8 General Purpose Working Registers
 * R0-R31
 */
/**
 * scratch register (need not be restored after use)
 * must store before ISR and restore after ISR
 */
#define R0 *(volatile uint8_t *)0x00
/**
 * must always be zero. Sometimes used as temporary register therefore
 * ISR must save,set 0, and restore
 **/
#define R1 *(volatile uint8_t *)0x01
#define R2 *(volatile uint8_t *)0x02
#define R3 *(volatile uint8_t *)0x03
#define R4 *(volatile uint8_t *)0x04
#define R5 *(volatile uint8_t *)0x05
#define R6 *(volatile uint8_t *)0x06
#define R7 *(volatile uint8_t *)0x07
#define R8 *(volatile uint8_t *)0x08
#define R9 *(volatile uint8_t *)0x09
#define R10 *(volatile uint8_t *)0x0A
#define R11 *(volatile uint8_t *)0x0B
#define R12 *(volatile uint8_t *)0x0C
#define R13 *(volatile uint8_t *)0x0D
#define R14 *(volatile uint8_t *)0x0E
#define R15 *(volatile uint8_t *)0x0F
#define R16 *(volatile uint8_t *)0x10
#define R17 *(volatile uint8_t *)0x11
// call clobbered
#define R18 *(volatile uint8_t *)0x12
// call clobbered
#define R19 *(volatile uint8_t *)0x13
// call clobbered
#define R20 *(volatile uint8_t *)0x14
// call clobbered
#define R21 *(volatile uint8_t *)0x15
// call clobbered
#define R22 *(volatile uint8_t *)0x16
// call clobbered
#define R23 *(volatile uint8_t *)0x17
// call clobbered
#define R24 *(volatile uint8_t *)0x18
// call clobbered
#define R25 *(volatile uint8_t *)0x19
// call clobbered
// X register low byte
#define R26 *(volatile uint8_t *)0x1A
// call clobbered
// X register high byte
#define R27 *(volatile uint8_t *)0x1B
// Y register low byte
#define R28 *(volatile uint8_t *)0x1C
// Y register high byte
#define R29 *(volatile uint8_t *)0x1D
// call clobbered
// Z register low byte
#define R30 *(volatile uint8_t *)0x1E
// call clobbered
// Z register high byte
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
/**
 * bit copy storage
 * used like r0, a tmp register therefore must be saved before ISR and restored
 * after ISR
 */
#define SREG6 6
// global interrupt enable
#define SREG7 7

// external interrupt control register A
#define EICRA *(volatile uint8_t *)0x69
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

// External Interrupt Mask Register
#define EIMSK *(volatile uint8_t *)0x3D
#define INT0 0
#define INT1 1

// define the PORTD Data Register
#define PORTD *(volatile uint8_t *)0x2B
#define PORTD0 0
#define PORTD1 1
#define PORTD2 2
#define PORTD3 3
#define PORTD4 4
#define PORTD5 5
#define PORTD6 6
#define PORTD7 7

// Define PORTD data direction register
#define DDRD *(volatile uint8_t *)0x2A
#define DDD0 0
#define DDD1 1
#define DDD2 2
#define DDD3 3
#define DDD4 4
#define DDD5 5
#define DDD6 6
#define DDD7 7

// Define Port D Input Pins Address
#define PIND *(volatile uint8_t *)0x29
#define PIND0 0
#define PIND1 1
#define PIND2 2
#define PIND3 3
#define PIND4 4
#define PIND5 5
#define PIND6 6
#define PIND7 7

#ifdef __cplusplus
#define __always_inline inline __attribute__((always_inline))
#else
#define __always_inline static inline __attribute__((always_inline))
#endif

__always_inline void cli() { asm volatile("cli"); }

__always_inline void sei() { asm volatile("sei"); }

__always_inline void push(uint8_t data) {
  asm volatile("PUSH %0" : : "r"(data));
}

__always_inline uint8_t pop() {
  uint8_t data;
  asm volatile("POP %0" : "=r"(data));
  return data;
}
