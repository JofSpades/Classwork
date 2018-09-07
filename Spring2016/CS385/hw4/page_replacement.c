#include"types.h"
#include"user.h"
int main(int argc, char** argv) {
  int i,j,k;

  char* chunks[10];
  for(i=0;i<10;i++) {
    chunks[i]=malloc(1024*1024);
    if(!chunks[i]) {
      printf(1,"Uh-oh, couldn't reserve any more RAM!\n");
      exit();
    }
    memset(chunks[i],i,1024*1024);
  }
  
  for(i=0;i<10;i++) {
    for(j=1023;j>=0;j--) {
      for(k=1023;k>=0;k-=256) {
        if(chunks[i][0]!=i || chunks[i][j*1024+k]!=i) {
          printf(1,"Uh-oh, chunk %d doesn't contain all %d's\n",i,i);
          exit();
        }
      }
    }
  }

  exit();
}
