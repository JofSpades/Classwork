#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef float data;

typedef struct node{

	struct node* up;
	data val;
	struct node* down;

} NODE;

typedef struct head{

	NODE* top;
	NODE* bottom;

}queue;

typedef queue stack;

int isQEmpty(queue* head){

	if(head->top == NULL){

		return TRUE;

	} else {

		return FALSE;

	}

}

data front(queue* head){

	return head->top->val;

}

void removeFront(queue* head){

	NODE* temp = head->top;
	head->top = temp->down;

	free(temp);

}

void addToEnd(queue* head, data inVal){

	NODE* newTemp = (NODE*)malloc(sizeof(NODE));

	newTemp->up = head->bottom;
	newTemp->down = NULL;
	newTemp->val = inVal;

	if(head->top == NULL){

		head->top = newTemp;

	}
	if(head->bottom != NULL){

		head->bottom->down = newTemp;

	}
	head->bottom = newTemp;

}

int isSEmpty(stack* head){

	return isQEmpty(head);

}

data top(stack* head){

	return front(head);

}

void pop(stack* head){

	removeFront(head);

}

void push(stack* head, data inVal){

	addToEnd(head, inVal);
	while(inVal != front(head)){

		addToEnd(head, front(head));
		removeFront(head);

	}

}

int main(int argc, char** argv){

	stack* head = (stack*)malloc(sizeof(stack));
	data inVal = 0.0;
	FILE* src;
	int count = 0;

	head->top = NULL;
	head->bottom = NULL;

	if(argc < 2) {
		printf("Usage: %s <input file name>\n", argv[0]);
		exit(-1);
	}

	src = fopen(argv[1], "r");

	if(src == NULL){

		printf("ERROR: CANNOT READ/OPEN FILE\n");
		exit(-1);

	}

	while((fscanf (src, "%f", &inVal) != EOF)){

		push(head, inVal);

	}

	while(isSEmpty(head) != TRUE){

		data d = top(head);
		if(count == 6){

			printf("\n");
			count = 1;
			printf("%.3f\t", d);
			pop(head);

		} else {

			printf("%.3f\t\t", d);
			pop(head);
			count++;

		}

	}

	printf("\nDONE\n");

}
