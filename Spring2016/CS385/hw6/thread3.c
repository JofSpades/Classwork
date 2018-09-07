#include"types.h"
#include"user.h"

int shared = 1;

void f(void) {
  while(shared<10000000) shared++;
  printf(1,"Done looping\n");
}

int main(int argc, char** argv) {
  thread_create(f);
  
  int last = shared;
  while(shared<10000000) {
    if(last!=shared) {
      last = shared;
//      printf(1,"shared = %d\n",last);
    }
  }
  printf(1,"Main is done!\n"); 

  // a little artificial wait: this is a completely bogus way of resolving
  // the race condition where the main thread may exit before f().
  int i=1000000000;
  while(i--);

  exit();
  return 0;
}
