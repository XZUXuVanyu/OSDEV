# UEFI Shell Makefile

CC = x86_64-w64-mingw32-gcc
LD = x86_64-w64-mingw32-ld

# Compile Flags
CFLAGS = -I./efi -I./shell -O2 -Wall -Wextra -nostdinc -nostdlib -fno-builtin -fpic -fno-builtin -ffreestanding

# UEFI specific compile flags
EFI_CFLAGS = -DEFI_FUNCTION_WRAPPER -D_GNU_EFI

# Linker Flags for LD
LDFLAGS = -nostdlib -shared -subsystem=10 -entry=efi_main

# Source Directories
EFI_DIR = efi
SHELL_DIR = shell

# Source Files
SOURCES = main.c $(EFI_DIR)/efi_shell.c $(EFI_DIR)/efi_shell_utils.c $(EFI_DIR)/efi_shell_commands.c

# Header Files
HEADERS = $(EFI_DIR)/efi_data_type.h $(EFI_DIR)/efi_system_table.h $(EFI_DIR)/efi_shell.h $(EFI_DIR)/efi_shell_utils.h $(SHELL_DIR)/efi_shell_commands.h

# OBJ Files
OBJECTS = $(SOURCES:.c=.o)

# Output File
TARGET = main.efi
BUILD_DIR = build

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link object files to create EFI executable
$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/$@ $^

# Compile C source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(EFI_CFLAGS) -c -o $@ $<

# Clean up build files
clean:
	rm -rf $(BUILD_DIR) $(OBJECTS)

.PHONY: all clean