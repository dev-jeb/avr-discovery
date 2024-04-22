/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
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
 * turned off. Both the flash memory and the electrically erasable programable
 * read-only memory (EEPROM) fall into this category.
 *
 * Take a moment to think about the consequences of the above definitions. When
 * the microcontroller is powered off, the contents of the SRAM is lost. What
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
 * mind, we can now explore the memory available to us on the atmega328p
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
 * The SRAM on an atmega328p is 2KB in size where 1KB equals 1024 bytes.
 *
 * SRAM size (bytes)       : 2048
 *
 * @note:
 * above we have stated that there are 2048 bytes of SRAM available to us but
 * when looking at the datasheet we see the address space for SRAM goes
 * from [0x0000, 0x08FF] which means there are 2304 addressable bytes available
 * to us. So where do the extra 256 bytes come from? This is an abstraction that
 * the microcontroller presents to us. Only the address interval [0x0060,
 * 0x08FF] is actual physical (hardware) SRAM. The address interval [0x0000,
 * 0x005F] is not implemented by SRAM hardware. This abstraction is used to
 * access the general working registers and i\o registers of the
 * microcontroller.
 *
 * @sram_diagram:
 *                   SRAM
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
 *        |    (.main_text + crt)    |
 *        |           ...            |
 *        |           ...            |
 *        |           ...            |
 * 0x1000 |--------------------------|
 *        |    (.prog2_main_text)    |
 *        |           ...            |
 *        |           ...            |
 *        |           ...            |
 * 0x2000 |--------------------------|
 *        |         .rodata          |
 *        |     (prog1 & prog2)      |
 *        |           ...            |
 *        |           ...            |
 * 0x3000 |--------------------------|
 *        |      .data + .bss        |
 *        |     (prog1 & prog2)      |
 *        |           ...            |
 *        |           ...            |
 * 0x3ffe |--------------------------|
 *
 * main.c will have the following sections:
 * - .main_text: stack variables, function code
 * - .data: one global variable that is initialized and one static global that
 * is initialized.
 * - .bss: one global variable that is not initialized
 * -rodata: one global variable that is const
 *
 * prog1.c will have the following sections:
 * - .prog1_main_text: function code
 * - .data: one global variable that is initialized and one static global that
 * is initialized.
 * - .bss: one global variable that is not initialized
 * -rodata: one global variable that is const
 *
 *
 *
 *                    SRAM
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
 *        |       .data + .bss       |
 *        |      (prog1 & prog2)     |
 *        |            ...           |
 *        |--------------------------|_data_end
 *        |            ...           |
 *        |            ...           |
 *        |            ...           |
 *        |           stack          |
 * 0x08ff |--------------------------|_stack_start
 *
 *
 * @object_file:
 * an object file is a file that is produced at multiple levels of the
 * compilation process. The assembler and linker are the producers of
 * object files. The compiler simply produces an assembly file from the source
 * code and passes it off to the assembler. An object file before linking is
 * know as relocatable. After linking you have an executable. These object files
 * will contain among other things the machine code broken up into sections. The
 * compiler outputs different `types of instructions` into different sections.
 * Each section has some attributes. These attributes are important as they tell
 * us if the machine code found in this section is executable, read-only,
 * writable, ..., allocatable. We can use the linker to put sections in
 * different parts of memory. For example machine code in the data section and
 * bss section is writable. This means the data needs to live in SRAM so we can
 * quickly and efficiently read and write to it. Machine code in the text
 * section is read-only. This means it can live in flash memory. We will explore
 * these sections in more detail.
 *
 *  @task:
 *  Build this lesson and use `avr-objdump -D object_file` to explore some
 *  object files. Use `avr-readelf -a object_file` to see other information.
 *  Notice that main.elf is an executable object file and it is our output.
 *  Note some differences between the relocatable object files and the
 *  executable object file.
 *
 * @sections:
 * The compiler will place different kinds of data in different sections of the
 * object file. When we go to link object files together into one executable
 * file these sections will be combined into the final memory layout of the
 * microcontroller. The linker gives us the ability to control where these
 * sections are placed in the final memory layout.
 *
 * since this is an uninitialized global variable, it will be stored in the
 * BSS section of the compiler produced object files. This byte and all other
 * bytes that get put into the BSS section will be loaded from flash to RAM
 * prior to the main function being called. This is done by the c runtime.
 */
#include "types.h"
/**
 * @data_section:
 * The data section of the object file is where initialized global variables are
 * as well as static variables that are initialized.
 */
uint8_t i_live_in_prog1_data = 0xAA;
static uint8_t i_live_in_prog1_data_static = 0xBB;

// what happens to a const variable in the data section?
const uint8_t i_am_a_const = 0xDD;

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