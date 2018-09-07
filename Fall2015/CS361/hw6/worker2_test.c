#include "test.h"
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void init();
void front_ready();
void back_ready();


// this is a thread-local value - every thread has its own version. 
// handy for keeping track of what kind of thread is calling group()!
__thread enum {BACK, FRONT} type;

int frontcount = 0, backcount = 0;
unsigned lastback = 0;
static sem_t *mutex;

void group() {

	sem_wait(mutex);
	if(type==BACK) {
		if(backcount==0) lastback = (unsigned)pthread_self();
		else if(lastback == (unsigned)pthread_self()) {
			printf("[FAIL] Cannot use same thread for both backs!\n");	 
			exit(1);
		}
		backcount++;
	}
	else if(type==FRONT) {
	frontcount++;
	}

	if(backcount == 2 && frontcount == 1) {
		frontcount = 0;
		backcount = 0;
	}
	else if(backcount > 2 || frontcount > 1) {
		printf("[FAIL] Incorrect back and front counts: %d backs, %d fronts\n",backcount, frontcount);
	}
	sem_post(mutex);
}

// back works until done == true or loop limit is reached
void* back_thread() {
	type=BACK;
	while(1) {
		back_ready();
		randomize();
	}
	return 0;
}

void* front_thread(void* limit) {
	type=FRONT;
	for(int i=0;i<*(int*)limit;i++) {
		front_ready();
		randomize();	 
	}
	return 0;
}

int main(int argc, char** argv) {
	srand(98769876);

	char *mutex_name = tempnam(0,"/worker2.");	
	mutex = sem_open(mutex_name+4,O_CREAT,0777,1);
	if(!mutex) {
		perror("No mutex!\n");
		exit(1);
	}

	pthread_t backs[8];

	/* TEST 1: several short-duration backs, one front */
	init();
	for(int i=0;i<8;i++) {
		randomize();
		pthread_create(&backs[i],0,back_thread,0);	 
	}

	pthread_t fronts[100];
	int lim = 960;
	pthread_create(&fronts[0],0,front_thread,(void*)&lim);
	void *result;
	pthread_join(fronts[0],&result);

	if(frontcount == 0) 
		printf("[PASS] worker2: short-duration backs, one front.\n");
	else {
		printf("[FAIL] incorrect final back and front count %d back %d front\n",backcount,frontcount);
		exit(1);
	}

	for(int i=0;i<8;i++) 
		pthread_cancel(backs[i]);

	frontcount = 0;
	backcount = 0;
	lastback = 0;
		
	// TEST 2: four of each
	init();
	for(int i=0;i<4;i++) {
		randomize();
		pthread_create(&backs[i],0,back_thread,0);	 
	}

	lim = 1000;
	for(int i=0;i<4;i++) 
		pthread_create(&fronts[i],0,front_thread,(void*)&lim);	


	for(int i=0;i<4;i++) 
		pthread_join(fronts[i],&result);

	for(int i=0;i<4;i++) 
		pthread_cancel(backs[i]);

	if(frontcount == 0) 
		printf("[PASS] worker2: four each\n");
	else {
		printf("[FAIL] worker2: four each -  incorrect final back and front count %d back %d front\n",backcount,frontcount);
		exit(1);
	}
	
	
	/*// TEST 3: one back, several fronts 
	init();
	for(int i=0;i<1;i++) {
		randomize();
		int lim = 2000;
		pthread_create(&backs[i],0,back_thread,(void*)&lim);	 
	}

	lim = 100;
	for(int i=0;i<20;i++) 
		pthread_create(&fronts[i],0,front_thread,(void*)&lim);	

	
	for(int i=0;i<20;i++) 
		pthread_join(fronts[i],&result);

	for(int i=0;i<1;i++) 
		pthread_join(backs[i],&result);

	printf("[PASS] worker2: 1 back, 20 fronts.\n");
	*/
}

