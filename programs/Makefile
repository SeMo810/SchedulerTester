CC = gcc
CFLAGS = -c -g -Wall -Wextra
LFLAGS = -g -Wall -Wextra

all: cpuprog

cpuprog: cpuprog.o mersenne.o
	$(CC) $(LFLAGS) $^ -o $@ -lm

mersenne.o: mersenne.c
	$(CC) $(CFLAGS) $<

cpuprog.o: cpuprog.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f cpuprog
	rm -f *.o
