#include <stdio.h>
#include <stdlib.h>

void printOut(char *prev, int depth, int width, int count){

	char buf[200];

	sprintf(buf, "%s", prev);

	for(int i = 0; i < width; i++){

		for(int j = 0; j < count; j++){

			printf("\t");

		}

		if((count % 2 == 1)){

			sprintf(buf, "%s.%c", prev, 65 + i);

		} else if ((count % 2 == 0)){

			sprintf(buf, "%s.%i", prev, i + 1);

		}

		printf("%s\n", buf);

		if(depth > 1){

			printOut(buf, depth - 1, width, count + 1);
		}

	}

}

int main(int argc, char *argv[]){

	int depth = atoi(argv[1]);
	int width = atoi(argv[2]);
	int count = 1;
	char start[200];

	if(depth > 10 || width > 26 || depth < 1 || width < 1){

		printf("OUT OF BOUNDS!!\n");

		return 0;
	}

	for(int i = 0; i < width; i++){

		printf("Section %i\n", i + 1);

		sprintf(start, "Section %i", i + 1);

		printOut(start, depth - 1, width, count);

	}

	return 0;

}