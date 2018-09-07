#include "test.h"
#include "barrier.h"
#include "mutex.h"

int shared_count = 0;
barrier wall;
barrier wall2;
mutex lock;

void* thread_code(void* nothing) {

	for(int i=0;i<1000;i++) {
		randomize();

		mutex_lock(&lock);
		shared_count++;
		mutex_unlock(&lock);

		barrier_wait(&wall);		

		if(shared_count % 100 != 0) {
			printf("[FAIL] Barrier\n");
			printf("VIOLATION: count was %d when it should have been a multiple of 100.\n", shared_count);
			exit(1);
		}

		randomize();
		barrier_wait(&wall2);
	}

	return NULL;
}

int main(int argc, char** argv) {
	srand(98769876);
	barrier_init(&wall, 100);
	barrier_init(&wall2, 100);
	mutex_init(&lock);
	
	pthread_t threads[100];
	for(int i=0;i<100;i++) {
		randomize();
		pthread_create(&threads[i],0,thread_code,0);
	}
		
	for(int i=0;i<100;i++) {
		void *return_value;
		pthread_join(threads[i],&return_value);
	}

	printf("[PASS} Barrier\n");
	
}
