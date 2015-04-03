CC = gcc
CFLAGS = -c -g -Wall -Wextra
LFLAGS = -g -Wall -Wextra

all: cpuprog

cpuprog: cpuprog.o mersenne.o sched_util.o
	$(CC) $(LFLAGS) $^ -o $@ -lm

mersenne.o: mersenne.c
	$(CC) $(CFLAGS) $<

sched_util.o: sched_util.c
	$(CC) $(CFLAGS) $<

cpuprog.o: cpuprog.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f cpuprog
	rm -f *.o

results:
	mkdir ../results
	echo "Running CPU bound, small (100), SCHED_OTHER"
	sudo /usr/bin/time --verbose --output=../results/cpu_s_other ./cpuprog 100 SCHED_OTHER
	echo "Running CPU bound, small (100), SCHED_FIFO"
	sudo /usr/bin/time --verbose --output=../results/cpu_s_fifo ./cpuprog 100 SCHED_FIFO
	echo "Running CPU bound, small (100), SCHED_RR"
	sudo /usr/bin/time --verbose --output=../results/cpu_s_rr ./cpuprog 100 SCHED_RR

results-clean:
	rm -rf ../results
