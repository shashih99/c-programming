# Makefile for remove_duplicates_sorted_list

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
DEBUG_CFLAGS = -Wall -Wextra -std=c99 -g -O0 -DDEBUG
TARGET = remove_duplicates_sorted_list
SRC = remove_duplicates_sorted_list.c
OBJ = $(SRC:.c=.o)
DEBUG_TARGET = build/Debug/$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

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

# Clean build artifacts
clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf build

.PHONY: all run clean debug debug-run
