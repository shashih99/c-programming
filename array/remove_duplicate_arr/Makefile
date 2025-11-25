# Makefile for remove_duplicate_arr

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = remove_duplicate_arr
SRC = remove_duplicate_arr.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

# Debug build
debug: build/Debug/outDebug

build/Debug/outDebug: $(SRC)
	@mkdir -p build/Debug
	$(CC) $(CFLAGS) -g -o build/Debug/outDebug $(SRC)

clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf build

.PHONY: all run clean debug

