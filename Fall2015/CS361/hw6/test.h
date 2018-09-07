#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void randomize() {
	int i=random();
	if(i%2==0) usleep(1);
	else usleep(i%1000);
}
