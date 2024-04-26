/**
 * @contact_info:
 * Author: dev_jeb
 * Email: dev_jeb@outlook.com

 * @purpose:
 * This lesson will show how to trigger a software interrupt on the AVR.
 * This gives us the ability to do some interesting things down the line
 */

#include "avr-arch.h"
#include "interrupt.h"
#include "types.h"

/**
 * Remember that we defined a weak symbol (__vector_n with n being a positive
 * integer) in crt.s for all the interrupt handlers (minus reset). We can define
 * our own interrupt handler for INT0 (__vector_1) by defining that symbol and
 * the linker will resolve the symbol to our address instead of the
 * __bad_interrupt symbol.
 *
 * We will check to see if our interrupt handler is being called by writing a
 * magic value (0x03) to the i_live_in_the_bss_section variable.
 */

/**
 * Here we will trigger an internal interrupt by calling the
 * trigger_interrupt_INT0 function declared in interrupt.h. We will define an
 * interrupt handler for INT0 in this file and check if it is being called by
 * incrementing the i_live_in_the_data_section variable. When we build this we
 * should see the INT0 entry in the vector table pointing to this function
 */
uint8_t i_live_in_the_data_section = 0x00;

ISR(INT0_vect) { i_live_in_the_data_section++; }

int main(void) {
  // Trigger the interrupt
  interrupt_trigger_int0();
  return 0;
}

/**
 * @note:
 * when running this in avr-gdb whenever the interrupt is triggered gdb seems to
 * enter an infinite loop and * never return. However, the interrupt is being
 * triggered and the ISR is being called. I know this because * we can see the
 * value of i_live_in_the_data_section incrementing in the data section of the
 * elf file. Maybe someone has an explanation?
 */