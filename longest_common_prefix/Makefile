# Makefile for longest_common_prefix

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = longest_common_prefix
SRC = longest_common_prefix.c
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

.PHONY: all run clean
