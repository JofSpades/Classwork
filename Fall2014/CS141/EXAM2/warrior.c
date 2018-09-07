#include <string.h>
#include <stdio.h>

//pt1

typedef struct{
	
	_Bool evil;
	int str;
	char *name;

}WARRIOR;

//pt2

void print(WARRIOR *w){

	printf("Name:     %s\n", w->name);
	printf("Strength: %i\n", w->str);
	
	if(w->evil == 1){

		printf("EVIL\n");

	} else if (w->evil == 0){

		printf("GOOD\n");

	}

}

void feed(WARRIOR *w, int f){
	
	w->str += f;

}

void convert(WARRIOR *w){
	
	if(w->evil == 1){

		w->evil = 0;

	} else if(w->evil == 0){

		w->evil = 1;

	}

}

//pt3

void main(){

	WARRIOR w1 = {1, 10, "Bob"};
	WARRIOR w2 = {1, 10, "Alice"};

	WARRIOR *bob = &w1;
	WARRIOR *alice = &w2;

	print(bob);
	print(alice);

	feed(alice, 2);

	convert(bob);

}