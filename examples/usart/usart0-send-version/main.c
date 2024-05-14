/**
 * @contact_info:
 * Author: dev_jeb
 * Email: developer_jeb@outlook.com
 *
 * @purpose:
 * Here we will use the universal synchronous and asynchronous receiver and
 * transmitter (USART) to transmit a character to another computer.
 *
 * @workflow:
 * step 1: Build the program using the `make` command in the development
 * container.
 *
 * step 2: Flash the program to the microcontroller using avrdude from the host
 * using the following command
 *
 * >> avrdude -p atmega328p -c arduino -P /dev/<serial_device> -b <baud> -U \
 *    flash:w:<executable>
 *
 * step 3: Check the output of the program using a serial monitor like minicom
 *
 * >> minicom -D /dev/<serial_device> -b <baud>
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
 *
 * @bug: when compiling an executable with the USART module, the optimization
 * level must be set to -Os. If not it is undefined behavior.
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
 * enhancing error detection capabilities. You should take five minutes and read
 * the wiki on parity bits. They are a simplistic form of error checking.
 */

extern uint8_t __crt_version_string;

void foo(uint8_ptr_t str) {
  usart0_transmit_bytes(str);
  usart0_transmit_byte(NEW_LINE);
  usart0_transmit_byte(CARRIAGE_RETURN);
  uint8_ptr_t str3 = "crt version(used to link):";
  usart0_transmit_bytes(str3);
  usart0_transmit_byte(NEW_LINE);
  usart0_transmit_byte(CARRIAGE_RETURN);
  usart0_transmit_bytes(&__crt_version_string);
}

int main(void) {
  // 16 MHz, 9600 Baud = 103
  uint16_t ubrr = 103;
  usart0_init(ubrr);
  usart0_transmit_bytes(CLEAR_SCREEN);
  uint8_ptr_t str = "ping";
  usart0_transmit_bytes(str);
  usart0_transmit_byte(NEW_LINE);
  usart0_transmit_byte(CARRIAGE_RETURN);
  uint8_ptr_t str1 = "pong";
  foo(str1);
  return 0;
}

/**
 * @note: the workflow to build, flash and check this programs
 * output is not pretty. This is because on OSX (Mac) you can't access the
 * serial device on the host from the docker development container. This is a
 * known issue. I develop using the tool chain in the container, I step over to
 * my host machine to flash the program and monitor the serial device.
 */