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
 * This lesson serves as an exploration of the avr-gcc compilation
 * pipeline. Starting with an arbitrary program, we will see how the compilation
 * pipeline (pre-processor, compiler, assembler, and linker) work together to
 * produce an executable file that can be flashed to our microcontroller
 * (atmega328p). We are particularly interested in how the linker handles
 * relocatable object files produced by the pre-processor -> compiler ->
 * assembler sequence to a final executable file that can be flashed to our
 * microcontroller.
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
 * @memory_intro:
 * First we need to talk about the different kinds of memory that are available
 * to us on the atmega328p microcontroller. This is important as these different
 * types of memory serve different functions within the microcontroller. We can
 * split the memory available to us into two broad catagories.
 *
 * @volatile_memory: memory that loses its contents when the power is turned
 * off. The static random access memory (sram) in the microcontroller falls into
 * this category.
 *
 * @non_volatile_memory: memory that retains its contents when the power is
 * turned off. The flash memory and the electrically erasable programable
 * read-only memory (EEPROM) fall into this category.
 *
 * Take a moment to think about the consequences of the above definitions. When
 * the microcontroller is powered off, the contents of the sram are lost. What
 * would happen if this were the only memory available to us on the
 * microcontroller? This would mean that all the machine code that represents
 * our programs instructions and data would not persist. We would need to
 * upload our program to the microcontroller every time we wanted to run it.
 *
 * What would happen if we only had non-volatile memory available to us? To
 * answer this you would need to know some common characteristics of
 * non-volatile memory.
 * - non-volatile memory is typically slower than volatile memory (takes longer
 * to read/write from/to).
 * - non-volatile memory is typically used to store large amounts of data that
 * is not accessed as frequently as the data stored in volatile memory.
 * - non-volatile memory has a limited number of write cycles, i.e. you can only
 * write to it a certain number of times before it becomes unreliable.
 * - non-volatile memory is often not byte addressable, i.e. you can't read or
 * write a single byte of data to it. You must read or write a block of data
 * at a time.
 *
 * With the definition/characteristics of volatile and non-volatile memory in
 * mind, we can see no explore the memory available to us on the atmega328p
 * microcontroller.
 *
 * @flash_memory:
 * The flash on an atmega328p is 32KB in size where 1KB equals 1024 bytes.
 *
 * flash size (bytes)     : 32768
 * flash size (words)     : 16384
 * flash page size (bytes): 128
 * flash pages            : 256
 * flash endurance        : 10000 write/erase cycles
 *
 * @note:
 * All AVR instructions are 16 or 32 bits wide, therefore the flash memory is
 * organized into 16-bit words. This is an example of non-volatile memory not
 * being byte addressable. The program counter (PC) in the microcontroller is 14
 * bits wide, therefore we can address 2^14 = 16,384 words of memory. If we
 * wanted to address every byte in the flash memory only using the program
 * counter we would need a 15-bit wide program counter.
 *
 * @flash_diagram:
 *                   FLASH
 * 0x0000 |--------------------------|
 *        |   byte 1   |   byte 2    |
 * 0x0002 |--------------------------|
 *        |           ...            |
 *        |           ...            |
 *        ~           ...            ~
 *        ~           ...            ~
 *        |           ...            |
 *        |           ...            |
 *        |           ...            |
 *        |           ...            |
 * 0x3ffe |--------------------------|
 *
 * @sram_memory:
 * The sram on an atmega328p is 2KB in size where 1KB equals 1024 bytes.
 *
 * sram size (bytes)       : 2048
 *
 * @note:
 * above we have stated that there are 2048 bytes of sram available to us but
 * when looking at the datasheet we see the address space for sram goes
 * from [0x0000, 0x08FF] which means there are 2304 addressable bytes available
 * to us. So where do the extra 256 bytes come from? This is an abstraction that
 * the microcontroller presents to us. Only the address interval [0x0060,
 * 0x08FF] is actual physical (hardware) sram. The address interval [0x0000,
 * 0x005F] is an abstraction that the microcontroller presents to us. This
 * abstraction is used to access the general working registers and i\o registers
 * of the microcontroller. The register file and i/o registers are not
 * implemented in hardware as sram. However, the microcontroller presents them
 * to us as if they were. Therefore the address interval [0x0000, 0x00FF] is
 * reserved for the register file, non sram i/o registers and sram external i/o
 * registers.
 *
 * @sram_diagram:
 *                   sram
 * 0x0000 |--------------------------|
 * 0x0001 |                          |
 *        |      32 x 8 registers    |
 *        |                          |
 * 0x0020 |--------------------------|
 *        |                          |
 *        |   64 x 8 i\o registers   |
 *        |                          |
 * 0x0060 |--------------------------|
 *        |                          |
 *        |160 x 8 ext i\o registers |
 *        |                          |
 * 0x0100 |--------------------------|
 *        |           ...            |
 *        |           ...            |
 *        ~           ...            ~
 *        ~           ...            ~
 *        |           ...            |
 *        |           ...            |
 * 0x08ff |--------------------------|
 *
 * @eeprom_memory:
 * @note:
 * @eeprom_diagram:
 *
 * @memory_layout:
 * Now we will start by describing what our final program should look like when
 * executing on our microcontroller. From this definition we will work to
 * achieve this layout using the compilation pipeline.
 *
 *                   FLASH
 * 0x0000 |--------------------------|
 *        |    Prog1 (.prog1_text)   |
 * 0x0002 |                          |
 *        |   byte 1   |   byte 2    |
 *        |--------------------------|
 *        |           ...            |
 *        |           ...            |
 * 0x1000 |--------------------------|
 *        |    Prog2 (.prog2_text)   |
 *        |           ...            |
 *        |           ...            |
 *        |           ...            |
 * 0x2000 |--------------------------|
 *        |           ...            |
 *        |           ...            |
 *        |           ...            |
 *        |           ...            |
 * 0x3000 |--------------------------|
 *        |           ...            |
 *        |           ...            |
 *        |           ...            |
 *        |           ...            |
 * 0x3ffe |--------------------------|
 *
 *
 * sram_size (bytes): 2,048
 * sram_page_size (bytes): 256
 *
 *                    sram
 * 0x0000 |--------------------------|
 * 0x0001 |                          |
 *        |      32 x 8 registers    |
 *        |                          |
 * 0x0020 |--------------------------|
 *        |                          |
 *        |   64 x 8 i\o registers   |
 *        |                          |
 * 0x0060 |--------------------------|
 *        |                          |
 *        |160 x 8 ext i\o registers |
 *        |                          |
 * 0x0100 |--------------------------|_data_start
 *        |           ...            |
 *        |       .data + .bss       |
 *        |           ...            |
 *        |--------------------------|_data_end
 *        |           ...            |
 *        |           ...            |
 *        |           ...            |
 *        |           ...            |
 * 0x08ff |--------------------------|_stack_start
 *
 * @observations:
 * 1. invariant: (stack_end - heap_end) > 0 otherwise a collision has occurred
 *
 * @object_file:
 * an object file is a file that is produced at multiple levels of the
 * compilation process. An object file prior to linking is called a relocatable
 * object file. This file contains machine code split into sections where each
 * section is a contiguous block of memory
 *
 * @sections:
 * The compiler will place different kinds of data in different sections of the
 * object file. When we go to link object files together into one executable
 * file these sections will be combined into the final memory layout of the
 * microcontroller. THe linker gives us the ability to control where these
 * sections are placed in the final memory layout.
 *
 * since this is an uninitialized global variable, it will be stored in the
 * BSS section of the compiler produced object files. This byte and all other
 * bytes that get put into the BSS section will be loaded from flash to RAM
 * prior to the main function being called. This is done by the c runtime.
 */
#include "types.h"
// initalized variable are stored in the data section of the object file
uint8_t i_live_in_prog1_data = 0xAA;

// uninitialized variables are stored in the BSS section of the object file
uint8_t i_live_in_prog1_bss;

void main() {
  i_live_in_prog1_bss = 0xCC;
  // we must have a runtime stack to store local variables
  uint8_t i_live_on_prog1_stack = 0xBB;
}

/**
 * NOTE:
 * I am verifying the functionality by running this program on an emulated AVR
 * microcontroller (simavr). Then I connect avr-gdb to the simavr instance and
 * set a breakpoint at the main function. I then step through the program to
 * verify that the EEPROM functions are working as expected. I do this by
 * watching the register values change as I step through the program. Look at
 * the README to find out how to setup this workflow.
 */