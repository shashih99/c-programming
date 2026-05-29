# Makefile for Same Tree Problem

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
DEBUG_CFLAGS = -Wall -Wextra -std=c11 -g -O0 -DDEBUG
LDFLAGS =

# Target executable
TARGET = same_tree

# Source files
SRC = same_tree.c

# Object files
OBJ = $(SRC:.c=.o)
DEBUG_TARGET = build/Debug/$(TARGET)

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

# Debug build with debugging symbols and no optimization
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(SRC)
	@mkdir -p build/Debug
	$(CC) $(DEBUG_CFLAGS) -o $(DEBUG_TARGET) $(SRC)
	@echo "Debug build created: $(DEBUG_TARGET)"
	@echo "Run with: make debug-run"
	@echo "Or debug with gdb: gdb $(DEBUG_TARGET)"

# Run the debug build
debug-run: $(DEBUG_TARGET)
	./$(DEBUG_TARGET)

# Phony targets
.PHONY: all clean rebuild run debug debug-run
