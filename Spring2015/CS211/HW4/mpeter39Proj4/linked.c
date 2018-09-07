#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

void pushC(TOKEN** head, char in){

	TOKEN* tempNode = (TOKEN*)malloc(sizeof(TOKEN));

	tempNode->op = in;

	tempNode->down = *head;

  	*head = tempNode;
  	// printf("%c\n", (*head)->op);

}

void pushV(TOKEN** head, int in){

	TOKEN* tempNode = (TOKEN*)malloc(sizeof(TOKEN));

	tempNode->val = in;

	tempNode->down = *head;

  	*head = tempNode;
  	// printf("%d\n", (*head)->val);
}

void pop(TOKEN** head){

	if(*head != NULL){
        TOKEN* pTemp =  *head;
        *head = pTemp->down;
        
        free(pTemp);
    }

}

int isSEmpty(TOKEN* head){

	if(head == NULL){

		return TRUE;

	} else {

		return FALSE;

	}

}

char frontO(TOKEN* head){

	return head->op;

}

int frontV(TOKEN* head){

	if(head == NULL){

		printf("ERROR: NO VALUES IN STACK\n");

		return -999;

	}

	return head->val;

}

int eval(int x, char op, int y){

	if( op == '+'){

		return x + y;

	} else if( op == '-'){

		return x - y;

	}  else if( op == '*'){

		return x * y;

	} else if( op == '/'){

		return x / y;

	} else {

		printf("ERROR: IMPROPER OPERATOR FOUND\n");
		int out = -999;
		return out;

	}
}

void popAndEval(TOKEN** operators, TOKEN** values){

	char op = frontO(*operators);
	pop(operators);
	int v2 = frontV(*values);
	pop(values);
	int v1 = frontV(*values);
	pop(values);

	int v3 = eval(v1, op, v2);
	pushV(values, v3);

}
