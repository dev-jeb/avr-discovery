#include "avr-arch.h"
#include "common.h"
#include "types.h"

/**
 * @function:
 * interrupt prologue/epilogue
 *
 * @implementation:
 * The interrupt prologue is a sequence of operations that must be performed
 * before we jump to the interrupt service routine. When an interrupt occurs our
 * microcontroller was probably doing something. Maybe executing another
 * function. This function has a state which is the set of registers that are
 * being used by the function. We dont know exactly what registers a function
 * will be using but per the specification of the compiler we must assume that
 * the following register are being used by the function.
 *
 * R0, R1, R18-27, R28, R29
 * The T flag in the status register
 *
 * and since the ISR is another avr-gcc compiled function we must assume that it
 * will use some of the registers. Therefore, we must save the state of these
 * registers prior to the ISR and then restore them after the ISR. That way we
 * are in the state prior to the interrupt.
 *
 * These two functions will be declared static so that their symbols are not
 * definable by other object file inout sections
 *
 */
static void interrupt_prologue() {
  // Save the status register to a temporary variable
  uint8_t temp = SREG;
  // Disable global interrupts
  DISABLE(SREG, SREG7);
  // Save the state of the registers
  R2 = R0;
  R3 = R1;
  R4 = R18;
  R5 = R19;
  R6 = R20;
  R7 = R21;
  R8 = R22;
  R9 = R23;
  R10 = R24;
  R11 = R25;
  R12 = R26;
  R13 = R27;
  R14 = R30 R15 = R31;
};

static void interrupt_epilogue() {
  // Restore the state of the registers
  R0 = R2;
  R1 = R3;
  R18 = R4;
  R19 = R5;
  R20 = R6;
  R21 = R7;
  R22 = R8;
  R23 = R9;
  R24 = R10;
  R25 = R11;
  R26 = R12;
  R27 = R13;
  R30 = R14;
  R31 = R15;
  // Restore the status register
  SREG = temp;
};

void trigger_interrupt_INT0() {
  // interrupt prologue
  interrupt_prologue();
  // Enable global interrupts
  sei();
  // set PD2 as output
  ENABLE(DDRD, DDD2);
  // Enable INT0 interrupt
  ENABLE(EIMSK, INT0);
  // Set INT0 to trigger on toggle
  ENABLE(EICRA, ISC00);
  DISABLE(EICRA, ISC01);
  // Toggle PD2 pin
  TOGGLE(PORTD, PORTD2);
  // Disable INT0 interrupt
  DISABLE(EIMSK, INT0);
  // interrupt epilogue
  interrupt_epilogue();
};

void trigger_interrupt_INT0_1arg(uint8_ptr_t arg1) {
  // interrupt prologue
  interrupt_prologue();
  // Pass arg1 to interrupt handler in R17
  R16 = *arg1;
  // Enable global interrupts
  sei();
  // set PD2 as output
  ENABLE(DDRD, DDD2);
  // Enable INT0 interrupt
  ENABLE(EIMSK, INT0);
  // Set INT0 to trigger on toggle
  ENABLE(EICRA, ISC00);
  DISABLE(EICRA, ISC01);
  // Toggle PD2 pin
  TOGGLE(PORTD, PORTD2);
  // Disable INT0 interrupt
  DISABLE(EIMSK, INT0);
  // interrupt epilogue
  interrupt_epilogue();
};