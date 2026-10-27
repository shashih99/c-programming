# Makefile for add_binary

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = add_binary
SRC = add_binary.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)



clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf build

.PHONY: all clean rebuild run debug debug-run

DEBUG_CFLAGS = -Wall -Wextra -std=c11 -g -O0 -DDEBUG
DEBUG_TARGET = build/Debug/$(TARGET)

debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(SRC)
	@mkdir -p build/Debug
	$(CC) $(DEBUG_CFLAGS) -o $(DEBUG_TARGET) $(SRC)

debug-run: $(DEBUG_TARGET)
	./$(DEBUG_TARGET)
