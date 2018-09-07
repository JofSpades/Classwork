#include "test.h"
#include "mutex.h"

int shared_count = 0;
mutex lock;

void* thread_code(void* nothing) {

  for(int i=0;i<100;i++) {
    int temp;
    randomize();
    mutex_lock(&lock);
    temp = shared_count;
    randomize();
    temp++;
    shared_count = temp;
    mutex_unlock(&lock);
  }

  for(int i=0;i<100;i++) {
    int temp;
    randomize();
    mutex_lock(&lock);
    temp = shared_count;
    randomize();
    temp--;
    shared_count = temp;
    mutex_unlock(&lock);
  }

  return NULL;
}

int main(int argc, char** argv) {
  srand(98769876);
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

  if(shared_count==0) {
    printf("[PASS] Mutex\n");
    exit(0);
  }
  else { 
    printf("[FAIL] Mutex\n");
    exit(1);
  }
}
