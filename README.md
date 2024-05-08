# AVR Exploration

So far I have built a basic runtime and libraray functions for the atmega328p controller. There are examples of how to use the library functions in the `examples` directory. `lessons`  is intended to be a deep dive into ceratin aspects of the AVR microcontroller. `projects` is a place for cool shit.

If you want to add something please do.
## Setup

To start programming for AVR microcontrollers, we will first need a development environment. Each microcontroller architecture, think AVR, ARM, ..., has its own toolchain. I've simplified this process with a Docker container complete with the AVR toolchain and other essentials. This allows for consistent development across machines with Docker installed. This is also a good opportunity to get familiar with Docker and its benefits.

First you should clone this repository to your local machine. Then follow the setup instructions [here](https://github.com/Johnyb0223/avr-dev-env) to setup your development environment.

**note**: If you develop on windows or mac there is a known limitation to Docker. You can't pass a serial device from the host to your container. Therefore, to flash and montier the serial output of the ccontroller you must do this on the host machine. I hate this beacuse I would love to provide a seamless development and testing pipleline but havn't found a way around this yet. There is 

## Project Structure

- **common:** Contains common files that are mostly lesson/example agnostic

- **examples:** Example code that explores different aspects of AVR microcontroller programming. Each example includes a `makefile` for easy building and extensively commented C files.

- **lessons:** A deep dive into various topics.

- **utils:** Utility files acting as a library, containing functions used in examples and lessons. The default makefile includes this directory in the
linkers search path. Therefore any file in this directory can be included in any example or lesson by using `#include <file.h>`.

## Important Notes

```
**THIS HAS IMMEDIATE IMPLICATIONS FOR THE USE OF THE USART MODULE**
```
- There is a documented bug with the usart module. Please see `/projects/bigBug` for more information. 



