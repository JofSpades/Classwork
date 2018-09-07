#include "barrier.h"
#include <stdlib.h>
#include <stdio.h>

void barrier_init(barrier* b, int s) {
	b->mutex = (sem_t*)malloc(sizeof(sem_t));
	sem_init(b->mutex, 0, 1);
	b->enter = (sem_t*)malloc(sizeof(sem_t));
	sem_init(b->enter, 0, 0);
	b->exit = (sem_t*)malloc(sizeof(sem_t));
	sem_init(b->exit, 0, 1);
	b->size = s;
	b->count = 0;
	b->first = 1;
}

void barrier_wait(barrier* b) {
	sem_wait(b->mutex);
	if(b->first == 1){
		b->count++;
		if(b->count == b->size)	{
			sem_wait(b->exit);
			sem_post(b->enter);
		}
		sem_post(b->mutex);
		sem_wait(b->enter);
		sem_post(b->enter);
		b->first = 0;
	} else {
		b->count--;
		if(b->count == 0){
			sem_wait(b->enter);
			sem_post(b->exit);
		}
		sem_post(b->mutex);
		sem_wait(b->exit);
		sem_post(b->exit);
		b->first = 1;
	}
}
