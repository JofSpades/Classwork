#include "test.h"
#include "rwlock.h"
#include <unistd.h>
#include <sys/time.h>

long int shared_count = 0;
rwlock rwl;

/*
 * test cases:
 * 1. multiple readers can complete concurrently
 * 2. multiple writers do not write concurrently
 * 3. when a writer has lock, reader cannot read
 * 4. when reader has lock, writer cannot write
 *
 */

void * immediate_writer(void*nothing){
  wlock(&rwl);
  shared_count+=1;
  wunlock(&rwl);
  return NULL;
}

void * laggy_writer(void*nothing){
  wlock(&rwl);
  sleep(3);
  shared_count+=1;
  wunlock(&rwl);
  return NULL;
}

void* laggy_reader(void* nothing){
  rlock(&rwl);
  sleep(3);
  runlock(&rwl);
  return (void*)shared_count;
}

void * immediate_reader(void * nothing){
  rlock(&rwl);
  runlock(&rwl);
  return (void*)shared_count;
}


int main(int argc, char** argv) {
  long int return_value;
  long int result;
  void *return_ptr = &return_value;
  int slow_thread = random() % 100;
  struct timeval tval_before, tval_after, tval_result;

  int first_diff, second_diff;
  srand(98769876);

  rwlock_init(&rwl,10);

  // test 1: laggy reader does not delay immediate readers

  pthread_t threads[100];
  
  gettimeofday(&tval_before, NULL);
  for(int i=0;i<100;i++) {
    if (i == slow_thread){
      pthread_create(&threads[i],0,laggy_reader,0);
    }
    else
      pthread_create(&threads[i],0,immediate_reader,0);
  }


  for(int i=0;i<100;i++) {
    if (i != slow_thread)
      pthread_join(threads[i],&return_ptr);
  }
  gettimeofday(&tval_after, NULL);

  timersub(&tval_after, &tval_before, &tval_result);
  
  if (tval_result.tv_sec < 3)
    printf("[PASS} rwlock test 1\n");
  else
    printf("[FAIL} rwlock test 1\n");
  
  pthread_join(threads[slow_thread],&return_ptr);

  // test 2: writers do not clobber each other or run concurrently
  
  shared_count = 0;
  gettimeofday(&tval_before, NULL);
  for(int i = 0 ; i < 3; i++){
    pthread_create(&threads[i],0,laggy_writer,0);
    
  }
  for(int i = 0 ; i < 3 ; i++){
    pthread_join(threads[i],&return_ptr);
  }
  
  gettimeofday(&tval_after, NULL);
  timersub(&tval_after, &tval_before, &tval_result);
  if(tval_result.tv_sec == 9 && shared_count == 3)
    printf("[PASS} rwlock test 2\n");
  else
    printf("[FAIL} rwlock test 2\n");
  
  // test 3. when a writer has lock, reader cannot read
  // make sure that readers (a) wait for writer to finish (1st join long, 2nd join short),
  // (b) get the value after the write
  shared_count = 0;
  pthread_create(&threads[0],0,laggy_writer,0);
  usleep(1);
  pthread_create(&threads[1],0,immediate_reader,0);
  gettimeofday(&tval_before, NULL);
  pthread_join(threads[1],&return_ptr);
  result = (long int) return_ptr;
  gettimeofday(&tval_after, NULL);
  timersub(&tval_after, &tval_before, &tval_result);
  printf("time to join on reader:  %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
  first_diff = tval_result.tv_sec;
  pthread_join(threads[0],NULL);
  gettimeofday(&tval_before, NULL);
  timersub(&tval_before, &tval_after, &tval_result);
  printf("time to join on writer:  %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
  printf("return value from reader: %ld\n", result);
  second_diff = tval_result.tv_sec;
  if(second_diff == 0 && first_diff == 3 && result == 1)
    printf("[PASS} rwlock test 3\n");
  else
    printf("[FAIL} rwlock test 3\n");


  //  * 4. when reader has lock, writer cannot write
  // make sure that (a) writer waits for reader to finish (1st join long, 2nd join short)
  // and (b) the reader gets the value from BEFORE the writer writes
  

  shared_count = 100;
  pthread_create(&threads[0],0,laggy_reader,0);
  usleep(1);
  pthread_create(&threads[1],0,immediate_writer,0);
  gettimeofday(&tval_before, NULL);
  pthread_join(threads[1],NULL);
  gettimeofday(&tval_after, NULL);
  timersub(&tval_after, &tval_before, &tval_result);
  printf("time to join on writer:  %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
  first_diff = tval_result.tv_sec;
  pthread_join(threads[0],&return_ptr);
  result = (long int) return_ptr;
  gettimeofday(&tval_before, NULL);
  timersub(&tval_before, &tval_after, &tval_result);
  printf("time to join on reader:  %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
  printf("return value from reader: %ld\n",result);
  second_diff = tval_result.tv_sec;
  if(second_diff == 0 && first_diff == 3 && result == 100)
    printf("[PASS} rwlock test 4\n");
  else
    printf("[FAIL} rwlock test 4\n");

}
