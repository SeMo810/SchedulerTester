CC = gcc
CFLAGS = -c -g -Wall -Wextra
LFLAGS = -g -Wall -Wextra

all: cpuprog ioprog mxprog

cpuprog: cpuprog.o mersenne.o sched_util.o
	$(CC) $(LFLAGS) $^ -o $@ -lm

ioprog: ioprog.o sched_util.o
	$(CC) $(LFLAGS) $^ -o $@ -lm

mxprog: mxprog.o mersenne.o sched_util.o
	$(CC) $(LFLAGS) $^ -o $@ -lm

mersenne.o: mersenne.c
	$(CC) $(CFLAGS) $<

sched_util.o: sched_util.c
	$(CC) $(CFLAGS) $<

cpuprog.o: cpuprog.c
	$(CC) $(CFLAGS) $<

ioprog.o: ioprog.c ioinput
	$(CC) $(CFLAGS) $<

mxprog.o: mxprog.c
	$(CC) $(CFLAGS) $<

ioinput: Makefile
	dd bs=1024 count=1 < /dev/urandom > data/datainput.dat

clean:
	rm -f mxprog
	rm -f ioprog
	rm -f cpuprog
	rm -f *.o
	rm -f data/*
