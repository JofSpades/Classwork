postfix: main.o linked.o
	gcc -o postfix main.o linked.o

main.o: main.c helper.h
	gcc -c main.c

linked.o: linked.c helper.h
	gcc -c linked.c