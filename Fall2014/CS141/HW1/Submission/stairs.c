#include "simpleio.h"
#include <stdio.h>


int main() {

	printf("Enter number of stairs:  ");
	int countStart = get_int();

	for(int i = 0; i < 3; i++){

		if(i == 0){

			printf("up:\n\n");

			int a = countStart - 1;

			for(int j = 0; j < countStart; j++){

				for(int k = 0; k < a; k++){
					printf(" ");
				}

				for(int k = 0; k < countStart - a; k++)	{
					printf("*");
				}			

				printf("\n");

				a = a - 1;

			}

		}

		if(i == 1){

			printf("down:\n\n");

			int a = countStart - 1;

			for(int j = 0; j < countStart; j++){

				for(int k = 0; k < countStart - a; k++)	{
					printf("*");
				}

				for(int k = 0; k < a; k++){
					printf(" ");
				}			

				printf("\n");

				a = a - 1;

			}

		}

		if(i == 2){

			int countEnd = (countStart * 2) - 1;
			int a = countStart - 1;

			printf("up then down:\n\n"); 

			for(int j = 0; j < countStart; j++){

				for(int k = 0; k < a; k++){
					printf(" ");
				}

				for(int k = 0; k < countEnd - (a * 2); k++)	{
					printf("*");
				}

				for(int k = 0; k < a; k++){
					printf(" ");
				}

				a--;			

				printf("\n");
				
			}

		}

	}

	printf("goodbye\n");

	return 0;
}
