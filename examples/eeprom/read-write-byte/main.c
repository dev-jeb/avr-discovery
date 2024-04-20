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
 * this program demonstrates how to read and write a byte to the EEPROM using
 * the EEPROM functions described in `eeprom.h`.
 */
#include "eeprom.h"

/**
 * here we are storing a byte in the EEPROM. It will be stored as the first
 * byte. This is because I have added the ".eeprom" attribute through a macro
 * defined in eeprom.h. The avr-gcc compiler understands this attribute and will
 * place the variable in the EEPROM section of the object file.
 */
uint8_t EEPROM im_the_first_byte_in_eeprom = 0xCC;

void main() {
  // we can read a byte from the EEPROM. This will read the first byte (0xCC)
  uint8_t data = eeprom_read_byte((ptr_uint8_t)0x00);
  // we can write a byte to the EEPROM (0xAA)
  eeprom_write_byte((ptr_uint8_t)0x01, 0xAA);
  // we can read a byte from the EEPROM (0xCC)
  data = eeprom_read_byte((ptr_uint8_t)0x00);
  // and read (0xAA) from the EEPROM
  data = eeprom_read_byte((ptr_uint8_t)0x01);
  // we store 0xAA in the second general purpose register.
  R2 = data;
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