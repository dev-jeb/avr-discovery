    /**
    * @contact_info:
    * Author: dev_jeb
    * Email: developer_jeb@outlook.com
    *
    * @purpose
    * This file will define and setup the structures and symbols expected
    * by the main() function. Normally these structures and routines would 
    * be automatically linked from an existing object file that came with
    * the toolchain. However, in the makefile we are passing the options 
    * -nostartfiles, -nostdlib, and -nodefaultlibs to the linker. Why? 
    * Because we want to do everything on our own. It's about learning.
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
    * put this section into a non allocatable/executable memory section in the final
    * executable. Better safe then sorry. @progbits says this section contains program data.  
    **/
    .section .vectors,"ax",@progbits
	.global __vectors
	.func   __vectors
__vectors:
	jmp    __init
	vector  __vector_1 ;notice how we use the macro defined above. Why? weak symbols
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
    clr r1        ;set the zero register to zero
    out 0x3F, r1  ;zero out the status register
    ldi r28, 0x08
    out 0x3E, r28 ;set stack pointer high byte
    ldi r28, 0xFF
    out 0x3D, r28 ;set stack pointer low byte
    .endfunc

    /**
    * The main function expects the data defined by the program located in the .data section
    * of the executable object file to be located in SRAM. It is then our job to copy this data
    * from the flash memory to the SRAM before we call the main function. 
    **/
    .section .load_data,"aw",@progbits
    .global __load_data
    .func __load_data
__load_data:
    ldi r17, hi8(__data_end_sram)   ;r17      <-- high byte of (uint8_t*)__data_end_sram
    ldi r30, lo8(__data_start_flash) ;low(Z)  <-- low byte of (uint8_t*)__data_start_flash
    ldi r31, hi8(__data_start_flash) ;high(Z) <-- high byte of (uint8_t*)__data_start_flash
    ldi r28 , lo8(__data_start_sram) ;low(Y)  <-- low byte of (uint8_t*)__data_start_sram
    ldi r29 , hi8(__data_start_sram) ;high(Y) <-- high byte of (uint8_t*)__data_start_sram
    rjmp __load_data_start
    /**
    * next we need to load the byte pointed to by the Z pointer into the register r0 and 
    * increment the Z pointer. Then we will store the value in r0 into the SRAM pointed to
    * by the Y pointer and increment the Y pointer.
    **/
__load_data_loop:
    lpm r0, Z+ ;load the byte pointed to by Z into r0 and increment Z
    st Y+, r0  ;store the value in r0 into the SRAM pointed to by Y and increment Y
    /**
    * next we need to check if we have reached the end of the .data section. We will do this by
    * comparing the Z pointer to the end of the .data section. If we have not reached the end of the
    * .data section we will loop back and load the next byte from flash into r0 and store it in SRAM. 
    **/
__load_data_start:
    cpi  r28, lo8(__data_end_sram)
    cpc r17, r29
    brne __load_data_loop
    .endfunc

    /**
    * n bytes must be allocated in SRAM for the .bss where n = SIZEOF(.bss). These allocated bytes must be 
    * initialized to zero. The .bss section contains the uninitialized global and static variables (e.g uint8_t value;). 
    **/
    .section .zero_bss,"aw",@progbits
    .global __zero_bss
    .func __zero_bss
__zero_bss:
    ldi r30, lo8(__bss_start_sram) ;set Z pointer low byte to the low byte of ADDR(.bss section)
    ldi r31, hi8(__bss_start_sram) ;set Z pointer high byte to the high byte of ADDR(.bss section)
    ldi r28, lo8(__bss_end_sram)   ;set Y pointer low byte to the low byte of ADDR(__bss_end)
    ldi r29, hi8(__bss_end_sram)   ;set Y pointer high byte to the high byte of ADDR(__bss_end)
__zero_bss_loop:
    cpi r30, lo8(__bss_end_sram)   ;compare the low byte of Z to the low byte of ADDR(__bss_end)
    cpc r31, r29                   ;compare with carry the high byte of Z to the high byte of ADDR(__bss_end)
    breq __zero_bss_end            ;if they are equal jump to end of function
    st Z+, r0                      ;store zero in the SRAM pointed to by Z and increment Z
    jmp __zero_bss_loop            ;loop back
__zero_bss_end:
    .endfunc

    /**
    * with every thing setup we can now call the main function. First we should
    * clear the status register.
    **/
    .section .call_main,"ax",@progbits
    .global __call_main
    .func __call_main
__call_main:
    out 0x3F, r1 ;clear the status register
    sei          ;enable interrupts
    call main    ;call the main function
    cli          ;disable interrupts
__exit:
    jmp __exit   ;loop after main return
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

