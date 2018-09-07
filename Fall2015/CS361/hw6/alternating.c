#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

void do_read();
void do_write();

void init() {
}

void read_ready() {
	do_read();	
}

void write_ready() {
	do_write();
}
