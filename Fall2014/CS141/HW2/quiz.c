#include "simpleio.h"
#include <stdio.h>
#include <time.h>

int main (){

	srand( (unsigned)time(NULL));

	int check = 0;

	while(check != 4){
		printf("\nMake a choice below\n");
		printf("1. Give me an addition problem...\n");
		printf("2. Give me a subtraction problem...\n");
		printf("3. Give me a multiplication problem...\n");
		printf("4. Exit program...\n\n  ");

		check = get_int();

		if(check == 1){

			int count = 0;
			int a = rand() % 101;
			int b = rand() % 101;
			int c = a + b;
			printf("\n%i + %i = ?\n", a, b);
			do{
				int d = get_int();
				if(d == c){
					printf("Good Job!\n");
					break;
				} else {
					count++;
					printf("Please try again\n");
					if(count == 5){
						printf("You are out of tries...\n");
						break;
					}
					printf("You have %i tries remaining...\n", 5 - count);
					printf("\n%i + %i = ?\n", a, b);
				}
			}while(count > 1 || count < 6);		
		}
		if(check == 2){

			int count = 0;
			int a = rand() % 101;
			int b = rand() % 101;
			int c = a - b;
			printf("\n%i - %i = ?\n", a, b);
			do{
				int d = get_int();
				if(d == c){
					printf("Good Job!\n");
					break;
				} else {
					count++;
					printf("Please try again\n");
					if(count == 5){
						printf("You are out of tries...\n");
						break;
					}
					printf("You have %i tries remaining...\n", 5 - count);
					printf("\n%i - %i = ?\n", a, b);
				}
			}while(count > 1 || count < 6);		
		}
		if(check == 3){

			int count = 0;
			int a = rand() % 101;
			int b = rand() % 101;
			int c = a * b;
			printf("\n%i * %i = ?\n", a, b);
			do{
				int d = get_int();
				if(d == c){
					printf("Good Job!\n");
					break;
				} else {
					count++;
					printf("Please try again\n");
					if(count == 5){
						printf("You are out of tries...\n");
						break;
					}
					printf("You have %i tries remaining...\n", 5 - count);
					printf("\n%i * %i = ?\n", a, b);
				}
			}while(count > 1 || count < 6);		
		}
	}

	printf("goodbye\n");

	return 0;
}