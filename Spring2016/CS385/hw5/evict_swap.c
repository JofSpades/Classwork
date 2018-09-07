#include"types.h"
#include"user.h"
int main(int argc, char** argv) {
  int fd = open("LARGE",0);  
  char* text = malloc(80000);
  read(fd,text,71680);
  text[71680]=0;

  printf(1,"Read some text.\n");
  printf(1,"%s\n",text+71661);

  printf(1,"Now evicting the page.\n");
  evict(text+71680);  

  exit();
}
