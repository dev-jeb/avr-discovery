#ifndef AVR_INTERRUPT_H
#define AVR_INTERRUPT_H
#endif

/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * This module will provide a way to trigger software interrupts on the AVR.
 *Will build out to facilitate other interrupts as needed.
 **/
#include "types.h"

/**
 * avr defined interrupt vectors
 */
#define INT0_vect __vector_1
#define INT1_vect __vector_2
#define PCINT0_vect __vector_3
#define PCINT1_vect __vector_4
#define PCINT2_vect __vector_5
#define WDT_vect __vector_6
#define TIMER2_COMPA_vect __vector_7
#define TIMER2_COMPB_vect __vector_8
#define TIMER2_OVF_vect __vector_9
#define TIMER1_CAPT_vect __vector_10
#define TIMER1_COMPA_vect __vector_11
#define TIMER1_COMPB_vect __vector_12
#define TIMER1_OVF_vect __vector_13
#define TIMER0_COMPA_vect __vector_14
#define TIMER0_COMPB_vect __vector_15
#define TIMER0_OVF_vect __vector_16
#define SPI_STC_vect __vector_17
#define USART_RX_vect __vector_18
#define USART_UDRE_vect __vector_19
#define USART_TX_vect __vector_20
#define ADC_vect __vector_21
#define EE_RDY_vect __vector_22
#define ANA_COMP_vect __vector_23
#define TWI_vect __vector_24
#define SPM_RDY_vect __vector_25

/**
 * macro to define an interrupt service routine
 *@param vector: interrupt vector to declare ISR for
 *
 * you can read more about how this works by looking at crt.s and exploring weak
 * symbols with respect to the linker
 */
#define ISR(vector) void vector(void)

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