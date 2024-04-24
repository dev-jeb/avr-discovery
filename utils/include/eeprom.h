#ifndef AVR_EEPROM_H
#define AVR_EEPROM_H
#endif

#include "avr-arch.h"
#include "types.h"

/**
 * macro to specify the value should be stored in EEPROM.  THis attribute is
 * understood implicitly by the avr-gcc compiler. You can inspect the map file
 * to verify that the variable is stored in the EEPROM section.
 */
#define EEPROM __attribute__((section(".eeprom")))

/**
 * NOTE: possibly use for error checking in the EEPROM functions.
 */
// EEPROM start address
#define EEPROM_START_ADDR 0x00
// EEPROM end address
#define EEPROM_END_ADDR 0x3FF

/**
 * EEPROM address register
 */
#define EEARL *(volatile uint8_t *)0x41
#define EEARH *(volatile uint8_t *)0x42

/**
 * macros to set the EEPROM address. Notice how these are cast to uint8_t.
 * No matter the input to our macro we will only take the lower 8 bits
 * and intepret them unsigned.
 */
#define eeprom_set_addr(addr)                                                  \
  EEARL = (uint8_t)(*(uint16_ptr_t)addr & 0xFF);                               \
  EEARH = (uint8_t)((*(uint16_ptr_t)addr >> 8) & 0x03);

/**
 * EEPROM data register
 * This register contains the data to be written to the EEPROM or the data read
 * from the EEPROM
 */
#define EEDR *(volatile uint8_t *)0x40

/**
 * macro to set the EEPROM data
 */
#define eeprom_set_data(data) EEDR = (uint8_t)data;

/**
 * EEPROM control register
 * This register contains the control bits for the EEPROM
 */
#define EECR *(volatile uint8_t *)0x3F
// EEPROM read strobe
#define EERE 0
// EEPROM write strobe
#define EEPE 1
// EEPROM master write enable
#define EEPME 2
// EEPROM ready interrupt enable
#define EERIE 3
// EEPROM programming mode select
#define EEPM0 4
// EEPROM programming mode select
#define EEPM1 5

/**
 * macro to check if the eeprom is ready to be written to.
 * The EEPE bit is cleared by hardware when the write operation is completed,
 * therefore this macro returns 1 when busy and 0 when ready.
 */
#define eeprom_busy() (EECR & (1 << EEPE))

/**
 * EEPROM read sequence:
 * 1. Wait until EEPE becomes zero.
 * 2. Wait until SELFPRGEN in SPMCSR becomes zero.
 * 3. Write new EEPROM address to EEAR (optional).
 * 4. Write a logical one to the EERE bit in EECR.
 * 5. The EEPROM data is available immediately.
 */
/**=============================================================================*/

/**
 * Read a byte from the EEPROM.
 * @param src The address to read from.
 * @return The byte read from the EEPROM.
 */
uint8_t eeprom_read_byte(uint8_t *src);

/**
 * EEPROM write sequence:
 * 1. Wait until EEPE becomes zero.
 * 2. Wait until SELFPRGEN in SPMCSR becomes zero.
 * 3. Write new EEPROM address to EEAR (optional).
 * 4. Write new EEPROM data to EEDR (optional).
 * 5. Write a logical one to the EEMPE bit while writing a zero to EEPE in EECR.
 * 6. Within four clock cycles after setting EEMPE, write a logical one to EEPE.
 */
/**=============================================================================*/

/**
 * Write a byte to the EEPROM.
 * @param dst The address to write to.
 * @param data The byte to write to the EEPROM.
 */
void eeprom_write_byte(uint8_t *dst, uint8_t data);
