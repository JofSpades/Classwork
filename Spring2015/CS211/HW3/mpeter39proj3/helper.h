#include <stdio.h>

typedef enum boolean {
	FALSE,
	TRUE
}boolLabel;

typedef enum status {
	CALL,
	WAIT
} statType;

typedef struct node{

	struct node* up;
	char* name;
	int group;
	statType grpStatus;
	struct node* down;

} NODE;

typedef struct head{

	NODE* top;
	boolLabel debug;
	NODE* bottom;

}TOP;

/*
Add the group to the wait list using the given group size and name specifying the group is waiting in the restaurant.
The group’s information is added to the end of the list.
If the name already exists in the wait list, give an error message and do not add the information.
*/
void doAdd(TOP** head);

/*
Add the group to the wait list using the given group size and name specifying the group as a call ahead group.
The group’s information is added to the end of the list.
If the name already exists in the wait list,give an error message and do not add the information.
*/
void doCallAhead(TOP* head);

/*
Mark the call ahead group using the given name as waiting in the
restaurant.
If the name does not exist is the wait list or is not a call ahead group, give an error message.
*/
void doWaiting(TOP* head);

/*
Retrieve and remove the first group on the wait list that is waiting in the restaurant and is less than or equal to the table size.
Note that “first” is the group that has been in the wait list the longest.
*/
void doRetrieve(TOP* head);

/*
List total number of groups that are in the wait list in front of the group specified by the given name.
Also list the size of each group that are in the wait list ahead of the group specified by the given name.
If the name does not exist, give an error message.
*/
void doList(TOP* head);

/*
Display the total number of groups in the wait list.
Also display the names, group size and in-restaurant status of all groups in the wait list in order from first to last.
*/
void doDisplay(TOP* head);

/*
----------used for linked list----------
*/

/*
This operation is to add a new node to the end of the linked list.
This is to be used when the a and c commands are given as input
*/
void addToList(TOP** head, char* name, int size);

/*
This operation is to return a Boolean value indicating whether a name already exists in the linked list.
This is to be used when the a, c, w and l commands are given as
input.
*/
boolLabel doesNameExist(TOP* head, char* name);

/*
This operation is to change the in-restaurant status when a call-ahead group arrives at the restaurant.
This operation will return a FALSE value if that group is already marked as being in the restaurant.
This is to be used when the w command is given as input.
*/
boolLabel updateStatus(TOP** head , char* name, statType stat);

/*
This operation is to find the first in-restaurant group that can fit at a given table.
This operation is to return the name of group.
This group is to be removed from the linked list.
This is to be used when the r command is given as input.
*/
char* retrieveAndRemove(TOP** head, int grpSize);

/*
This operation is to return the number of groups waiting ahead of a group with a specific name.
This is to be used when the l command is given as input.
*/
int countGroupsAhead(TOP* head, char* name);

/*
This operation traverses down the list until a specific group name is encountered.
As each node is traversed, print out that node’s group size. This command is to be used when the l command is given.
*/
boolLabel displayGroupSizeAhead(TOP* head, char* name);

/*
This operation to traverse down the entire list from beginning to end.
As each node is traversed, print out that node’s group name, group size and in-restaurant status.
This command is to be used when the d command is given as input.
*/
void displayListInformation(TOP* head);