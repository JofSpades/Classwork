#include <stdio.h>

int main(int argc, char *argv[]) {

	/*
	   Like said at the start of encode the process is the same except for how the alphabet arrays are made
	   which is explained below
	*/

	if(strlen(argv[1]) != 4){

		printf("************ERROR PIN MUST BE OF LENGTH 4************\nYOU ENTERD A PIN THAT IS EITHER TOO LONG OR TOO SHORT")
	
		return 0;

	}

	srand(atoi(argv[1]));

	int shift = rand() % 25;
	int val = 0;
	char ch;
	int in[26];
	int out[26];

	/*
	   the in[] array is made the same and tehn 
	*/

	for(int i = 0; i < 26; i++){

		in[i] = 97 + i;

	}

	for(int i = 0; i < 26; i++){

		out[i] = in[i] - shift;

		if(out[i] < 97){

			out[i] = 123 - (97 - out[i]);

		}

	}

	while(val != -1){

		ch = getchar();

		val = ch;

		if(val != -1){

			if(isalpha(ch)){

				ch = tolower(ch);

				for(int i = 0; i < 26; i++){


					if(in[i] == ch){

						printf("%i ", out[i]);

						continue;
						
					}

				}

			} else {

				putchar(ch);
				
			}

		}

	}

	return 0;

}