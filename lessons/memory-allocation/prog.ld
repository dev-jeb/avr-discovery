
/*
*
*
/*
OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

/* define useful constants for the ATmega328p */
__TEXT_REGION_ORIGIN__ =  0;
__TEXT_REGION_LENGTH__ = 32K;
__DATA_REGION_ORIGIN__ = 0x800000;
__DATA_REGION_LENGTH__ = 0x08ff;
__EEPROM_REGION_LENGTH__ = 1K;
__FUSE_REGION_LENGTH__ =  1K;
__LOCK_REGION_LENGTH__ =  1K;
__SIGNATURE_REGION_LENGTH__ =  1K;
__USER_SIGNATURE_REGION_LENGTH__ = 1K;

/* define the memory layout of the ATmega328p */
MEMORY
{
  text   (rx)   : ORIGIN = __TEXT_REGION_ORIGIN__, LENGTH = __TEXT_REGION_LENGTH__
  data   (rw!x) : ORIGIN = __DATA_REGION_ORIGIN__, LENGTH = __DATA_REGION_LENGTH__
  eeprom (rw!x) : ORIGIN = 0x810000, LENGTH = __EEPROM_REGION_LENGTH__
  fuse      (rw!x) : ORIGIN = 0x820000, LENGTH = __FUSE_REGION_LENGTH__
  lock      (rw!x) : ORIGIN = 0x830000, LENGTH = __LOCK_REGION_LENGTH__
  signature (rw!x) : ORIGIN = 0x840000, LENGTH = __SIGNATURE_REGION_LENGTH__
  user_signatures (rw!x) : ORIGIN = 0x850000, LENGTH = __USER_SIGNATURE_REGION_LENGTH__
}

SECTIONS
{
    
    .text  : {

        /* Start here after reset. */
        _vectors = .;
        _text_start = .;
        *(.vectors)
        KEEP(*(.vectors))

        *(.trampolines*)
        KEEP(*(.trampolines))

        *(.init0)
        KEEP(*(.init0))

        *(.init2)
        KEEP(*(.init2))

        *(.init4)
        KEEP(*(.init4))

        *(.init6)
        KEEP(*(.init6))

        *(.init9)
        KEEP(*(.init9))

        prog1.o(.text)
        prog1.o(.text.*)

        prog2.o(.text)
        prog2.o(.text.*)

        *(.text)

        *(.fini9)
        KEEP(*(.fini9))

        *(.fini0)
        KEEP(*(.fini0))

        . = ALIGN(2);
        _text_end = .;
    } > text

    .data  :{
        PROVIDE (__data_start = .);
        *(.data)
        *(.data*)
        *(.gnu.linkonce.d*)
        /* We need to include .rodata here if gcc is used with -fdata-sections. */
        *(.rodata)
        *(.rodata*)
        *(.gnu.linkonce.r*)
        . = ALIGN(2);
        PROVIDE (__data_end = .) ;
    } > data AT> text

    .bss ADDR(.data) + SIZEOF (.data)   : AT (ADDR (.bss)) {
        PROVIDE (__bss_start = .);
        *(.bss)
        *(.bss*)
        *(COMMON)
        PROVIDE (__bss_end = .);
    }> data

    __data_load_start = LOADADDR(.data);
    __data_load_end = __data_load_start + SIZEOF(.data);
}

