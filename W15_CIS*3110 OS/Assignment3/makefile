CC = gcc
CFLAGS = -Wall -pedantic

all: dinner holes

holes: 
	$(CC) $(CFLAGS) holes.c fifoQueue.c memUtils.c -o holes

dinner:
	$(CC) $(CFLAGS) philosophers.c -o dinner

devholes:
	rm holes
	$(CC) $(CFLAGS) holes.c fifoQueue.c memUtils.c -o holes
