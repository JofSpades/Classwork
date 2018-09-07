#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void handler(int sig) {
  printf("Got signal %d\n", sig);
}

int main(int argc, char **argv) {
  int status;

  signal(SIGINT, handler);
  //signal(SIGTSTP, handler);

  if( !fork() ) {
    while( 1 ) {
      printf("This is an infinite loop\n");
      sleep(2);
    }
    exit(0);
  }

  wait(&status);
  printf("After wait from parent process\n");

  return 0;
}
