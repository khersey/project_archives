CC = gcc 
CFLAGS = -c -g -Wall -pedantic -ansi 

all: libpm.a ParameterManager.o parsing.o

libpm.a: ParameterManager.o parsing.o
	ar rc libpm.a ParameterManager.o parsing.o

ParameterManager.o: 
	$(CC) $(CFLAGS) ParameterManager.c

parsing.o:
	$(CC) $(CFLAGS) parsing.c

clean:
	rm *.o
	rm *.a
