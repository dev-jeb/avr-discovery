# Makefile for building assembly files with avr-as

# Assembler and Assembler flags
AS = avr-as
ASFLAGS = -mmcu=atmega328p

# OBJ_CPY
OBJ_CPY = avr-objcopy


# Version control
VERSION = "Version 2.0" # Default version number

# match any files in the common directory
OBJ_FILES = crt.o

# Targets
all: $(OBJ_FILES)

$crt.o: crt.s 
	$(AS) $(ASFLAGS) -c $< -o $@

clean:
	rm -rf crt.o

.PHONY: all clean
