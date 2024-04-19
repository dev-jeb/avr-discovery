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
uint8_t i_live_in_the_bss_section;
void __vector_1(void) { i_live_in_the_bss_section = 0x03; }

int main(void) {
  // Set the INT0 pin as output
  // Set the INT0 pin to high

  while (1) {
    // Do nothing
  }

  return 0;
}