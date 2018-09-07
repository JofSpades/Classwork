#include <stdio.h>
#include <stdlib.h>


//the function below this initilizes arrays to 0

void init1D(int in[], int n){

	for(int i = 0; i < n; i++){

		in[i] = 0;

	}

}

//Checks for all values to be proper

void checkForProper(int in[9][9], int n, int m){

	for(int i = 0; i < n; i++){

		for(int j = 0; j < m; j++){

			if(in[i][j] > 9 || in[i][j] < 1){

				printf("IMPROPER VALUE FOUND OF %i AT (%i,%i) EXPECTING VALUE 1 - 9\n", in[i][j], i+1, j+1);

				exit (-1);

			}

		}

	}

}

/*
	This function below takes a completed soku bord
	and checks for any defective cells and return either 0
	for none or the amount of defective cells
*/


int scheck(int board[9][9]){

	int viol = 0;

	int tmp[9];

	init1D(tmp, 9);

	checkForProper(board, 9, 9);

	//Row check

	for(int i = 0; i < 9; i++){

		for(int j = 0; j < 9; j++){

			tmp[board[i][j] - 1]++;

		}

		for(int j = 0; j < 9; j++){

			if(tmp[j] != 1){

				viol++;

				break;

			}

		}

		init1D(tmp, 9);

	}

	//Columns check

	for(int j = 0; j < 9; j++){

		for(int i = 0; i < 9; i++){

			tmp[board[i][j] - 1 ]++;
		}

		for(int k = 0; k < 9; k++){

			if(tmp[k] != 1){

				viol++;

				break;

			}

		}

		init1D(tmp, 9);
		
	}

	//Boxes check

	for(int i = 0; i < 9; i += 3){

		for(int j = 0; j < 9; j += 3){

			for(int k = 0; k < 3; k++){

				for(int l = 0; l < 3; l++){

					tmp[board[i + k][j + l] - 1]++;

				}

			}

			for(int j = 0; j < 9; j++){

				if(tmp[j] != 1){

					viol++;

					break;

				}

			}

			init1D(tmp, 9);

		}

	}

	return viol;

}