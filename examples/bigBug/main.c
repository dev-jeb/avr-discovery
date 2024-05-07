/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose: Here I will document and hopefully fix a bug that has kept me up at
 * night for the past 2 weeks. So much so that I have considered stopping
 * development on this repo and throwing in the towel. I would just use
 * avr-libc. I really do not want to do that.
 *
 * @bug_info: I am trying to achieve one simple task. Send a string over usart.
 */

#include "avr-arch.h"
#include "common.h"
#include "types.h"
#include "usart.h"

/**
 * you would think this would print out H to the terminal. It does not, and I
 * have spentt the past week... trying to figure out why I probably have around
 * 15 hours spent on actively working on this bug. TH
 */

int main(void) {
  // Initialize the USART module
  usart0_init(103);
  uint8_t pyl[] = "Hello";

  // loop
  for (uint8_t i = 0; i < strlen(pyl); i++) {
    // wait for the data buffer to be empty
    while (!(UCSR0A & (1 << UDRE0))) {
    };
    // Put data into buffer, sends the data
    UDR0 = *(pyl + i);
  }
}