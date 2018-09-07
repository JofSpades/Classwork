#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

/* Clear input until next End of Line Character - \n */
 void clearToEoln()
 {
   int ch;

   do {
     ch = getc(stdin);
   }
   while ((ch != '\n') && (ch != EOF));
 }

/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
 *      space, tab \t, newline \n, vertical tab \v, 
 *      form feed \f, and carriage return \r
 */ 
int getNextNWSChar ()
{
 int ch;

 ch = getc(stdin);
 if (ch == EOF)
  return ch;
 while (isspace (ch))
 {
  ch = getc(stdin);
  if (ch == EOF)
  return ch;
 }
 return ch;
}

/* read in the next Positive Integer or error:    */
/* This is based on the Mathematical definition of a Postive Integer */
/*    zero is not counted as a positive number */ 
int getPosInt ()
{
 int value = 0;

 /* clear white space characters */
 int ch;
 ch = getc(stdin);
 while (!isdigit(ch))
 {
    if ('\n' == ch)  /* error \n ==> no integer given */
   return 0;
    if (!isspace(ch)) /* error non white space ==> integer not given next */
   {
     clearToEoln();
     return 0;
   }
   ch = getc(stdin);
 }

 value = ch - '0';
 ch = getc(stdin);
 while (isdigit(ch))
 {
  value = value * 10 + ch - '0';
  ch = getc(stdin);
 }

 ungetc (ch, stdin);  /* put the last read character back in input stream */

 /* Integer value of 0 is an error in this program */
 if (0 == value)
  clearToEoln();

 return value;
}

/* read in the name until the end of the input */
char *getName()
{
 /* skip over the white space characters */
 int ch;
 ch = getc(stdin);
 while (isspace(ch))
 {
    if ('\n' == ch)  /* error \n ==> no integer given */
   return NULL;
   ch = getc(stdin);
 }

 char *word;
 int size;
 size = 10;
 word = (char *) malloc (sizeof(char) * size);

 // read in character-by-character until the newline is encountered
 int count = 0;

 while (ch != '\n')
 {
  if (count+1 >= size)
  {
       // to grow an array to make it "dynamically sized" using malloc
   char* temp;
   int i;
   size = size * 2;
   temp = (char *) malloc (sizeof(char) * size);

       // printf ("Growing array from size %d to size %d\n", count, size);
       // copy the characters to the new array
   for (i = 0 ; i < count ; i++)
     temp[i] = word[i];

   free (word);
   word = temp;
 }

 word[count] = ch;
 count++;
 word[count] = '\0';

    // read next character
 ch = getc(stdin);
 }

 if (count > 30)
 {
  count = 30;
  word[count] = '\0';
 }

 /* clear ending white space characters */
 while (isspace (word[count-1]))
 {
  count--;
  word[count] = '\0';
 }

 return word;
}

/* Print out a list of the commands for this program */
void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("a <size> <name> - to add a group to the wait list\n");
 printf ("c <size> <name> - to add a call-ahead group to the wait list\n");
 printf ("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
 printf ("r <table-size> - to retrieve the first waiting group that can fit at the available table size\n");
 printf ("l <name> - list how many groups are ahead of the named group\n");
 printf ("d - display the wait list information\n");

 /* clear input to End of Line */
 clearToEoln();
}

void doAdd(TOP** head)
{
 /* get group size from input */
 int size = getPosInt();
 if (size < 1)
 {
  printf ("Error: Add command requires an integer value of at least 1\n");
  printf ("Add command is of form: a <size> <name>\n");
  printf ("  where: <size> is the size of the group making the reservation\n");
  printf ("         <name> is the name of the group making the reservation\n");
  return;
 }

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
 {
  printf ("Error: Add command requires a name to be given\n");
  printf ("Add command is of form: a <size> <name>\n");
  printf ("  where: <size> is the size of the group making the reservation\n");
  printf ("         <name> is the name of the group making the reservation\n");
  return;
 }

 printf ("Adding group \"%s\" of size %d\n", name, size);

 addToList(head, name, size);
}

void doCallAhead(TOP* head)
{
 /* get group size from input */
 int size = getPosInt();
 if (size < 1)
 {
  printf ("Error: Call-ahead command requires an integer value of at least 1\n");
  printf ("Call-ahead command is of form: c <size> <name>\n");
  printf ("  where: <size> is the size of the group making the reservation\n");
  printf ("         <name> is the name of the group making the reservation\n");
  return;
 }

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
 {
  printf ("Error: Call-ahead command requires a name to be given\n");
  printf ("Call-ahead command is of form: c <size> <name>\n");
  printf ("  where: <size> is the size of the group making the reservation\n");
  printf ("         <name> is the name of the group making the reservation\n");
  return;
 }

 printf ("Call-ahead group \"%s\" of size %d\n", name, size);

 statType inGrpStatus = CALL;
 addToList(&head, name, size);
 updateStatus(&head, name, inGrpStatus);

}

void doWaiting(TOP* head)
{
 /* get group name from input */
 char *name = getName();
 if (NULL == name)
 {
  printf ("Error: Waiting command requires a name to be given\n");
  printf ("Waiting command is of form: w <name>\n");
  printf ("  where: <name> is the name of the group that is now waiting\n");
  return;
 }

 printf ("Waiting group \"%s\" is now in the restaurant\n", name);

 statType inGrpStatus = WAIT;

 NODE* tempNode = head->top;

 while(tempNode != NULL){

  if(tempNode->name == name){

    if(tempNode->grpStatus == CALL){

     updateStatus(&head, name, inGrpStatus);
    
    } else {

      printf("ALL READY ON WAITING LIST\n");

    }

  }

 }
}

void doRetrieve(TOP* head)
{
 /* get table size from input */
 int size = getPosInt();
 if (size < 1)
 {
  printf ("Error: Retrieve command requires an integer value of at least 1\n");
  printf ("Retrieve command is of form: r <size>\n");
  printf ("  where: <size> is the size of the group making the reservation\n");
  return;
 }
 clearToEoln();
 printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

 char* removed = retrieveAndRemove(&head, size);

 if(removed == NULL){

  printf("LIST IS EMPTY\n");

 } else {

  printf("%s's group has a table ready for them", removed);
  
 }
 
}

void doList(TOP* head)
{
 /* get group name from input */
 char *name = getName();
 if (NULL == name)
 {
  printf ("Error: List command requires a name to be given\n");
  printf ("List command is of form: l <name>\n");
  printf ("  where: <name> is the name of the group to inquire about\n");
  return;
 }

 int grpcount = countGroupsAhead(head, name);
 if(grpcount > 0){
  printf ("Group \"%s\" is behind: %d groups.\n", name, grpcount);
  
  if(grpcount > 1){

    printf("The sizes are listed here:\n");

  } else {

    printf("The size is listed here:\n");

  }

  displayGroupSizeAhead(head, name);

 }
}

void doDisplay(TOP* head)
{
 clearToEoln();
 printf ("Display information about all groups\n");

 displayListInformation(head);
}
