/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * Here we will use the universal synchronous and asynchronous receiver and
 * transmitter (USART) to transmit a character to another computer.
 *
 * @usage:
 * I will note here that the workflow to build, flash and check this programs
 * output is not pretty. This is because on OSX (Mac) you can't access the
 * serial device on the machine from the container. This is a known issue,
 * search for github pull requests related to this problem for more info.
 * So while I develop using the tool chain in the container, I have to step over
 * to my host machine to flash the program and check the output.
 *
 * @workflow:
 * step 1: Build the program using the `make` command in the development
 * container.
 *
 * step 2: Flash the program to the microcontroller using avrdude from the host
 * using the following command
 *
 * >> avrdude -p atmega328p -c arduino -P /dev/tty.usbmodem14301 -b 115200 -U \
 *    flash:w:main.hex
 *
 * step 3: Check the output of the program using a serial monitor like minicom
 *
 * >> minicom -D /dev/tty.usbmodem14301 -b 9600
 *
 * @important_notes:
 *
 * -the above steps mean you will need to download and install avrdude and
 * minicom on your host machine.
 *
 * - You  can use simavr to run the main.elf file built with the `make` command.
 * The command below can be used to see the configured baud rate and the format
 * of the data being sent.
 *
 * >> simavr -v -v -v -f 16000000 -m atmega328p -t main.elf
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
 * Utilizing error checking mechanisms like parity bits enhances the reliability
 * of data transmission, as it allows the receiving end to detect and
 * potentially correct errors that may have occurred during transmission.
 */

/**
 * here is something fun. We will transmit the version of crt.s used to
 * compile this program.  We include this info at the bottom of crt.s
 * and place it in our final executable with the linker. The version
 * string is defined as a global variable (__crt_version_string).
 * It will be a symbol in the object file and we can access it as follows.
 * Notice how the label is a byte
 */

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
  USART0_CLEAR_SCREEN;
  usart0_transmit_string((uint8_ptr_t) "hello");
  usart0_transmit_byte(NEW_LINE);
  usart0_transmit_byte(CARRIAGE_RETURN);
  usart0_transmit_version();
  return 0;
}