
// file:  scheck_tst.c
// Description:
//     primitive program exercising/testing the scheck
//     sudoku checker function
//
// Disclaimer:  only for illustration purposes.  Does not do
//     robust testing by any means.
//     Merely offered as a starting point.

#include "scheck.h"
#include <stdio.h>

int main() {
int nviolations;


int ok[][9] =  {
                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                       {7, 8, 9, 1, 2, 3, 4, 5, 6}, 
                       {4, 5, 6, 7, 8, 9, 1, 2, 3},
                       {9, 1, 2, 3, 4, 5, 6, 7, 8},
                       {6, 7, 8, 9, 1, 2, 3, 4, 5}, 
                       {3, 4, 5, 6, 7, 8, 9, 1, 2},
                       {8, 9, 1, 2, 3, 4, 5, 6, 7},
                       {5, 6, 7, 8, 9, 1, 2, 3, 4}, 
                       {2, 3, 4, 5, 6, 7, 8, 9, 1}
                 };

int bad[][9] =  {
                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                       {79, 8, 9, 1, 2, 3, 4, 5, 6}, 
                       {4, 5, 6, 7, 8, 9, 6, 2, 3},
                       {9, 1, 2, 3, 4, 5, 1, 7, 8},
                       {6, 7, 8, 9, 1, 2, 3, 4, 5}, 
                       {3, 4, 5, 6, 7, 8, 9, 1, 2},
                       {8, 9, 1, 2, 3, 4, 5, 6, 7},
                       {5, 6, 7, 8, 9, 1, 2, 3, 4}, 
                       {2, 3, 4, 5, 6, 7, 8, 9, 1}
                 };
  nviolations = scheck(ok);

  if(nviolations != 0)
       printf("FAILED:  expected 0 violations; %i reported\n", 
			nviolations);
  else
       printf("PASSED: %i violations reported\n", nviolations);

   nviolations = scheck(bad);

  if(nviolations != 0)
       printf("FAILED:  expected 0 violations; %i reported\n", 
			nviolations);
  else
       printf("PASSED: %i violations reported\n", nviolations);

}
