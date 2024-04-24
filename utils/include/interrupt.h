#ifndef AVR_INTERRUPT_H
#define AVR_INTERRUPT_H
#endif
/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 **/

#include "types.h"

/**
 * @function:
 * trigger_interrupt_INT0
 *
 * @implementation:
 * The PD2 pin is used as the INT0 external interrupt pin.
 * We can use this pin to trigger a software interrupt.
 *
 * To implement a software interrupt on the AVR microcontroller we will need to
 * take a couple steps. These steps will be a sequence of operations on some
 * i/o registers.
 * STEP 1: Save the status register to a temporary variable
 * STEP 2: Enable global interrupts
 * Step 3: Set PD2 (INIT0 pin) as output
 * STEP 4: Set INT0 to trigger on toggle
 * STEP 5: Enable INT0 interrupt
 * STEP 6: Toggle PD2 pin
 * STEP 7: Disable INT0 interrupt
 * STEP 8: Restore the status register
 *
 * This function will be callable with no arguments and one argument. If called
 * with one argument that argument will be passed to the function through the
 * register (R17).
 */
void trigger_interrupt_INT0();
void trigger_interrupt_INT0_1arg(uint8_ptr_t arg1);