
#include <stdio.h>
#include <stdlib.h>
#include "bboard.h"

#define MAX_ROWS 40
#define MAX_COLS 40

struct bboard {

	int numrows;
	int numcols;
	int score;
	int oldScore;
	int count;

	char boardArr[MAX_ROWS][MAX_COLS];
	char undoPop[MAX_ROWS][MAX_COLS];

};

#define None ' '
#define Red  '^'
#define Blue '='
#define Green 'o'
#define Yellow '+'


/**
* Function:  bb_create
* Parameters: number of rows and columns
* Description: returns pointer to newly created
*              board with given number of rows
*              and columns.
*
*              Populates board with random balloons.
*
*              If nrows or ncols is out of range, 
*              an error message is printed to stderr
*              and NULL is returned.
*
*/
BBoard bb_create(int nrows, int ncols){

	if(nrows > MAX_ROWS || ncols > MAX_COLS || nrows < 1 || ncols < 1){

		printf("OUT OF BOUNDS\n");

		return NULL;

	} else {

		BBoard board = malloc(sizeof(struct bboard));

		board->numcols = ncols;
		board->numrows = nrows;
		board->score = 0;
		board->count = 0;

		char inputVal;

		for(int i = 0; i < nrows; i++){

			for(int j = 0; j < ncols; j++){
				
				int test = (rand() % 4) + 1;

				switch (test){

					case 1:
					inputVal = Red;
					break;

					case 2:
					inputVal = Blue;
					break;

					case 3:
					inputVal = Green;
					break;

					case 4:
					inputVal = Yellow;
					break;

					default:
					break;

				}

				board->boardArr[i][j] = inputVal;

			}

		}

		return board;

	}

}

/**
* Function:  bb_create_from_mtx
* Parameters: number of rows and columns
* Description: returns pointer to newly created
*              board with given number of rows
*              and columns.
*
*              Populates board with random balloons.
*
*              If nrows or ncols is out of range, 
*              an error message is printed to stderr
*              and NULL is returned.
*
*/
BBoard bb_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols){

	if(nrows > MAX_ROWS || ncols > MAX_COLS || nrows < 1 || ncols < 1){

		printf("OUT OF BOUNDS\n");

		return NULL;

	} else {

		BBoard board = malloc((sizeof(struct bboard)) * (sizeof(struct bboard)));

		board->numcols = ncols;
		board->numrows = nrows;
		board->score = 0;

		for(int i = 0; i < nrows; i++){

			for(int j = 0; j < ncols; j++){

				board->boardArr[i][j] = mtx[i][j];

			}

		}

		return board;

	}

}

/**
* Function:  bb_clear
* Description:  sets all slots to be empty (None)
*               sets score to zero
*
*/
int bb_clear(BBoard b){

	for(int i = 0; i < b->numrows; i++){

		for(int j = 0; j < b->numcols; j++){

			b->boardArr[i][j] = None;
		}
	}

	b->score = 0;

	return 1;
}

/**
* Function:  bb_destroy
* Description:  deallocates all dynamically allocated 
*  		memory associated with the board.
*		
*		Comment:  this might start out as
*		a one-liner.
*
*/
void bb_destroy(BBoard b){

	free(b);

}

