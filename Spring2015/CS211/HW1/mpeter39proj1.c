#include <stdio.h>
#include <stdlib.h>

void arrayCopy(int inArr[], int outArr[], int size){
    	//making index for the following loop
    	int i;

    	for(i = 0; i < size; i++){

    	    	/*
    	    	as this loop iterates through all the values 0 to <size>
    	    	it makes the i'th values of outArr equal to the i'th value of
    	    	inArr
    	    	*/
    		outArr[i] = inArr[i];

    	}
}
void sort(int inArr[], int size){
    	int i;

    	//looping through the whole array
    	for(i = 1; i < size; i++){

        	//setting the check value as not to lose the current place of the loop
        	int j = i;

        	//checking that the current value is larger than the previous
        	while(inArr[j] < inArr[j - 1]){

            		//if not then move the current value until it's in its proper place
            		int temp = inArr[j - 1];
            		inArr[j - 1] = inArr[j];
            		inArr[j] = temp;

            		j--;

        	}

    	}

}

int iSearch(int inArr[], int size, int look, int* numComp){
    	int i;
    	//setting found to -1 to start makes it set to be returned if the value is not
    	//found
    	int found = -1;

    	//iterating through the array looking for the requested value
    	for(i = 0; i < size; i++){

        	//keeping track of the amount of comparisons that have been made
        	(*numComp)++;

        	if(inArr[i] == look){

            		//because it was found its now time to return the value
            		found = i;

            		//ending the loop now as to stop the counter
            		break;

        	}

    	}

    	return found;

}

int bSearch(int inArr[], int size, int look, int* numComp){

	//setting found to being -1 to start so if its not found its set to be returned
	int found = -1;
	//the next two values allow for the range of values to be measured so the loop
	//can end
	int top = size - 1;
	int bottom = 0;
	//setting i to be the middle value will allow a proper binary search
	int i = (top + bottom) / 2;
	int count = 0;

	while(bottom <= top){

		//keeping track of computations
		(*numComp)++;

	        //checking if the curent index of inArr is what we need
	        if(inArr[i] < look){

			bottom = i + 1;

	        } else if(inArr[i] == look){

			//found it
			found = i;
			break;

		} else {

			top = i - 1;

		}

		i = (top + bottom) / 2;

	}

	return found;

}

int main(int argc,int argv[]) {

	int val = 0;

	//setup of aray
	int *arr;
	int size = 100;
	int count = 0;
	arr = (int*)malloc(size * sizeof(int));

	printf("Enter digits for the comparisons by hitting the value then the return key.\nEnd the series with the value -999.\n no negitve numbers please.\n");

	scanf("%d", &val);

	while(val != -999){


		count++;

		//checking for need of reallocation
		if(count == size -1) {

			//reallocating
			int *temp;
			temp = (int*)malloc(size * 2 * sizeof(int));
			int i;

			for (i = 0; i < size; i++){
				temp[i]= arr[i];
			}

			free(arr);

			arr = temp;
			size *= 2;

		}

		//placing val in array
		arr[count] = val;

		//obtaining next value
		scanf("%d", &val);

	}

	int *arr2 = (int*)malloc(count * sizeof(int));
	int comp1 = 0;
	int comp2 = 0;

	//copying the data from arr to arr2
	arrayCopy (arr, arr2, size);

	//sorting arr2
	sort(arr2, size);

	//second scan for input
	scanf("%d", &val);

	printf("Column names:\nType\t\tSize\t\tNeeded Value\t\tFound at\t\tComputations\n");

	while( val != -999){

		int foundI = iSearch(arr, size, val, &comp1);
		int foundB = bSearch(arr2, size, val, &comp2);
		printf("Iteration :  \t%d\t\t%d\t\t        %d\t\t    %d\n", count, val, foundI, comp1);
		comp1 = 0;
		printf("Binary    :  \t%d\t\t%d\t\t        %d\t\t    %d\n", count, val, foundB, comp2);
		comp2 = 0;
		printf("--------------------------------------------------------------------------------------------\n");
		scanf("%d", &val);

	}

	return 0;
}
