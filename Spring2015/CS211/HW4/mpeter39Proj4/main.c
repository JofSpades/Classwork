/*  Code for the user interface for Lab 4 for CS 211 Spring 2015  
 *
 *  Author: Pat Troy
 *  Original Date: 10/13/2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

TOKEN getInputToken (FILE *in);

void processExpression (TOKEN inputToken, FILE *in, boolean inDebug)
{
  /**********************************************/
  /* Declare both stack head pointers here      */
 
  TOKEN* operators = NULL;
  TOKEN* values= NULL;

  /* Loop until the expression reaches its End */
 while (inputToken.type != EOLN)
   {
    /* The expression contains an OPERATOR */
    if (inputToken.type == OPERATOR)
      {
       /* make this a debugMode statement */
        if(inDebug == TRUE){

          printf ("OP:%c, " ,inputToken.op);

        }

       // add code to perform this operation here
        if(inputToken.op == '('){
          pushC(&operators, inputToken.op);
        }
        if(inputToken.op == '+' || inputToken.op == '-'){

          while((isSEmpty(operators) != TRUE) && ((frontO(operators) == '+') || (frontO(operators) == '-') || (frontO(operators) == '/') || (frontO(operators) == '*'))){

            popAndEval(&operators, &values);

          }

          pushC(&operators, inputToken.op);

        }
        if(inputToken.op == '*' || inputToken.op == '/'){

          while((isSEmpty(operators) != TRUE) && ((frontO(operators) == '/') || (frontO(operators) == '*'))){

            popAndEval(&operators, &values);

          }

          pushC(&operators, inputToken.op);

        }
        if(inputToken.op == ')'){

          while((isSEmpty(operators) != TRUE) && !(frontO(operators) == '(')){

            popAndEval(&operators, &values);

          }

          if(isSEmpty(operators) == TRUE){

            printf("ERROR: UNBALENCED PARENTHESIS FOUND\n");

          } else {

            pop(&operators);

          }

        }

      }

    /* The expression contain a VALUE */
    else if (inputToken.type == VALUE)
      {
       /* make this a debugMode statement */
        if(inDebug == TRUE){

          printf ("Val: %d, ", inputToken.val); 

        }
       
        pushV(&values, inputToken.val);
       // add code to perform this operation here

      }
   
    /* get next token from input */
    inputToken = getInputToken (in);
   } 

 /* The expression has reached its end */

   while(!isSEmpty(operators)){

    popAndEval(&operators,& values);

   }

   int endVal = frontV(values);
   printf("%d\n", endVal);
   pop(&values);

   if(!isSEmpty(values)){

    printf("ERROR: VALUES STILL REMAIN\n");

   } else {

    free(operators);
    free(values);
   
   }

 printf ("\n");
}


/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

TOKEN getInputToken (FILE *in)
{
 TOKEN retToken;
 retToken.type = QUIT;

 int ch;
 ch = getc(in);
 if (ch == EOF)
   return retToken;
 while (('\n' != ch) && isspace (ch))
   {
    ch = getc(in);
    if (ch == EOF)
      return retToken;
   }
 
 /* check for a q for quit */
 if ('q' == ch)
   {
    retToken.type = QUIT;
    return retToken;
   }

 /* check for a ? for quit */
 if ('?' == ch)
   {
    retToken.type = HELP;
    return retToken;
   }

 /* check for the newline */
 if ('\n' == ch)
   {
    retToken.type = EOLN;
    return retToken;
   }

 /* check for an operator: + - * / ( ) */
 if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) )
   {
    retToken.type = OPERATOR;
    retToken.op = ch;
    return retToken;
   }
   
 /* check for a number */
 if (isdigit(ch))
   {
    int value = ch - '0';
    ch = getc(in);
    while (isdigit(ch))
      {
       value = value * 10 + ch - '0';
       ch = getc(in);
      }
    ungetc (ch, in);  /* put the last read character back in input stream */
    retToken.type = VALUE;
    retToken.val = value;
    return retToken;
   }
      
 /* else token is invalid */
 retToken.type = ERROR;
 return retToken;
}

/* Clear input until next End of Line Character - \n */
void clearToEoln(FILE *in)
{
 int ch;
 
 do {
     ch = getc(in);
    }
 while ((ch != '\n') && (ch != EOF));
}

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

int main (int argc, char **argv)
{

 char *input;
 TOKEN inputToken;

 printf ("Starting Expression Evaluation Program\n\n");

  boolean inDebug = FALSE;

  if(argc == 2){

  if(strncmp(argv[1], "-d", 3) == 0){

    inDebug = TRUE;
    printf("DEBUG MODE IS ACTIVE\n");

  } else {

    printf("WRONG FLAG IGNORING\n");

  }

  }else if (argc > 2){

  printf("TOO MANY INPUTS IGNORING ALL\n");

  }

 printf ("Enter Expression: ");

 inputToken = getInputToken (stdin);
 while (inputToken.type != QUIT)
   {
    /* check first Token on Line of input */
    if(inputToken.type == HELP)
      {
       printCommands();
       clearToEoln(stdin);
      }
    else if(inputToken.type == ERROR)
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       clearToEoln(stdin);
      }
    else if(inputToken.type == EOLN)
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
    else 
      {
       processExpression(inputToken, stdin, inDebug);
      } 

    printf ("\nEnter Expression: ");
    inputToken = getInputToken (stdin);
   }

 printf ("Quitting Program\n");
 return 1;
}