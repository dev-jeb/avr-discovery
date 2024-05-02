/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * Here we will use the universal synchronous and asynchronous receiver and
 * transmitter (USART) to transmit a character to another computer.
 *
 * @important_notes:
 * - You  can use simavr to run the main.elf file built with the `make` command.
 * The command below can be used to see the configured baud rate and the format
 * of the data being sent.
 *
 * simavr -v -v -v -f 16000000 -m atmega328p -t main.elf
 */

#include "types.h"
#include "usart.h"

/**
 * @implementation:
 *
 * The Atmega328p microcontroller features a versatile Universal
 * Synchronous/Asynchronous Receive Transmit (USART) peripheral, which serves as
 * a crucial component for serial communication. The USART enables the
 * transmission and reception of data, facilitating communication
 * between the microcontroller and external devices or other microcontrollers.
 * Data transmission occurs bit by bit over a communication line, with each byte
 * framed by a start bit and one or two stop bits, the number of which is
 * configurable. Additionally, the byte frame may incorporate a parity bit,
 * enhancing error detection capabilities.
 *
 * Parity bits serve as a fundamental form of error-detecting code, typically
 * applied to the smallest units of a communication protocol, such as 8-bit
 * octets (bytes). The inclusion of a parity bit ensures that the total number
 * of 1-bits in the transmitted string is either even or odd, thereby detecting
 * errors that may occur during data transmission. There are two variants of
 * parity bits: even parity and odd parity, each imposing a different parity
 * requirement on the transmitted data.
 *
 * From Wikipedia:
 *
 * "Parity bits are a simple form of error-detecting code. Parity bits are
 * generally applied to the smallest units of a communication protocol,
 * typically 8-bit octets (bytes). The parity bit ensures that the total number
 * of 1-bits in the string is even or odd. Accordingly, there are two variants
 * of parity bits: even parity bit and odd parity bit."
 *
 * Utilizing error checking mechanisms like parity bits enhances the reliability
 * of data transmission, as it allows the receiving end to detect and
 * potentially correct errors that may have occurred during transmission.
 */

/**
 * here is something fun. We will transmit the version of crt.s used to
 * compile this program. We include this info at the bottom of crt.s
 * and place it in out final executable with the linker. The version
 * string is define as a global variable (crt_version_string).
 * It will be a symbol in the object file and we can access it as follows
 */
extern uint8_ptr_t __crt_version_string;

int main(void) {
  /**
   * I must chose a value to be loaded into the UBRRnH:L register
   * to set the baud rate. I will use the default value of 103
   * which assumes a system clock frequency of 16MHz and a baud rate of 9600
   * Initialize the USART module to 9600 baud rate at 16MHz clock frequency
   * usart0_init();
   */
  uint16_t ubrr = 103;
  usart0_init(ubrr);
  usart0_transmit_string(__crt_version_string);
  return 0;
}