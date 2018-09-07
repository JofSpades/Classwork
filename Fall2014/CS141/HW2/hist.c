#include "simpleio.h"
#include <stdio.h>


int main() {

	/*recieve values for histogram check for positive or negitive */

	int a, b, c, d;
	a = -1;
	b = -1;
	c = -1;
	d = -1;

	while(a < 0){
		printf("Enter value for A:  ");
		a = get_int();
		if(a < 0){
			printf("Non negitive value please\n");
		}
	}
	while(b < 0){
		printf("Enter value for B:  ");
		b = get_int();
		if(b < 0){
			printf("Non negitive value please\n");
		}
	}
	while(c < 0){
		printf("Enter value for C:  ");
		c = get_int();
		if(c < 0){
			printf("Non negitive value please\n");
		}
	}
	while(d < 0){
		printf("Enter value for D:  ");
		d = get_int();
		if(d < 0){
			printf("Non negitive value please\n");
		}
	}
	
	
	
	/*check for maximum value*/

	int maximum = 0;

	if(maximum < a){
		maximum = a;
	}
	if(maximum < b){
		maximum = b;
	}
	if(maximum < c){
		maximum = c;
	}
	if(maximum < d){
		maximum = d;
	}

	/*graph drawing with one row at a time */

	int track = maximum;

	printf("\n\n");

	for (int i = 0; i < maximum; i++){
		printf(" ");
		if(a >= track){
			printf("X");
		} else {
			printf(" ");
		}
		printf(" ");
		if(b >= track){
			printf("X");
		} else {
			printf(" ");
		}
		printf(" ");
		if(c >= track){
			printf("X");
		} else {
			printf(" ");
		}
		printf(" ");
		if(d >= track){
			printf("X");
		} else {
			printf(" ");
		}
		printf(" ");
		printf("\n");
		track--;
	}

	/*bottom formatting*/

	printf("---------\n A B C D \n");

	return 0;
}