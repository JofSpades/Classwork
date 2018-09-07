
#include <stdio.h>
#include "arr_util.h"



int main(){

	int sorted[10] = {1,2,3,4,5,6,7,8,9,10};
	int nonSorted[10] = {1,2,5,3,4,6,7,8,9,10};

	if(is_sorted(sorted, 10)){

		printf("W00T its fine!!!!\n");

	} else {

		printf("Damn Dawg you dun fucked up!\n");

	}

	if(is_sorted(nonSorted, 10)){

		printf("W00T its fine!!!!\n");

	} else {

		printf("Damn Dawg you dun fucked up!\n");

	}

	int data[5] = {3,19,6,5,7};
	int data2[5] = {3,5,7,19,6};
	int data3[5] = {3,3,3,3,3};
	int data4[5];

	for(int i = 0; i < 5; i++){

		data4[i] = data[i];
	}

	histogram(data, 5);

	printf("%i\n", num_distinct(data,5));
	printf("%i\n", num_distinct(data3,5));

	if(same_contents(data, data, 5)){

		printf("W00T its fine!!!!\n");

	} else {

		printf("Damn Dawg you dun fucked up!\n");

	}

	if(same_contents(data, data2, 5)){

		printf("W00T its fine!!!!\n");

	} else {

		printf("Damn Dawg you dun fucked up!\n");

	}

	if(same_contents(data, data3, 5)){

		printf("W00T its fine!!!!\n");

	} else {

		printf("Damn Dawg you dun fucked up!\n");

	}

	for(int i = 0; i < 5; i++){

		printf("%i,", data4[i]);
	}

	printf("\n");

	rotate_right(data4, 5);
	
	for(int i = 0; i < 5; i++){

		printf("%i,", data4[i]);
	}

	printf("\n"); 

}
