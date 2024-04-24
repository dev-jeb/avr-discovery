/**
 * @contact_info:
 * Author: dev_jeb
 * Email: dev_jeb@outlook.com
 *
 * @usage:
 * Ensure you have successfully setup the development container described in the
 * README or ensure you have the necessary tools installed locally on you
 * machine. You can build this lesson using the `make` command
 *
 * @purpose:
 *
 *
 * @project_index:
 *
 * main.c: main lesson file
 *
 * makefile: the makefile for this lesson. This makefile when run with the
 * command `make` produces many different files. These files each give a
 * different view of our program at different stages of the compilation process.
 * They will be invaluable in gaining insight into the structure of our final
 * executable and the steps that were taken to produce it.
 *
 * prog.ld: the linker script (more on this later)
 *
 * prog1.c: this is a C file that will be used to show how we can compile two
 * separate files and then link them together into one executable file
 *
 * The atmega328p gives us a convenient way to trigger software interrupts.
 * We can use the INT0 pin and set it to output. Then we can trigger an
 * interrupt by setting the pin to high. This will be a good exercise
 *
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
  trigger_interrupt_INT0();
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