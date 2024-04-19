# AVR Exploration

Welcome to AVR discovery! Here, I document my exploration of embedded systems, focusing on the AVR architecture. With an Arduino Uno featuring an ATmega328p microcontroller, I explore fundamental areas such as memory types, I/O, interrupts, and protocols. A lot of these concepts are architectures agnostic and can be applied to other microcontrollers.

## Setup

To start programming for AVR microcontrollers, set up the development environment. Each microcontroller architecture, like AVR, ARM, ..., has its own toolchain. I've simplified this process with a Docker container pre-installed with the AVR toolchain and other essentials. This allows for consistent development across machines with Docker installed. This is also a good opportunity to get familiar with Docker and its benefits.

First you should clone this repository to your local machine.Then follow the setup instructions [here](https://github.com/Johnyb0223/avr-dev-env) to setup your development environment.

## Project Structure

- **examples:** Explore example code for the AVR microcontroller, organized by topics. Each example includes a `makefile` for easy building and extensively commented C files.

- **lesson:** Dive deeper into specific aspects of embedded systems with in-depth explorations housed in this directory.

- **utils:** Access utility files acting as a library, containing functions beneficial for AVR microcontroller development.

## Important Notes

- The `makefile` used in building many examples generates multiple file types, offering insights into different stages of the compilation pipeline.
