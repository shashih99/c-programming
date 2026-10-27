# Makefile for Valid Parentheses Problem

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS = 

# Target executable
TARGET = valid_parentheses

# Source files
SRC = valid_parentheses.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf build

# Rebuild everything
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean rebuild run debug debug-run

DEBUG_CFLAGS = -Wall -Wextra -std=c11 -g -O0 -DDEBUG
DEBUG_TARGET = build/Debug/$(TARGET)

debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(SRC)
	@mkdir -p build/Debug
	$(CC) $(DEBUG_CFLAGS) -o $(DEBUG_TARGET) $(SRC)

debug-run: $(DEBUG_TARGET)
	./$(DEBUG_TARGET)
