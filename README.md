# AVR Exploration

Welcome to AVR discovery! Here, I document my exploration of embedded systems, focusing on the AVR architecture. With an Arduino Uno featuring an ATmega328p microcontroller, I explore fundamental areas such as memory types, I/O, interrupts, and protocols. A lot of these concepts are architectures agnostic and can be applied to other microcontrollers.

## Setup

To start programming for AVR microcontrollers, set up the development environment. Each microcontroller architecture, like AVR, ARM, ..., has its own toolchain. I've simplified this process with a Docker container pre-installed with the AVR toolchain and other essentials. This allows for consistent development across machines with Docker installed. This is also a good opportunity to get familiar with Docker and its benefits.

First you should clone this repository to your local machine.Then follow the setup instructions [here](https://github.com/Johnyb0223/avr-dev-env) to setup your development environment.

## Project Structure

- **common:** Contains common files that are lesson/example agnostic (most of the time)

- **examples:** Explore example code that explores different aspects of AVR microcontroller programming. Each example includes a `makefile` for easy building and extensively commented C files.

- **lessons:** A deep dive into various topics.

- **utils:** utility files acting as a library, containing functions used in examples and lessons.

## Table of Contents
- **common**:
    - *[crt.s](common/crt.s)*:
    data structures the atmega328p microcontroller expects (vector table) and routines that work before the main function of a C program is called. This is to ensure the microcontroller is in a known state. This is usually known as the C-runtime and is conceptually different to *runtimes* used by javascript and other high-level languages.
- **examples**:
    - **eeprom**:
        - **[read-write-byte](examples/eeprom/read-write-byte/main.c)**:
            demonstrates how to read and write a byte to the EEPROM memory of the microcontroller.
    - **usart**: to be developed
- **lessons**:
   - **[interrupts](lessons/interrupts/main.c)**:
   - **[memory-allocation](lessons/memory-allocation/main.c)**:
   This lesson serves as an exploration of the avr-gcc compilation
   pipeline. Starting with an arbitrary program, we will see how the compilation
   pipeline (pre-processor, compiler, assembler, and linker) work together to
   produce an executable file that can be flashed to our microcontroller
   (atmega328p). We are particularly interested in how the linker handles
   relocatable object files produced by the pre-processor -> compiler ->
   assembler sequence to a final executable file that can be flashed to our
   microcontroller.
   - **[minimal-executable](lessons/minimal-executable/main.c)**:
   The executable created by building this directory is a minimal program that
   will properly setup the microcontroller and call the main function
## Important Notes

- The `makefile` used in building many examples generates multiple file types, offering insights into different stages of the compilation pipeline.
