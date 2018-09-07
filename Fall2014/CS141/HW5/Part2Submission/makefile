
simpleio.o: simpleio.h simpleio.c
	gcc -std=c99 -c simpleio.c

stack.o: stack.h stack.c
	gcc -std=c99 -c stack.c

bboard.o: bboard.h bboard.c
	gcc -std=c99 -c bboard.c

stack: main.c stack.o
	gcc -std=c99 -o stk_tst main.c stack.o

balenced: balenced.c simpleio.o stack.o
	gcc -std=c99 -o balence balenced.c simpleio.o stack.o

bpop: bpop.c simpleio.o bboard.o
	gcc -std=c99 -o bpop bpop.c simpleio.o bboard.o