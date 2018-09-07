#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define STDIN_FD 0
#define STDOUT_FD 1

int main(int argc, char **argv) {
  int fd = open("output.txt", O_RDWR | O_CREAT, 0666);
  if( fd < 0 ) {
    printf("Unable to open output.txt\n");
    exit(0);
  }

  printf("The file descriptor is %d\n", fd);

  // do the redirection
  dup2(fd, STDIN_FD);

  char str[100];
  scanf("%s", str);
  printf("The input from keyboard is: %s\n", str);

  close(fd);

  return 0;
}
