/*************************************************
 |	Author: Maxwell Petersen					 |
 |	Lab: Thursday 9 AM							 |
 |	Program: #1, Google NGram word count		 |
 ************************************************/

 #include <iostream>
 #include <cassert>
 #include <climits>
 #include <cstring>
 #include <cstdlib>
 #include <cstdio>
 using namespace std;

 const char fileInputName[] = "all_words.csv";

//making linked list to store massive amounts of data entries
struct RowOfData{

	RowOfData* prevAddress;
	char storedWord[81];
	int storedYear[200];
	unsigned long int storedWordCount[200];
	RowOfData* nextAddress;

};

struct TotalsForData{

	RowOfData* first;
	unsigned long long int totalCount;
	RowOfData* last;

};

void appendRow( TotalsForData * pTop, char inWord[81], int inYear, int inWordCount){
    // Get a new RowOfData and initialize all fields
    RowOfData *pTemp = new RowOfData;
    pTemp->prevAddress = NULL;
    pTemp->nextAddress = NULL;
    //assigning word into the struct
    int i = 0;
    
    for(i = 0; i < 81; i++){

    	pTemp->storedWord[i] = inWord[i];
    	
    }

    for(i = 0; i < 200; i++){

    	pTemp->storedWordCount[i] = 0;
    	pTemp->storedYear[i] = 0;

    }

    if((inYear >= 1801) && (inYear <= 2000)){

    	pTemp->storedYear[0] = inYear;
    	pTemp->storedWordCount[0] = inWordCount;
    	pTemp->nextAddress = NULL;

    }
     
    // Reset pointers, depending on whether this is the first RowOfData
    if( pTop->first == NULL) {
        // This is the first RowOfData
        pTop->first = pTemp;
        pTop->last = pTemp;
        pTemp->prevAddress = NULL;
        pTemp->nextAddress = NULL;
    	pTop->totalCount++;

    } else {

    	//Fitting new element into list
        pTop->last->nextAddress = pTemp;
    	pTemp->prevAddress = pTop->last;
    	pTemp->nextAddress = NULL;

    	//updating the pTop element
    	pTop->last = pTemp;

  		pTop->totalCount++;

    }


}

void graphWrite(unsigned long int inArr[40], int maximum, int minimum){

	//setup of variables for this graph
	int i = 0;
	int j = 0;
	int verticalScale = 20;
        if(maximum - minimum < 20)
            verticalScale = maximum - minimum;
	int totalScale = maximum / verticalScale;

	//top of the graph
	printf("******************************************\n");

	for(i = 0; i < verticalScale; i++){

		printf("|");

		//based on the computed various scales the actual value used is computed
		//here then implamentd later on in the for loops
		int useableScale = totalScale * (verticalScale - i);
		int useableScale2 = totalScale * (verticalScale - i + 1);

		for(j = 0; j < 40; j++){

			if((inArr[j] <= useableScale2) && (inArr[j] > useableScale)){

				cout << "+";

			} else if(inArr[j] < minimum){
            
                cout << "+";
            
            } else {

				cout << " ";

			}

		}

		printf("| %d\n", useableScale);
	}

	printf("******************************************\n");
	printf("1801               1900               2000\n");


}

void graphWriteD(double inArr[40], double maximum, double minimum){

	//setup of variables for this graph
	double i = 0;
	int j = 0;
	double verticalScale = 20;
	if(maximum - minimum < verticalScale){
	
		verticalScale = maximum - minimum;
		cout << endl << verticalScale << endl;
	
	}
	double totalScale = maximum  / verticalScale;

	//top of the graph
	cout << "Graph of average word length of all words from 1801 - 2000\n";
	printf("******************************************\n");

	for(i = maximum; i >= minimum; i -= 0.05){

		printf("|");

		//based on the computed various scales the actual value used is computed
		//here then implamentd later on in the for loops
		double useableScale = i;
		double useableScale2 = i + 0.05;

		for(j = 0; j < 40; j++){

			if((inArr[j] <= useableScale2) && (inArr[j] > useableScale)){

				cout << "+";
            
            } else if(inArr[j] < minimum){
            
                cout << "+";
            
            } else {

				cout << " ";

			}

		}

		printf("| %f\n", useableScale);
	}

	printf("******************************************\n");
	printf("1801               1900               2000\n");


}

void graphIt(TotalsForData* pTop, char inGraph[81]){

	//setting title
	printf("\nGrapth of how oftern %s was used betwenn 1801 and 2000\n", inGraph);

	//running the algorithm to collect the data from the element and avrage every
    //five years then load into array for displaying
    unsigned long int avg[40];
    int i = 0;
    int maximum = 0;
    int minimum = 30000;
    
    //finding the address of the element
    RowOfData *pTemp = pTop->first;
    while (strncmp(pTemp->storedWord, inGraph, 81) != 0){
        
        pTemp = pTemp->nextAddress;
        
    }
    
    unsigned long int avgVal = 0;
    for(i = 0; i < 200; i+= 5){
        
        avgVal = pTemp->storedWordCount[i];
        avgVal += pTemp->storedWordCount[i + 1];
        avgVal += pTemp->storedWordCount[i + 2];
        avgVal += pTemp->storedWordCount[i + 3];
        avgVal += pTemp->storedWordCount[i + 4];
        avgVal /= 5;
        
        if(avgVal> maximum){

        	maximum = avgVal;
        }

        if(avgVal < minimum){

        	minimum = avgVal;
        }

        avg[i / 5] = avgVal;
        
    }
    
    graphWrite(avg, maximum, minimum);

}

