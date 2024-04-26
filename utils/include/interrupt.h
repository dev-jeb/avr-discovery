#ifndef AVR_INTERRUPT_H
#define AVR_INTERRUPT_H

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
 * @macro:
 * ISR
 *
 * @param vector:
 * interrupt vector to declare handler for
 *
 * @note:
 * you can read more about how this works by looking at crt.s and exploring weak
 * symbols with respect to the linker
 */
#define ISR(vector) void vector(void)

/**
 * @function:
 * interrupt_trigger_int0
 *
 * @purpose:
 * trigger the INT0 interrupt to act as a software interrupt
 */
void interrupt_trigger_int0();

/**
 * @function:
 * trigger_interrupt_int0_a1
 *
 * @purpose:
 * trigger the INT0 interrupt to act as a software interrupt
 *
 * @param arg1: uint8_ptr_t, can be used to pass a flag or data to the ISR
 */
void interrupt_trigger_int0_a1(uint8_ptr_t arg1);

#endif // AVR_INTERRUPT_H