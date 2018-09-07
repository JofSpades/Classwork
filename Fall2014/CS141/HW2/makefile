

hist: hist.c simpleio.o
	gcc -std=c99 -o hist hist.c simpleio.o

quiz: quiz.c simpleio.o
	gcc -std=c99 -o quiz quiz.c simpleio.o

util.o: util.h util.c
	gcc -std=c99 -c util.c

util_tst: util_tst.c util.o
	gcc -std=c99 -o util_tst util_tst.c util.o