#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

typedef struct {
	sem_t *mutex, *enter, *exit;
	int size;
	int count;
	int first;
} barrier;
sem_t *mutex, *backReady, *frontReady;
barrier *bar;
int backCount, frontCount;

void group();
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

void init() {
	mutex = (sem_t*)malloc(sizeof(sem_t));
	sem_init(mutex, 0, 1);
	backReady = (sem_t*)malloc(sizeof(sem_t));
	sem_init(backReady, 0 , 0);
	frontReady = (sem_t*)malloc(sizeof(sem_t));
	sem_init(frontReady, 0 , 0);
	bar = (barrier*)malloc(sizeof(barrier));
	barrier_init(bar, 3);
	backCount = 0;
	frontCount = 0;
}

void front_ready() {
	sem_wait(mutex);
	frontCount++;
	if(backCount >= 2){
		sem_post(backReady);
		sem_post(backReady);
		backCount -=2;
		sem_post(frontReady);
		frontCount--;
	} else {
		sem_post(mutex);
	}
	sem_wait(frontReady);
	// printf("front ready\n");
	group();
	barrier_wait(bar);
	barrier_wait(bar);
	sem_post(mutex);
}

void back_ready() {
	sem_wait(mutex);
	backCount++;
	if(backCount >= 2 && frontCount >= 1){
		sem_post(backReady);
		sem_post(backReady);
		backCount -= 2;
		sem_post(frontReady);
		frontCount--;
	} else {
		sem_post(mutex);
	}
	sem_wait(backReady);
	// printf("back ready\n");
	group();
	barrier_wait(bar);
	barrier_wait(bar);
}