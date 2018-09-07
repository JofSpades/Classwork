#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VISITED 0
#define UNVISITED 1

typedef struct mazeStruct
{
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
} maze;

typedef struct depthFirstSearch{

	int xPosition;
	int yPosition;
	struct depthFirstSearch * previousAddress;

} dhfStack;

void push(dhfStack ** pTop, int x, int y){

	dhfStack* pTemp = (dhfStack*)malloc(sizeof(dhfStack));

	pTemp->xPosition = x;
	pTemp->yPosition = y;
	pTemp->previousAddress = *pTop;

  *pTop = pTemp;

}

void pop(dhfStack ** pTop){
  
    if(*pTop != NULL){
        dhfStack* pTemp = (dhfStack*)malloc(sizeof(dhfStack));
        pTemp = *pTop;
        *pTop = pTemp->previousAddress;
        
        free(pTemp);
    }

}

void printStack(dhfStack* p) {
	printf("printing stack:\n");
	while(p != NULL) {
		printf("xPosition: %i, yPosition: %i\n", p->xPosition, p->yPosition);
		printf("previousAddress: %lu\n---------\n\n", (unsigned long) p->previousAddress);
		p = p->previousAddress;
	}
}

void popOff(dhfStack ** pTop, maze *inMaze){
	if(*pTop != NULL){
		popOff(&(*pTop)->previousAddress, inMaze);
		printf("(%d,%d)\n", (*pTop)->xPosition, (*pTop)->yPosition);
		pop(pTop);
	}

}

