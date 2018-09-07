#include <semaphore.h>
typedef struct {
	sem_t *s;
} mutex;
void mutex_init(mutex* m);
void mutex_lock(mutex* m);
void mutex_unlock(mutex* m);
