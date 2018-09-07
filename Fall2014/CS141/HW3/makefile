

arr_util.o: arr_util.h arr_util.c
	gcc -std=c99 -c arr_util.c

arr_util_tst: arr_util.c arr_util.o
	gcc -std=c99 -o arr_util_tst arr_util_tst.c arr_util.o

encode: encode.c
	gcc -std=c99 -o encode encode.c

decode: decode.c
	gcc -std=c99 -o decode decode.c