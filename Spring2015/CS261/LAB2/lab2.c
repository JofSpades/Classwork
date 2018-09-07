#include <stdio.h>

void swap (int *x, int *y){
  	int tmp;
	tmp = *x; /* step 1 */
	*x = *y;  /* step 2 */
	*y = tmp; /* step 3 */
	}

void inplace_swap(int *x, int *y) {
	*y = *x ^ *y;  /* Step 1 */
	*x = *x ^ *y;  /* Step 2 */
	*y = *x ^ *y;  /* Step 3 */
    	}


int main() {

int first = 10;
int second = 100;

printf("first %d second %d \n", first, second);
swap(&first,&second);
printf("first %d second %d \n", first, second);
inplace_swap(&first,&second);
printf("first %d second %d \n", first, second);



}
