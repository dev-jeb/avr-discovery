#ifndef AVR_ARCH_H
#define AVR_ARCH_H
#endif

#include "types.h"

/**
 * 32 x 8 General Purpose Working Registers
 * R0-R31
 */
#define R0 *(volatile uint8_t *)0x00
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
#define R18 *(volatile uint8_t *)0x12
#define R19 *(volatile uint8_t *)0x13
#define R20 *(volatile uint8_t *)0x14
#define R21 *(volatile uint8_t *)0x15
#define R22 *(volatile uint8_t *)0x16
#define R23 *(volatile uint8_t *)0x17
#define R24 *(volatile uint8_t *)0x18
#define R25 *(volatile uint8_t *)0x19
// X register low byte
#define R26 *(volatile uint8_t *)0x1A
// X register high byte
#define R27 *(volatile uint8_t *)0x1B
// Y register low byte
#define R28 *(volatile uint8_t *)0x1C
// Y register high byte
#define R29 *(volatile uint8_t *)0x1D
// Z register low byte
#define R30 *(volatile uint8_t *)0x1E
// Z register high byte
#define R31 *(volatile uint8_t *)0x1F

// define status register
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
// bit copy storage
#define SREG6 6
// global interrupt enable
#define SREG7 7

#ifdef __cplusplus
#define __always_inline inline __attribute__((always_inline))
#else
#define __always_inline static inline __attribute__((always_inline))
#endif

__always_inline void cli() { asm volatile("cli"); }

__always_inline void sei() { asm volatile("sei"); }
