#include "simpleio.h"
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int balence(){

	StackPtr balence = stk_create();
	char comp;
	int n = 0;

	printf("ENTER THE STRING YOU NEED CHECKED HERE:\n");

	char *test = get_string();

	//testing for bad initial case

	if(test[0] == '}' || test[0] == ']' || test[0] == ')'){
		
		return 0;
		
	}

	//testing all cases for proper balence by pushing all opening braces and all closing braces call for a 
	//push and compairing to see if they match up

	for (int i = 0; test[i] != '\0'; i++){

		if(test[i] == '{' || test[i] == '[' || test[i] == '('){

			stk_push(balence, test[i]);

			n++

		} else if (test[i] == '}' || test[i] == ']' || test[i] == ')') {

			comp = stk_pop(balence);

			n--;

			if(comp == '{' && test[i] != '}'){

				return 0;

			} else if(comp == '(' && test[i] != ')'){

				return 0;

			} else if(comp == '[' && test[i] != ']'){

				return 0;

			} 

		}

	}

	if(n != 0){

		return 0;

	}

	return 1;

}	

int main(){

	if(balence()){

		printf("PROPERLY BALENCED, GOOD JOB\n");

	} else {

		printf("NOT PROPER, TRY AGAIN\n");

	}

	return 0;
}