#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){

	char *animals[] = {"frog", "cat", "dog", "horse", "eagle", "bear", "weasel", "child"};
	char *temp;
	int w, x, y, z;

	for(int i = 0; i < 8; i++){

		srand(time(NULL));

		w=rand() % 7;
		x=rand() % 7;
		y=rand() % 7;
		z=rand() % 7;

		temp = animals[i];
		animals[i] = animals[7];
		animals[7] = temp;

		temp = animals[x];
		animals[x] = animals[y];
		animals[y] = temp;

		temp = animals[w];
		animals[w] = animals[z];
		animals[z] = temp;

	}

	printf("A %s couldn't sleep, so her mother told a story about a little %s,\n", animals[0], animals[1]);
	printf("\twho couldn't sleep, so the %s's mother told a story about a little %s,\n", animals[1], animals[2]);
	printf("\t\twho couldn't sleep, so the %s's mother told a story about a little %s,\n", animals[2], animals[3]);
	printf("\t\t\t...who fell asleep.\n");
	printf("\t\t...and the little %s fell asleep;\n", animals[2]);
	printf("\t...and the little %s fell asleep;\n", animals[1]);
	printf("...and the %s fell asleep.\n", animals[0]);

	return 0;
}