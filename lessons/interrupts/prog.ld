/**
* @contact_info:
* Author: dev_jeb
* Email: dev_jeb@outlook.com
*
* @purpose:
* A linker script to use with avr-ld.
**/

/**
* These statements will tell the linker to add certain metadata to the 
* headers in the executable file. The executable will be the elf32-avr format.
* The elf headers will contain metadata relating to the ATmega328p.
OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

/**
* we will explicitly link with the crt.o file found in the 
* /common/ directory (We need this to setup the environment prior to calling main). 
* Notice how we pass the option -L with the path to the common directory in the makefile. 
* The linker search for the crt.o file in the current directory then when not found traverse 
* the directories specified with the -L option.
**/
INPUT (crt.o)



/* define useful constants for the ATmega328p */
__TEXT_REGION_ORIGIN__           = 0;
__TEXT_REGION_LENGTH__           = 32768;
__DATA_REGION_ORIGIN__           = 0x800000;
__DATA_REGION_LENGTH__           = 0x08ff;
__EEPROM_REGION_LENGTH__         = 1K;
__FUSE_REGION_LENGTH__           = 1K;
__LOCK_REGION_LENGTH__           = 1K;
__SIGNATURE_REGION_LENGTH__      = 1K;
__USER_SIGNATURE_REGION_LENGTH__ = 1K;

/* define some useful symbols */
__stack = 0x;

/* define the memory layout of the ATmega328p */
MEMORY
{
  text   (rx)            : ORIGIN = __TEXT_REGION_ORIGIN__, LENGTH = __TEXT_REGION_LENGTH__
  data   (rw!x)          : ORIGIN = __DATA_REGION_ORIGIN__, LENGTH = __DATA_REGION_LENGTH__
  eeprom (rw!x)          : ORIGIN = 0x810000, LENGTH = __EEPROM_REGION_LENGTH__
  fuse      (rw!x)       : ORIGIN = 0x820000, LENGTH = __FUSE_REGION_LENGTH__
  lock      (rw!x)       : ORIGIN = 0x830000, LENGTH = __LOCK_REGION_LENGTH__
  signature (rw!x)       : ORIGIN = 0x840000, LENGTH = __SIGNATURE_REGION_LENGTH__
  user_signatures (rw!x) : ORIGIN = 0x850000, LENGTH = __USER_SIGNATURE_REGION_LENGTH__
}

SECTIONS
{

    .text 0x0000   : 
    {
        

        /**
        * must place the reset vector at the beginning of the .text section
        **/
        crt.o(.vectors)
        KEEP(crt.o(.vectors))

        /** 
        * section contains weak symbol for __init that will ensure reset vector 
        * jumps to __init function if it is not redefined by the user. __init is 
        * defined in crt.s
        **/
        crt.o(.init)
        KEEP(crt.o(.init))

        /**
        * section contains the  function that will be called by the reset vector
        * sets status register to 0 and initialize the stack pointer
        **/
        crt.o(.bad_interrupt)
        KEEP(crt.o(.bad_interrupt))

        /**
        * section that contains the routines to load the data section from flash to ram
        * and to zero out the bss section
        **/
        *(.init4)
        KEEP(*(.init4))

        /**
        * calls the main function
        **/
        *(.init9)
        KEEP(*(.init9))

        main.o(.text)
        main.o(.text.*)

        *(.text)

        *(.fini9)
        KEEP(*(.fini9))

        *(.fini0)
        KEEP(*(.fini0))

        /**
        * include the version information for crt.s
        **/
        crt.o(.version)
        KEEP(crt.o(.version))

        . = ALIGN(2);
        _text_end = .;
    }

    .data 0x800100  : AT (ADDR(.text) + SIZEOF (.text)) {
        __data_start = .;
        *(.data)
        *(.data*)
        *(.gnu.linkonce.d*)
        /* We need to include .rodata here if gcc is used with -fdata-sections. */
        *(.rodata)
        *(.rodata*)
        *(.gnu.linkonce.r*)
        . = ALIGN(2);
        __data_end = .;
    }

    .bss __data_end : AT (ADDR (.bss)) {
        __bss_start = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    }> data
    __HEAP_START = .;
    __data_load_start = LOADADDR(.data);
    __data_load_end = __data_load_start + SIZEOF(.data);
}