void avgYear(TotalsForData* pTop, int reqYear){
	//setup for searching
	RowOfData* pTemp = pTop->first;
	int index = (200 - (2000 - reqYear));
	double total = 0;
	double totalCount = 0;
	

	//iterating through the linked list getting all of the needed data and compiling
	//it
	while (pTemp != NULL){

		if(pTemp->storedWordCount[index] != 0){

			total += (double)(strlen(pTemp->storedWord) * pTemp->storedWordCount[index]);
			totalCount += (double)pTemp->storedWordCount[index];

		}
		
		pTemp = pTemp->nextAddress;

	}

	double avgAcross = total / totalCount;

	printf("The avrage word length of the year: %d is %.2f\n\n", reqYear, avgAcross);

}

double avgYearR(TotalsForData* pTop, int index){
	//setup for searching
	RowOfData* pTemp = pTop->first;
	double total = 0;
	double totalCount = 0;
	

	//iterating through the linked list getting all of the needed data and compiling
	//it
	while (pTemp != NULL){

		if(pTemp->storedWordCount[index] != 0){

			total += (double)(strlen(pTemp->storedWord) * pTemp->storedWordCount[index]);
			totalCount += (double)pTemp->storedWordCount[index];

		}
		
		pTemp = pTemp->nextAddress;

	}

	double avgAcross = total / totalCount;

	return avgAcross;
}

void avgAll(TotalsForData* pTop){
	//this function repeaditly preformes the previous function in order to gain the avrage for all years
	int i = 0;
	double firstInArray[200];
	double secondInArray[40];
	double finalAvg = 0.0;
	for(i = 0; i < 200; i++){

			firstInArray[i] = avgYearR(pTop, i);

	}

	// going through the array of stored avrages by groups of 5 to shrink it down to 40 elements
	double concat = 0.0;
	double maximum = 0.0;
    double minimum = 30000.0;
	for(i = 0; i < 200; i+= 5){
        
        concat = firstInArray[i];
        concat += firstInArray[i + 1];
        concat += firstInArray[i + 2];
        concat += firstInArray[i + 3];
        concat += firstInArray[i + 4];
        concat /= 5;

        if(concat > maximum){

        	maximum = (double)concat;
        }

        if(concat < minimum){

        	minimum = (double)concat;
        }

        secondInArray[i / 5] = (double)concat;

        cout << secondInArray[i / 5];
        
    }

    graphWriteD(secondInArray, maximum, minimum);


}

RowOfData* trueStrnCmp(TotalsForData* pTop, char inWord[81]){

	RowOfData* pTemp = pTop->last;
	int i = 0;
    
	while(pTemp != NULL){

		if(strncmp(inWord, pTemp->storedWord, 81) == 0){

			return pTemp;

		} 

        pTemp = pTemp->prevAddress;
	}

	return NULL;

}

//The following function is for debugging and development purposes
void displayList( TotalsForData* pTop){
    RowOfData *pTemp = pTop->first;  // keep track of starting place

    int i = 0;
     
    while (pTemp != NULL){
        cout << pTemp->storedWord << "\n";
        for(i = 0; i < 200; i++){

        	cout << "\t" << pTemp->storedWordCount[i] << "\n";        
        }
        pTemp = pTemp->nextAddress;
    }
     
}

 int main(){

 	//starting the linked list
 	TotalsForData *pTop = new TotalsForData;
 	pTop -> first = NULL;
 	pTop -> last = NULL;
 	pTop -> totalCount = 0;

 	//set up the input file and read it in
 	FILE *inputFile; 
 	//set up input data types and names
 	char inWord[81];				//input word
 	int inYear = 0;					//input year
 	unsigned int inWordCount = 0;			//input word count
 	int inUniqueTextCount = 0;		//needed to prevent error
    int i = 0;

 	printf("Opening file %s\n", fileInputName);
 	printf("PROCESSING AND SORTING....PLEASE WAIT....\n");
    int countout= 0;
 	
 	//processing the input file
 	inputFile = fopen(fileInputName, "r");
 	assert(inputFile);

 	while(fscanf(inputFile, "%s %d %d %d", inWord, &inYear, &inWordCount, &inUniqueTextCount) != EOF){
        
        for(i = 0; i < strlen(inWord); i++){
            
            inWord[i] = tolower(inWord[i]);
            
        }

 		if(pTop->first == NULL && pTop->last == NULL){

 			appendRow(pTop, inWord, inYear, inWordCount);

 		} else {
            
            RowOfData* pTemp2 = trueStrnCmp(pTop, inWord);
            
 			if(pTemp2 == NULL){

 				appendRow(pTop, inWord, inYear, inWordCount);

 			} else {

 				//adding data to the element
 				if((inYear >= 1801) && (inYear <= 2000)){

 					pTemp2->storedYear[(200 - (2000 - inYear)) - 1] = inYear;
 					pTemp2->storedWordCount[(200 - (2000 - inYear)) - 1] += inWordCount;
                    
 				}
 				
 			}

 		}

 	}

 	printf("DONE\n");
    
 	printf("**************************************************\n| Author: Maxwell Petersen\t\t\t |\n| Lab: Thursday 9 AM\t\t\t\t |\n| Program: #1, Google NGram word count\t\t |\n| \t\t\t\t\t\t |\n| Total number of distinct words: %llu\t\t |\n**************************************************\n", pTop->totalCount);
 	
 	//reciving input
    printf("\nEnter requested word to graph: ");
    char inGraph[81];
    scanf("%s",inGraph);
    graphIt(pTop, inGraph);
    
    printf("\nEnter requested year from 1801 - 2000: ");
    int reqYear = 0;
    scanf("%d", &reqYear);
    avgYear(pTop, reqYear);

    printf("\nPROCESSING REQUEST...\n");
    avgAll(pTop);
    
    
 	printf("\nEnjoy your day!\n");
    
 	return 0;

 }