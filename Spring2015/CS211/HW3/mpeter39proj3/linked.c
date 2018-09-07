#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

void debug(NODE* node){

	char stat;

	if(node->grpStatus == CALL){

		stat = 'C';

	} else if (node->grpStatus == WAIT){

		stat = 'W';

	}
	printf("NAME: %s SIZE: %d STATUS: %c\n", node->name, node->group, stat);

}

void addToList(TOP** head, char* name, int size){

	//malloc new node
	NODE* tempNode = (NODE*)malloc(sizeof(NODE));

	if((*head)->top == NULL){

		(*head)->top = tempNode;

	}
	//connect tempNode to the end of the list
	tempNode->up = (*head)->bottom;

	if((*head)->bottom != NULL){

		(*head)->bottom->down = tempNode;
	}
	(*head)->bottom = tempNode;
	tempNode->down = NULL;
	//filling in data
	tempNode->name = name;
	tempNode->group = size;
	tempNode->grpStatus = WAIT;

}

boolLabel doesNameExist(TOP* head, char* name){

	NODE* tempNode = head->top;

	if(head->debug == TRUE){

		printf("DEBUG:\n");

	}

	while(tempNode != NULL){

		if(head->debug == TRUE){

			debug(tempNode);

		}

		if(strncmp(tempNode->name, name, 50) == 0){

			return TRUE;

		}

		tempNode = tempNode->down;

	}


	return FALSE;

}

boolLabel updateStatus(TOP** head ,char* name, statType stat){

	if(doesNameExist((*head), name) == TRUE){

		if((*head)->debug == TRUE){

			printf("DEBUG:\n");

		}

		NODE* tempNode = (*head)->top;

		while(tempNode != NULL){

			if((*head)->debug == TRUE){

				debug(tempNode);

			}

			if(strncmp(tempNode->name, name, 50) == 0){

				tempNode->grpStatus = stat;
				if((*head)->debug == TRUE){

					printf("SUCCESS\n");

				}
				return TRUE;

			}

			tempNode = tempNode->down;

		}

		if((*head)->debug == TRUE){

			printf("FAILURE\n");

		}
		return FALSE;

	}

}

char* retrieveAndRemove(TOP** head, int grpSize){

	NODE* tempNode = (*head)->top;

	char* foundName;

	while(tempNode != NULL){

		if(grpSize >= tempNode->group && tempNode->grpStatus == WAIT){

			foundName = tempNode->name;

			if(tempNode->up != NULL){

				tempNode->up->down = tempNode->down;

			} if(tempNode->down != NULL){

				tempNode->down->up = tempNode->up;

			}else {

				(*head)->top = tempNode->down;

			}

			if((*head)->top == tempNode){
				
				(*head)-> top = tempNode->down;

			}
			free(tempNode);
			return foundName;

		}

		tempNode = tempNode->down;

	}

}

int countGroupsAhead(TOP* head, char* name){

	NODE* tempNode = head->top;
	int count = -1;

	if(doesNameExist(head, name) == TRUE){

		count = 0;

		while(tempNode != NULL){

			if(head->debug == TRUE){

				debug(tempNode);

			}

			if(strncmp(tempNode->name, name, 50) == 0){

				return 0;

			}

			count++;

			tempNode = tempNode->down;

		}

	}

}

boolLabel displayGroupSizeAhead(TOP* head, char* name){

	NODE* tempNode = head->top;

	if(doesNameExist(head, name) == TRUE){

		while(tempNode != NULL){

			if(strncmp(tempNode->name, name, 50) == 0){

				return TRUE;

			}

			
			if(tempNode != NULL){

				printf("---------------------------------------\n");
				printf("GROUP SIZE:   %d\n", tempNode->group);
				printf("---------------------------------------\n\n");

			}

			tempNode = tempNode->down;

		}

	}

}

void displayListInformation(TOP* head){

	NODE* tempNode = head->top;

	while(tempNode != NULL){

		printf("---------------------------------------\n");
		printf("GROUP NAME:   %s\n", tempNode->name);
		printf("GROUP SIZE:   %d\n", tempNode->group);
		printf("----------------------------------------\n\n");

		tempNode = tempNode->down;

	}

}