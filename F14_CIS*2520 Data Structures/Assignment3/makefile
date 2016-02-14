CFLAGS = -Wall -ansi -pedantic 

all: p1 p2

p1: 
	gcc $(CFLAGS) -Iinclude1 src1/main.c src1/utility.c src1/tree.c src1/parse.c -o bin1/runme

p2: 
	gcc $(CFLAGS) -Iinclude2 src2/main.c src2/filestuff.c src2/arraystuff.c -o bin2/runme


clean:
	rm -f /bin1/*.o
	rm -f /bin2/*.o
	