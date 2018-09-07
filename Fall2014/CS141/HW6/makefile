llist.o: list.h llist.c
	gcc -std=c99 -g -O0 -c llist.c

listTest: ll_tst.c llist.o
	gcc -std=c99 -g -O0 -o listTest ll_tst.c llist.o

imsort: imsort.c llist.o
	gcc -std=c99 -g -O0 -o imsort imsort.c llist.o