void topBottom(int col){

	printf("\t\t   +");
	for(int i = 0; i < (col * 2) + 1; i++){

		printf("-");

	}

	printf("+\n");

}

 /**
* Function:  bb_display
* Description:  pretty-prints the current board.
*
*		uses '|', '+' and '-' to "draw" the boundaries
*               of the board.
*
*		For full credit rows and columns are labeled with
* 		their indices.  Column indices displayed "vertically"
*
*		Examples:
*
*  This board is full of balloons (like at the beginning of a game).
* 
*           +-----------------------+
*		  0 | + + + = + ^ ^ o + = = |
*		  1 | ^ = = o + o + + + ^ = |
*		  2 | ^ + ^ o + o + = = = = |
*		  3 | = ^ o o = o + + + = = |
*		    +-----------------------+
* 		      0 0 0 0 0 0 0 0 0 0 1
*		      0 1 2 3 4 5 6 7 8 9 0
*
*
*  This board has some empty slots represented by  '.'
*           +-----------------------+
*		  0 | + + + = + ^ ^ o + = = |
*		  1 | ^ = o o + o + + + ^ = |
*		  2 | ^ + . o + . + = . . = |
*		  3 | . . . o . . + + . . = |
*		    +-----------------------+
* 		      0 0 0 0 0 0 0 0 0 0 1
*		      0 1 2 3 4 5 6 7 8 9 0
*
*
*  Here is the same board using a space ' ' to 
*  represent an empty slot.
*
*           +-----------------------+
*		  0 | + + + = + ^ ^ o + = = |
*		  1 | ^ = o o + o + + + ^ = |
*		  2 | ^ +   o +   + =     = |
*		  3 |       o     + +     = |
*		    +-----------------------+
* 		      0 0 0 0 0 0 0 0 0 0 1
*		      0 1 2 3 4 5 6 7 8 9 0
*
*/
void bb_display(BBoard b){

	topBottom(b->numcols);

	for(int i = 0; i < b->numrows; i++){

		printf("\t\t");

		if((i + 1) < 10){

			printf("0%i | ", i+1);

		} else {

			printf("%i | ", i+1);

		}		

		for(int j = 0; j < b->numcols; j++){

			printf("%c ", b->boardArr[i][j]);

		}

		printf("|\n");
	}

	topBottom(b->numcols);

	printf("\t\t     ");

	for(int i = 1; i <= b->numcols; i++){

		printf("%i ", i/10);

	}

	printf("\n\t\t     ");

	for(int i = 1; i <= b->numcols; i++){

		printf("%i ", i%10);

	}

	printf("\n");

}

/**
* Function:  bb_pop
* Description:  (attempts to) "pop" the balloon at (r,c) (if any)
*               and its associated "color cluster"
*
*               Cluster must be of AT LEASE SIZE 2 (a balloon that
*   		is its own cluster will not be popped).
*
* Returns:  number of balloons popped
*
* Side effect:  adds n*(n-1) to score if n balloons were popped.
*
*/
int bb_pop(BBoard b, int r, int c){

	if(b->count == 0){

		for(int i = 0; i < b->numrows; i++){

			for(int j = 0; j < b->numcols; j++){

				char tmp;

				tmp = b->boardArr[i][j];

				b->undoPop[i][j] = tmp;

			}

		}

		int tmp;

		tmp = b->score;

		b->oldScore = tmp;

	}

	int bottomRow = b->numrows - 1;
	int rightSide = b->numcols - 1;

	if(r >= 0 && r <= bottomRow && c >= 0 && c <= rightSide){

		int tst = bb_get_balloon(b,r,c);

		if(r != 0){

			if(bb_get_balloon(b,r - 1,c) == tst){

				if(bb_set_balloon(b, r, c, None)){

					b->count++;

					bb_pop(b,r - 1,c);

				}
				
			}

			else if (bb_get_balloon(b, r + 1, c) == None){

				bb_set_balloon(b, r, c, None);

				b->count++;

			}

		}

		if (c != 0){

			if(bb_get_balloon(b,r,c - 1) == tst){

				if(bb_set_balloon(b, r, c, None)){

					b->count++;

					bb_pop(b,r,c - 1);

				}
				
			}

			else if (bb_get_balloon(b, r, c + 1) == None){

				bb_set_balloon(b, r, c, None);

				b->count++;

			}

		}

		if (r != bottomRow){

			if(bb_get_balloon(b,r + 1,c) == tst){

				if(bb_set_balloon(b, r, c, None)){

					b->count++;

					bb_pop(b,r + 1,c);

				}
				
			}

			else if (bb_get_balloon(b, r - 1, c) == None){

				bb_set_balloon(b, r, c, None);

				b->count++;

			}

		}

		if (c != rightSide){

			if(bb_get_balloon(b,r,c + 1) == tst){

				if(bb_set_balloon(b, r, c, None)){

					b->count++;

					bb_pop(b,r,c + 1);

				}
				
			}

			else if (bb_get_balloon(b, r, c - 1) == None){

				bb_set_balloon(b, r, c, None);

				b->count++;

			}


		}



		for(int i = 0; i < b->numrows; i++){

			for(int j = 0; j < b->numcols; j++){

				if((b->boardArr[i][j] == b->boardArr[i][j + 1]) && (b->boardArr[i][j] != None && b->boardArr[i][j + 1] != None)){

					return 0;

				}

			}

		}

		for(int i = 0; i < b->numcols; i++){

			for(int j = 0; j < b->numrows; j++){

				if((b->boardArr[i][j] == b->boardArr[i][j + 1]) && (b->boardArr[i][j] != None && b->boardArr[i][j + 1] != None)){

					return 0;

				}

			}

		}
		

	} else {

		printf("OUT OF BOUNDS!\n");

	}

}

