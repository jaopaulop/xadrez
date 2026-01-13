CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = xadrez

all: $(TARGET)

$(TARGET): xadrez.c
	$(CC) $(CFLAGS) -o $(TARGET) xadrez.c

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
