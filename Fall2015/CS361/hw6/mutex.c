#include "mutex.h"
#include <stdlib.h>
#include <stdio.h>

void mutex_init(mutex* m) {
	m->s = (sem_t*)malloc(sizeof(sem_t));
	sem_init(m->s, 0, 1);
}
void mutex_lock(mutex* m) {
	sem_wait(m->s);
}
void mutex_unlock(mutex* m) {
	sem_post(m->s);
}
