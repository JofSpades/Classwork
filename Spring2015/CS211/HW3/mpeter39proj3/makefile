waitList: main.o doFile.o linked.o
	gcc -o waitList main.o doFile.o linked.o

main.o: main.c helper.h
	gcc -c main.c

doFile.o: doFile.c helper.h
	gcc -c doFile.c

linked.o: linked.c helper.h
	gcc -c linked.c