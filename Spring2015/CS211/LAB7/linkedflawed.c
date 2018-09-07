#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define FALSE 0
#define TRUE  1


struct linkedStruct
{
 int elem;
 struct linkedStruct*  next;
};
 
typedef struct linkedStruct linked;
typedef linked* linkedPtr; 

void push (linkedPtr* hd, int val)
{
 linkedPtr ptr = (linkedPtr) malloc (sizeof(linked));
 ptr->elem = val;
 ptr->next = *hd;
 *hd = ptr;
}

int isEmpty (linkedPtr hd)
{
 if (hd == NULL)
   return TRUE;
 else
   return FALSE;
}


int top (linkedPtr hd)
{
 return (hd->elem);
}

void pop (linkedPtr* hd)
{
 linkedPtr tmp = *hd;
 hd* = hd->next;
 free (tmp);
}

void show (linkedPtr hd)
{
 while (hd != NULL)
   {
    printf ("%d, ", hd->elem);
    hd = hd->next;
   }
 printf ("\n");
}

int main (int argc, char**argv)
{
  linkedPtr head = NULL;
  int i;
  int temp;

  /* push 10 random values onto the stack showing the stack growing */
  for (i = 0 ; i < SIZE; ++i)
    {
     temp = rand() % 100;
     printf ("In main(): temp: %6d\n", temp);
     push (&head, temp);
     show (head);
    }

  printf ("\n");

  /* remove the value from the stact */
  while (!isEmpty(head))
    {
     printf ("Top of stact value is: %d\n", top(head));
     pop (&head);
    }

}
