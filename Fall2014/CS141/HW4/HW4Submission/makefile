scheck.o: scheck.h scheck.c
	gcc -std=c99 -c scheck.c

scheck_tst: scheck_tst.c scheck.o
	gcc -std=c99 -o scheck_tst scheck_tst.c scheck.o

story: story.c
	gcc -std=c99 -o story story.c

outline: outline.c
	gcc -std=c99 -o outline outline.c