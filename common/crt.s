    /**
    * @purpose
    * This file will define and setup the structures and symbols expected
    * by the main() function. Normally these structures and routines would 
    * be automatically linked into the final executable by the linker.
    * However, in the makefile we are passing the options -nostartfiles,
    * -nostdlib, and -nodefaultlibs to the linker. Why? Because we want to
    * do everything on our own. It's about learning and understanding.
    **/

    /**
    * This macro is used to define the vectors in the vector table. 
    * It ensures that the the name passed to the macro is defined in the
    * relocatable object file as a weak symbol. Therefore jump to name (i.e. __vector_1) 
    * if defined by user otherwise jump to __bad_interrupt
    **/
    .macro  vector name
    .weak   \name
    .set    \name, __bad_interrupt
    jmp    \name
    .endm
	
    /**
    * @vector_table
    * This is the vector table. It will be placed in the .vectors section 
    * of the relocatable object file. The attributes "ax" says that this section
    * is allocatable and executable. While the microcontroller does not know the
    * difference between allocatable/executable the linker will yell at you if you
    * put this section into a non allocatable/executable section. in the final. 
    * Better safe then sorry. @progbits says this section contains program data.  
    **/
    .section .vectors,"ax",@progbits
	.global __vectors
	.func   __vectors
__vectors:
	jmp    __init
	vector  __vector_1  ;notice how we use the macro defined above. Why? weak symbols
	vector  __vector_2
	vector  __vector_3
	vector  __vector_4
	vector  __vector_5
    vector  __vector_6
    vector  __vector_7
    vector  __vector_8
    vector  __vector_9
    vector  __vector_10
    vector  __vector_11
    vector  __vector_12
    vector  __vector_13
    vector  __vector_14
    vector  __vector_15
    vector  __vector_16
    vector  __vector_17
    vector  __vector_18
    vector  __vector_19
    vector  __vector_20
    vector  __vector_21
    vector  __vector_22
    vector  __vector_23
    vector  __vector_24
    vector  __vector_25
    .endfunc;

    /**
    * This is the default interrupt handler. Remember that all the vectors
    * in the vector table other then the reset vector were defined a weak symbols
    * that would be redirected to this handler if not defined by the user.
    * This handler is also defined as a weak symbol. Therefore, if the user
    * defines __vector_default, the handler will jump to that vector. Otherwise
    * we will jump to the symbol __vectors which happen to be the reset vector.
    **/
    .section .bad_interrupt,"ax",@progbits
    .global __bad_interrupt
    .func   __bad_interrupt
__bad_interrupt:
    .weak __vector_default
    .set __vector_default, __vectors
    jmp __vector_default
    .endfunc

    /**
    * So on reset or bad interrupt (an interrupt has occurred but the user did not define a handler)
    * we will jump to the __init symbol. So what should we do from here? The objective of this file is to
    * setup the environment that our main() function expects. We will set the zero register (r1) to zero
    * as is expected by the avr-gcc compiler. We will also zero out the status register. We will set the stack
    * register to 0x08FF which is the top of the SRAM. The stack register is implemented as two 8-bit registers
    * in the AVR architecture. This can be seen in the datasheet.
    **/
    .section .init,"ax",@progbits
    .weak __init
    .func __init
__init:
    clr r1  ;set the zero register to zero
    out 0x3F, R1 ;zero out the status register
    ldi r28, 0x08
    out 0x3E, r28 ;set stack pointer high byte
    ldi r28, 0xFF
    out 0x3D, r28 ;set stack pointer low byte
    .endfunc

    /**
    * The main function expects the data defined by the program located in the .data section
    * of the relocatable object files be located in SRAM. It is then our job to copy this data
    * from the flash memory to the SRAM. We will define a symbol in the linker script that will
    * point to the start of the .data section in flash. 
    **/
    .section .load_data,"aw",@progbits
    .global __load_data
    .func __load_data
__load_data:
    .endfunc


    /**
    * This section is used to define the version of crt.s. We will ensure in the linker script
    * that we catch this section and include it in the final executable. This is a simple way to
    * include some version control. Notice that this is a global symbol. We can reference this
    * symbol in our C program. We could write a function that prints this version string.
    **/
    .section .crt_version,"S",@progbits
    .global crt_version_string
crt_version_string:
    .string "Version 1.0"
    .byte 0

