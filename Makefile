CC = gcc
CFLAGS = -Wall -std=c99
TARGETS = desafio1 desafio2 desafio3

all: $(TARGETS)

desafio1: desafio1.c
	$(CC) $(CFLAGS) -o desafio1 desafio1.c

desafio2: desafio2.c
	$(CC) $(CFLAGS) -o desafio2 desafio2.c

desafio3: desafio3.c
	$(CC) $(CFLAGS) -o desafio3 desafio3.c

clean:
	rm -f $(TARGETS)

.PHONY: all clean
