# Define directory paths
UTILS_DIR := /workspaces/avr/utils
INCLUDE_DIR := $(UTILS_DIR)/include
SRC_DIR := $(UTILS_DIR)/src
OBJ_DIR := $(UTILS_DIR)/object-files

# Get all C source files in the src directory
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Convert source file paths to object file paths
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Compiler settings
CC := avr-gcc
CFLAGS := -Wall -g -Wextra -Os -mmcu=atmega328p -I$(INCLUDE_DIR)

# Main target
PRG := main
all: $(OBJ_FILES)

# Rule to compile each C source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean target
clean:
	rm -rf $(OBJ_DIR)/*.o $(PRG)


.PHONY: all clean
