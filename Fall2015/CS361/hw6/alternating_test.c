#include <unistd.h>
#include <fcntl.h>
#include "test.h"
#include <semaphore.h>

void init();
void read_ready();
void write_ready();

static sem_t *mutex;
static int readers=0, writers=0;
enum {READ, WRITE} last_action = READ;

void do_write() {	
	sem_wait(mutex);	
	writers++;
	if(readers) {
		printf("[FAIL] concurrent write and read\n");
		exit(1);
	}
	/*	if(writers>8) {
		printf("[FAIL] too many concurrent writers\n");
		exit(1);
		}*/
	sem_post(mutex);

	if(last_action == READ) {
		last_action = WRITE;
		usleep(100000);
	}
	usleep(10000);
	printf("WRITE\n");

	sem_wait(mutex);
	writers--;
	sem_post(mutex);
}

void do_read() {
	sem_wait(mutex);
	readers++;
	if(writers) { 
		printf("[FAIL] concurrent read and write\n");
		exit(1);
	}
	/*	if(readers>8) {
		printf("[FAIL] too many concurrent readers\n");
		exit(1);
		}*/
	sem_post(mutex);

	if(last_action == WRITE) {
		last_action = READ;
		usleep(1000);
	}
	usleep(100);
	printf("READ\n");

	sem_wait(mutex);
	readers--;
	sem_post(mutex);
}

void* reader_thread(void* limit) {
	for(int i=0;i<*(int*)limit;i++) {
		read_ready();
		randomize();
	}
	return 0;
}

void* writer_thread(void* limit) {
	for(int i=0;i<*(int*)limit;i++) {
		write_ready();
		randomize();	 
	}
	return 0;
}


int main(int argc, char** argv) {
	init();

	char *mutex_name = tempnam(0,"alternating.");	
	mutex = sem_open(mutex_name+4,O_CREAT,0777,1);

	int lim = 100;

	pthread_t readers[100];
	for(int i=0;i<10;i++) {
		randomize();
		pthread_create(&readers[i],0,reader_thread,&lim);	 
	}

	pthread_t writers[100];
	for(int i=0;i<10;i++) {
		randomize();
		pthread_create(&writers[i],0,writer_thread,(void*)&lim);
	}

	void *result;
	for(int i=0;i<10;i++) {
		pthread_join(readers[i],&result);
		pthread_join(writers[i],&result);
	}
	
	}