int main (int argc, char **argv)
{
  maze m1;

  int xpos, ypos;
  int i,j;

  //temp variables to run the check
  int xTemp = 0;
  int yTemp = 0;
  int count = 0;
  int debugmode = 0;

  FILE *src;

  /* verify the proper number of command line arguments were given */
  if(argc < 2 || argc > 3) {
     printf("Usage: %s <input file name>\n", argv[0]);
     exit(-1);
  }

  for(i = 1; i < argc; i++) {
  	if(strncmp(argv[i], "-d", 2) == 0) {
  		debugmode = 1;
  		printf("DEBUGMODE IS ACTIVE:\n");
  	}
  	else {
  		src = fopen(argv[i], "r");
  	}
  }
  if(src == NULL) {
  	printf("ERROR: cannot read file\n");
  }

  

  /* read in the size, starting and ending positions in the maze */
  
  while((fscanf (src, "%d %d", &xTemp, &yTemp) != EOF)){

    int check = 0;

    if((count == 0) && ((xTemp != 0) && (yTemp != 0))){

      m1.xsize = xTemp;
      m1.ysize = yTemp;

      count = 1;
      check = 1;

    } else if((count == 1) && ((xTemp != 0) && (yTemp != 0)) && ((xTemp <= m1.xsize) && (yTemp <= m1.ysize))){

      m1.xstart = xTemp;
      m1.ystart = yTemp;

      count = 2;
      check = 1;

    } else if((count == 2) && ((xTemp != 0) && (yTemp !=0)) && ((xTemp <= m1.xsize) && (yTemp <= m1.ysize)) && ((xTemp != m1.xstart) && (yTemp != m1.ystart))){

      m1.xend = xTemp;
      m1.yend = yTemp;

      count = 3;
      check = 1;

    }

    if(count == 3){
      break;
    }

    if((count == 0) && (check == 0)){

    	fprintf(stderr, "BAD SIZE VALUES CANNOT BE 0: (%d,%d)\n", xTemp, yTemp);

    } else if ((count == 1) && (check == 0)){

    	if((xTemp == 0) || (yTemp ==0)){

    		fprintf(stderr, "BAD START VALUES CANNOT BE 0: (%d,%d)\n", xTemp, yTemp);

    	} if((xTemp > m1.xsize) || (yTemp > m1.ysize)){

    		fprintf(stderr, "BAD START VALUES CANNOT BE BEYOND THE MAXIMUM SIZE VALUES: (%d,%d)\n", xTemp, yTemp);

    	}

    } else if (((m1.xend == 0) && (m1.yend == 0)) && (count == 3) && (check == 0)){

    	if((xTemp == 0) || (yTemp ==0)){

    		fprintf(stderr, "BAD END VALUES CANNOT BE 0: (%d,%d)\n", xTemp, yTemp);

    	} if((xTemp > m1.xsize) || (yTemp > m1.ysize)){

    		fprintf(stderr, "BAD END VALUES CANNOT BE BEYOND THE MAXIMUM SIZE VALUES: (%d,%d)\n", xTemp, yTemp);

    	} if((xTemp == m1.xstart) && (yTemp == m1.ystart)){

    		fprintf(stderr, "BAD END VALUES CANNOT BE THE SAME AS THE START VALUE: (%d,%d)\n", xTemp, yTemp);

    	}

    }

  }
  /* print them out to verify the input */
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  printf ("end: %d, %d\n", m1.xend, m1.yend);

  char** arr;
  arr = malloc((m1.xsize + 2) * sizeof(char*));
  for(i = 0; i < (m1.xsize + 2); i++){

    arr[i] = malloc((m1.ysize + 2) * sizeof(char*));

  }

  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize+2; i++)
     for (j = 0; j < m1.ysize+2; j++)
       arr[i][j] = '.';

  /* mark the borders of the maze with *'s */
  for (i=0; i < m1.xsize+2; i++)
    {
     arr[i][0] = '*';
     arr[i][m1.ysize+1] = '*';
    }
  for (i=0; i < m1.ysize+2; i++)
    {
     arr[0][i] = '*';
     arr[m1.xsize+1][i] = '*';
    }

  /* mark the starting and ending positions in the maze */
  arr[m1.xstart][m1.ystart] = 's';
  arr[m1.xend][m1.yend] = 'e';

  dhfStack * pTop = (dhfStack*)malloc(sizeof(dhfStack));
  pTop->xPosition = m1.xstart;
  pTop->yPosition = m1.ystart;
  pTop->previousAddress = NULL;
		  
  /* mark the blocked positions in the maze with *'s */
  while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
        if (((xpos <= m1.xsize) && (ypos <= m1.ysize))) {
            if(((xpos == m1.xstart) && (ypos == m1.ystart)) || ((xpos == m1.xend) && (ypos == m1.yend))){
                
                if((xpos == m1.xstart) && (ypos == m1.ystart)){
                
                	fprintf(stderr, "BAD BLOCK VALUES CANNOT BE THE START VALUE\n");
                	
        		} else if((xpos == m1.xend) && (ypos == m1.yend)){
                
                	fprintf(stderr, "BAD BLOCK VALUES CANNOT BE THEEND VALUE\n");
        		}

            } else {

            	arr[xpos][ypos] = '*';

            }
        }

        if (((xpos >= m1.xsize) && (ypos >= m1.ysize))) {

    		fprintf(stderr, "BAD BLOCK VALUES CANNOT BE BEYOND THE MAXIMUM SIZE VALUES\n");

        }
     
    }

  /* print out the initial maze */
  for (i = 0; i < m1.xsize+2; i++)
  {
    for (j = 0; j < m1.ysize+2; j++)
      printf ("%c", arr[i][j]);
    printf("\n");
  }

    int unusedArr[m1.xsize + 2][m1.ysize + 2];

  for (i = 0; i < m1.xsize + 2; i++)
  {
    for (j = 0; j < m1.ysize + 2; j++){
        
      unusedArr[i][j] = VISITED;
       
      if(arr[i][j] == '.'){

      	unusedArr[i][j] = UNVISITED;

      }
      if(arr[i][j] == 's'){
            
        unusedArr[i][j] = VISITED;
            
      }
      if(arr[i][j] == 'e'){
            
        unusedArr[i][j] = UNVISITED;
            
      }



    }

  }

  //while we dont have a null amount or we dont have the end element as our current position keep going
  while(pTop != NULL){

    //pop and print the whole stack up to this point
  	if(pTop->xPosition == m1.xend && pTop->yPosition == m1.yend){

  	  printf("SOLUTION FOUND:\n");
      popOff(&pTop, &m1);
  	  return 0;

    //from here until the else are the checks for the depth search
  	} else if (unusedArr[pTop->xPosition][pTop->yPosition - 1] == UNVISITED){

      unusedArr[pTop->xPosition][pTop->yPosition - 1] = VISITED;
		  push(&pTop, pTop->xPosition,pTop->yPosition - 1);
      if(debugmode == 1){

          printf("l(%d,%d)\n", pTop->xPosition, pTop->yPosition);
        
        }

	  } else if (unusedArr[pTop->xPosition + 1][pTop->yPosition] == UNVISITED){

      unusedArr[pTop->xPosition + 1][pTop->yPosition] = VISITED;
		  push(&pTop, pTop->xPosition + 1,pTop->yPosition);
      if(debugmode == 1){

          printf("d(%d,%d)\n", pTop->xPosition, pTop->yPosition);
        
        }

	  } else if (unusedArr[pTop->xPosition][pTop->yPosition + 1] == UNVISITED){

      unusedArr[pTop->xPosition][pTop->yPosition + 1] = VISITED;
		  push(&pTop, pTop->xPosition,pTop->yPosition + 1);
      if(debugmode == 1){

          printf("r(%d,%d)\n", pTop->xPosition, pTop->yPosition);
        
        }

	  } else if (unusedArr[pTop->xPosition - 1][pTop->yPosition] == UNVISITED){

      unusedArr[pTop->xPosition - 1][pTop->yPosition] = VISITED;
		  push(&pTop, pTop->xPosition - 1, pTop->yPosition);
      if(debugmode == 1){

          printf("u(%d,%d)\n", pTop->xPosition, pTop->yPosition);
        
        }
      // if there isnt a found proper value
	  } else {
        if(debugmode == 1){

          printf("p(%d,%d)\n", pTop->xPosition, pTop->yPosition);
        
        }

        pop(&pTop);
	  }

  }

  printf("NO SOLUTIONS FOUND PLESE SUBMIT ANOTHER MAZE\n");

  return 0;

}