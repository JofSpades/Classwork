#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

sem_t *service_sem, *request_sem, *enter_sem, *exit_sem, *mutex;
int size, count;
void pair();

void init() {
	service_sem = (sem_t*)malloc(sizeof(sem_t));
	sem_init(service_sem, 0, 1);
	request_sem = (sem_t*)malloc(sizeof(sem_t));
	sem_init(request_sem, 0, 1);
	enter_sem = (sem_t*)malloc(sizeof(sem_t));
	sem_init(enter_sem, 0, 0);
	exit_sem = (sem_t*)malloc(sizeof(sem_t));
	sem_init(exit_sem, 0, 1);
	mutex = (sem_t*)malloc(sizeof(sem_t));
	sem_init(mutex, 0, 1);
	size = 2;
	count = 0;
}

void frontBarrier(){
	sem_wait(mutex);
	count++;
	if(count == size)	{
		sem_wait(exit_sem);
		sem_post(enter_sem);
	}
	sem_post(mutex);
	sem_wait(enter_sem);
	sem_post(enter_sem);
}

void backBarrier(){
	sem_wait(mutex);
	count--;
	if(count == 0){
		sem_wait(enter_sem);
		sem_post(exit_sem);
	}
	sem_post(mutex);
	sem_wait(exit_sem);
	sem_post(exit_sem);
}

void wait_for_service() {
	sem_wait(service_sem);
	frontBarrier();
	pair();
	backBarrier();
	sem_post(service_sem);
}

void wait_for_request() {
	sem_wait(request_sem);
	frontBarrier();
	pair();
	backBarrier();
	sem_post(request_sem);
}
