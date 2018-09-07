#include "rwlock.h"
#include <stdlib.h>
#include <stdio.h>

void rwlock_init(rwlock* m, int concurrent_readers){
	m->mutex = (sem_t*)malloc(sizeof(sem_t));
	sem_init(m->mutex, 0, 1);
	m->writers = (sem_t*)malloc(sizeof(sem_t));
	sem_init(m->writers, 0, 1);
	m->readers = (sem_t*)malloc(sizeof(sem_t));
	sem_init(m->readers, 0, concurrent_readers);
	m->thereIsAReader = (sem_t*)malloc(sizeof(sem_t));
	sem_init(m->thereIsAReader, 0, 1);
	m->readerCount = 0;
	m->writerCount = 0;
}

void rlock(rwlock * m){
	sem_wait(m->mutex);
	if(m->writerCount == 0){
		if(m->readerCount == 0){
			sem_wait(m->thereIsAReader);
		}
		m->readerCount++;
		sem_post(m->mutex);
		sem_wait(m->readers);
	} else {
		sem_post(m->mutex);
		sem_wait(m->writers);
		sem_post(m->writers);
		sem_wait(m->mutex);
		if(m->readerCount == 0){
			sem_wait(m->thereIsAReader);
		}
		m->readerCount++;
		sem_post(m->mutex);
		sem_wait(m->readers);
	}
}

void runlock(rwlock * m){
	sem_wait(m->mutex);
	sem_post(m->readers);
	m->readerCount--;
	if(m->readerCount == 0){
		sem_post(m->thereIsAReader);
	}
	sem_post(m->mutex);
}

void wlock(rwlock * m){
	sem_wait(m->mutex);
	if(m->readerCount == 0){
		m->writerCount++;
		sem_post(m->mutex);
		sem_wait(m->writers);
	} else {
		sem_post(m->mutex);
		sem_wait(m->thereIsAReader);
		sem_post(m->thereIsAReader);
		sem_wait(m->mutex);
		m->writerCount++;
		sem_post(m->mutex);
		// sem_wait(m->writers);
	}
}

void wunlock(rwlock * m){
	sem_post(m->writers);
	sem_wait(m->mutex);
	m->writerCount--;
	sem_post(m->mutex);

}

