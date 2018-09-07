
#include <stdio.h>
#include "util.h"


int main(){
int tst_num=1;
int npassed=0;
int nfailed=0;


    
  if(abs_diff(5.0, 3.0) != 2.0){
	printf("test %i failed\n", tst_num);
	nfailed++;
  }
  else {
	npassed++;
  }
  tst_num++;

  if(median3(1, 2, 3) != 2) {
	printf("test %i failed\n", tst_num);
	nfailed++;
  }
  else {
	npassed++;
  }
  tst_num++;

  if(sqrt_floor(4) != 2) {
	printf("test %i failed\n", tst_num);
	nfailed++;
  }
  else {
	npassed++;
  }
  tst_num++;

  if(sqrt_floor(5) != 2) {
  printf("test %i failed\n", tst_num);
  nfailed++;
  }
  else {
  npassed++;
  }
  tst_num++;

  if(sqrt_floor(10) != 3) {
  printf("test %i failed\n", tst_num);
  nfailed++;
  }
  else {
  npassed++;
  }
  tst_num++;

  if(sqrt_floor(40) != 6) {
  printf("test %i failed\n", tst_num);
  nfailed++;
  }
  else {
  npassed++;
  }
  tst_num++;

  if(sqrt_floor(44) != 6) {
  printf("test %i failed\n", tst_num);
  nfailed++;
  }
  else {
  npassed++;
  }
  tst_num++;

  if(num_ones(5) != 2) {
	printf("test %i failed\n", tst_num);
	nfailed++;
  }
  else {
	npassed++;
  }
  tst_num++;

  if(num_ones(16) != 1) {
  printf("test %i failed\n", tst_num);
  nfailed++;
  }
  else {
  npassed++;
  }
  tst_num++;

  if(num_ones(511) != 9) {
  printf("test %i failed\n", tst_num);
  nfailed++;
  }
  else {
  npassed++;
  }
  tst_num++;

  if(num_ones(7) != 3) {
  printf("test %i failed\n", tst_num);
  nfailed++;
  }
  else {
  npassed++;
  }
  tst_num++;

  if(num_ones(31) != 5) {
  printf("test %i failed\n", tst_num);
  nfailed++;
  }
  else {
  npassed++;
  }

  printf("num_tests:     %i\n", tst_num);
  printf("num_passed:    %i\n", npassed);
  printf("num_failed:    %i\n", nfailed);


}
