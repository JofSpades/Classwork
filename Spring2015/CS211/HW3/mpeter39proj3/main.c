/*  Code for the user interface for Project 3 for CS 211 Spring 2015  
 *
 *  Author: Pat Troy
 *  Date: 10/6/2013
 *  Modified: Maxwell Petersen
 *  Date:02/25/2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

int main (int argc, char *argv[])
{

 char *input;
 int ch;

 TOP* head = (TOP*) malloc(sizeof(TOP));
 head->top = NULL;
 head->bottom = NULL;
 head->debug = FALSE;

 if(argc == 2){

  if(strncmp(argv[1], "-d", 3) == 0){

    head->debug = TRUE;
    printf("DEBUG MODE ON\n");

  }

}

printf ("Starting Restaurant Wait List Program\n\n");
printf ("Enter command: ");

while ((ch = getNextNWSChar ()) != EOF)
{
    /* check for the various commands */
  if ('q' == ch)
  {
   printf ("Quitting Program\n");
   return (0);
 }
 else if ('?' == ch)
 {
   printCommands();
 }
 else if('a' == ch)
 {
   doAdd(&head);
 } 
 else if('c' == ch)
 {
   doCallAhead(head);
 } 
 else if('w' == ch)
 {
   doWaiting(head);
 } 
 else if('r' == ch)
 {
   doRetrieve(head);
 } 
 else if('l' == ch)
 {
   doList(head);
 } 
 else if('d' == ch)
 {
   doDisplay(head);
 } 
 else
 {
   printf ("%c - in not a valid command\n", ch);
   printf ("For a list of valid commands, type ?\n");
   clearToEoln();
 }

 printf ("\nEnter command: ");
}

printf ("Quiting Program - EOF reached\n");
return 1;
}