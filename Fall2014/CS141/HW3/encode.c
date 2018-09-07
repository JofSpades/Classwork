#include <stdio.h>

/* The majority of this code and the code for decode are the same */

int main(int argc, char *argv[]) {

	// Here I have a test for the length of the pin to make sure it is valid if not i end the program here

	if(strlen(argv[1]) != 4){

		printf("************ERROR PIN MUST BE OF LENGTH 4************\nYOU ENTERD A PIN THAT IS EITHER TOO LONG OR TOO SHORT")
	
		return 0;

	}

	/* 
	   I make 2 ararys here one is for the input which in this case is a standard alphabet
	   the second one will have the shifted value which was made by the use of the srand
	   and the atoi function, which converts teh ASCII input of the pin to a usuable intager,

	   I made use of the % 25 to gaurentee that the shift amount will be inbetween 1 and 25 making
	   sure that there is infact a change between the input and output  
	*/ 

	srand(atoi(argv[1]));

	int shift = rand() % 25;
	int val = 0;
	char ch;
	int in[26];
	int out[26];

	for(int i = 0; i < 26; i++){

		in[i] = 97 + i;

	}

	for(int i = 0; i < 26; i++){

		out[i] = in[i] + shift;

		if(out[i] > 122){

			out[i] = 96 + (out[i] - 122);

		}

	}

	/*
	   Once the input and output array have been made I run a series of checks for what the value should be
	*/

	while(val != -1){

		/*
		   While val(seen below) is not given the end of file key (-1) then the loop keeps going.
		*/

		ch = getchar();

		val = ch;

		/*
		   I dont want to run the conversion from one alphabet to another so I make sure here that
		   val is not -1 and then the while loop will end after these checks are skipped
		*/

		if(val != -1){

			/*
			   I check here to make sure that the charcter that once made lower case is given will
			   be in the alphabet made in the in[] array
			*/

			if(isalpha(ch)){

				//the said above conversion to lowercase

				ch = tolower(ch);

				for(int i = 0; i < 26; i++){

					/*
					   this loop is where I go through the in[] array and when the char is found
					   it is made to be the out[i] element which with how I set up the out[] array
					   will be the properly shifted charcter
					*/

					if(in[i] == ch){

						/*
						   to cut down on processing time I have the out[i] char outputted right here
						   then have the for loop that this if statement is in skipped over
						*/

						putchar(out[i]);

						continue;
						
					}

				}

			} else {

				/*
				   if the char bought into the program by the getchar() function above is not an alphabetic
				   character I just output the char right back into the output file 
				*/

				putchar(ch);

			}

		}

	}

	return 0;

}