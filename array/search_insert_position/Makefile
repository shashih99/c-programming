# Makefile for Search Insert Position Problem

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS = 

# Target executable
TARGET = search_insert_position

# Source files
SRC = search_insert_position.c

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

# Rebuild everything
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean rebuild run

