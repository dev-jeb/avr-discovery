# AVR

Welcome, this is a repository where I document my exploration of embedded systems. I have an arduino uno which has an ATmega328p microcontroller as the brains of the operations. This is why I have chosen to explore the AVR architecture. The fundamental aspects of embedded systems such as memory types (volatile, non-volatile), memory mapped i/o, interrupts, communication protocols, etc are pretty hardware agnostic. So a lot of what is learned on an AVR microcontroller can be applied to other microcontroller. Skills such as reading data sheets, writing/compiling/linking C, flashing hardware, blah blah blah.

# Setup

The first step to develop for the AVR microcontroller is to setup the development environment. We need the software tools required to compile, flash, and run our code on the microcontroller. Each microcontroller architecture (AVR, ARM, x86-64,...) has its own toolchain. This is because each architecture has its own set of machine code instructions the microcontroller understands. So loading a byte into a register on a microcontroller that implements the ARM instruction set is different from the instruction that is used by an AVR microcontroller implementation

You could just download the toolchain on your local computer but you would miss a great opportunity to learn about Docker. I have setup a docker container that has the AVR toolchain installed (among other nice to haves). This way you can develop for the AVR microcontroller without having to install the toolchain on your local machine. This is great because you can develop on any machine that has Docker installed. It gives you a well defined and reproducible development environment.

You would clone this repo to your local machine. Then follow the instructions I have written [here](https://github.com/Johnyb0223/avr-dev-env) to setup the docker container.

# Project Structure

- **examples:** This folder contains example code for the AVR microcontroller. It is divided into logical sub-directories dependant on what the example pertains to. Each example is in its own folder and contains a `makefile` to build the example. The c files will have comments that are meant to be informative.

- **lesson:** This folder contains example code that I have found to be instructive.

- **link:**

- **utils:**

# Important Notes

- The `makefile` used to build a lot of the examples produces many different types of files. This is useful to really explore what is happening throughout different stages of the compilation pipeline and