/**
* Function:  bb_is_compact
* Description:  determines if all balloons are as "high" as possible.
*               Returns 1 if this is the case
*               Returns 0 otherwise.
*
*               Note:  a balloon is as high as possible if and only
*     		if all slots in its column ABOVE it are also balloons
*		(non-empty)
*
*/
int bb_is_compact(BBoard b){

	for(int i = 0; i < (int)b->numcols; i++){

		for(int j = 0; j < (int)b->numrows - 1; j++){

			if((b->boardArr[i][j] == None) && (b->boardArr[i][j + 1] != None && b->boardArr[i][j + 1] != b->numrows - 1)){

				return 0;

			}

		}

	}

	return 1;
	
}

/**
* Function:  bb_float_one_step
* Description:  moves all balloons that that are NOT AS HIGH AS POSSIBLE
*               up one spot.  
*
*   Example:
*
*		before
*
*           +-----------------------+
*		  0 | + + + = + ^     + = = |
*		  1 | ^       + o + +   ^ = |
*		  2 | ^ +   o +   + =     = |
*		  3 |       o     + + =   = |
*		    +-----------------------+
* 		      0 0 0 0 0 0 0 0 0 0 1
*		      0 1 2 3 4 5 6 7 8 9 0
*
*		after
*
*           +-----------------------+
*		  0 | + + + = + ^ + + + = = |
*		  1 | ^ +   o + o + =   ^ = |
*		  2 | ^     o +   + + =   = |
*		  3 |                     = |
*		    +-----------------------+
* 		      0 0 0 0 0 0 0 0 0 0 1
*		      0 1 2 3 4 5 6 7 8 9 0
*
*
* Note:  think animation by repeating this until it
*   is compact (perhaps displaying each intermediate
*   configuration).
*/ 
int bb_float_one_step(BBoard b){

	for(int i = 0; i < b->numcols; i++){

		for(int j = 0; j < b->numrows; j++){

			if(b->boardArr[j][i] == None && b->boardArr[j+1][i] != None){

				char tmp1;
				char tmp2;

				tmp1 = b->boardArr[j+1][i];
				tmp2 = b->boardArr[j][i];

				b->boardArr[j][i] = tmp1;
				b->boardArr[j+1][i] = tmp2;

				bb_display(b);

				return 0;

			}

		}

	}

}

/**
* Function:  bb_score
* Description:  returns the current score 
*
*/ 
int bb_score(BBoard b){

	if(b->count > 0){

		int old = b->count;

		b->count -= (b->count / 2) + 1;
		old -= b->count;
		b->count = old;
		b->score += b->count * (b->count -1);
		b->count = 0;

	}

	return b->score;

}

/**
* Function:  bb_set_balloon
* Description:  sets position (r,c) in the board to 
*               given color.
*               If r or c is out of range, no change
*                 to the grid occurs.
*
*		returns 1 on success
*		returns 0 on failure ((r,c) out of range
*		  or invalid balloon color.
*
* Notes:  allows board to be initalized externally.
*
*/
int bb_set_balloon(BBoard b, int r, int c, char color){

	if((color == Red) || (color == Yellow) || (color == Green) || (color == Blue) || (color == None)){

		b->boardArr[r][c] = color;

		return 1;

	}

	return 0;

}

/**
* Function:   bb_get_balloon
* Description:  returns color of balloon at given location as a char.
*		if (r,c) is out of range, -1 is returned.
*
*/ 
int bb_get_balloon(BBoard b, int r, int c){

	if ((r > b->numrows - 1) || (r < 0) || (c > b->numcols - 1) || (c < 0)){

		return -1;

	}

	return b->boardArr[r][c];
}

/**
* Function:  bb_undo
* Description:  "undoes" most recent pop (if any).
*               includes all intermediate "float" operations.
*		
*		Restores score to corresponding previous value.
*
*/ 
int bb_undo(BBoard b){

	for(int i = 0; i < b->numrows; i++){

		for(int j = 0; j < b->numcols; j++){

			char tmp;
			
			tmp = b->undoPop[i][j];

			b->boardArr[i][j] = tmp;

		}

	}

	int tmp;

	tmp = b->score;

	b->score = tmp;

	return 1;

}

/*
	ALWAYS RETURN TO THE ORIGIN
*/