#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  printf("cs361> ");
  
  char cmd[513];
  fgets(cmd, 512, stdin);

  if( 0 == fork() ) {
    /*for(int i=1; i <=10; i++) {
      printf("Printing the command from child process\n%s\n", cmd);
      sleep(1);
    }*/

    execl("/bin/ls", "-l", NULL);
    printf("This printf is never executed! before exec\n");
    exit(0);
  }

  int status;
  wait(&status);

  printf("End of shell! Process pid: %d\n", getpid());

  return 0;

}
