hw1: hw1.c
	gcc -c -Wall hw1.c
	gcc -Wall -o hw1 hw1.c

test: hw1
	readelf -s hw1.o

clean:
	rm hw1 hw1.o
