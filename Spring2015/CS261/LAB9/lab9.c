/*###########################
# Name1:Maxwell Petersen    #
# Name2: Stephen Selke      #
# NetID1: mpeter39          #
# NetID2: sselke2           #
###########################*/
#include <stdio.h>
#include <sys/time.h>

#define  DIM 100
struct timeval tvalBefore, tvalAfter;

//1.Removed the sedend array element from second[][1] and result[][1], they are now second[] and result[].
//2.Unrolled the loops in matrixvector().

void matrixvector(int first[][DIM], int second[], int result[]) {
  int c;
  int k;

  for(c = 0; c < DIM; c += 4) {
    for(k = 0; k < DIM; k += 4) {
      result[c] += first[c][k]*second[k];
      result[c] += first[c][k+1]*second[k+1];
      result[c] += first[c][k+2]*second[k+2];
      result[c] += first[c][k+3]*second[k+3];

      result[c+1] += first[c+1][k]*second[k];
      result[c+1] += first[c+1][k+1]*second[k+1];
      result[c+1] += first[c+1][k+2]*second[k+2];
      result[c+1] += first[c+1][k+3]*second[k+3];

      result[c+2] += first[c+2][k]*second[k];
      result[c+2] += first[c+2][k+1]*second[k+1];
      result[c+2] += first[c+2][k+2]*second[k+2];
      result[c+2] += first[c+2][k+3]*second[k+3];

      result[c+3] += first[c+3][k]*second[k];
      result[c+3] += first[c+3][k+1]*second[k+1];
      result[c+3] += first[c+3][k+2]*second[k+2];
      result[c+3] += first[c+3][k+3]*second[k+3];
    }
  }

  if(DIM % 4 != 0){
    printf("did i get here?...\n");
    for(; c < DIM; c++) {
    for(; k < DIM; k++) {
      result[c] += first[c][k]*second[k];
    }
  }
  }
}


int main() {

  gettimeofday(&tvalBefore, NULL);
  int first[DIM][DIM];
  int second[DIM];
  int result[DIM];
  int i;
  int j;

  for (i=0;i<DIM;i++) {
    for (j=0;j<DIM;j++) {
     first[i][j]=i+j;
     second[i]=(i+1)*(j+1);
     result[i]=0;
   }
 }

 matrixvector(first,second,result);
 gettimeofday(&tvalAfter, NULL);

 printf("DONE\nTIME TAKEN:%ums\n",(unsigned int)(tvalAfter.tv_usec - tvalBefore.tv_usec));
 for (i=0;i<DIM;i++) {
 printf("%d ",result[i]);
}
printf("\n");
 return 1;
}
