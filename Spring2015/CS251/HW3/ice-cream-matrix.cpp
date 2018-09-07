#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

//for time keeping and comparison
struct timeval tvalBefore, tvalAfter;

/*
 * +---------------------------------------------+
 * | Authors: Stephen Selke & Maxwell Petersen   |
 * | Emails: (sselke2||mpeter39)@uic.edu         |
 * | Program 3: Ice Cream (dominance problem)    |
 * +---------------------------------------------+
 * | Tested on: 2.6GHz 8GB Macbook Pro           |
 * | Also on: 2.5GHz 16GB Lenovo G510 (Ubuntu)   |
 * +---------------------------------------------+
 */

/* 
 * EDIT VERSION 2.3
 * ----------------
 */

struct Matrix {
	int** matrix;
	int size;
	int found;
};

struct Node {
	int id;
	Node* next;
};

struct Vertex {
	int id;
	int degree;
	int rDegree;
	Vertex* next; // for linked list ordering
	Node* list;
};

struct LinkedList {
	Vertex* head;
	Vertex** vertices;
	int n;
	int edges;
	int MSP;
};

/*
 * creating a new matrix of set size
 * and setting all fields to zero
 */
int** newMatrix(int size) {
 	int fixedSize = size + 1;
	int** matrix = new int*[fixedSize]; // +1 because vertex count starts at 1 not 0
	int i, j;
	for(i = 0; i < fixedSize; i++) {
		matrix[i] = new int[fixedSize];
		for(j = 0; j < fixedSize; j++) {
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

/*
 * updates entries in the matrix
 */
void updateMatrix(int** matrix, int input[], int n) {
 	int i;
	for(i = 1; i < n; i++) { // starts at 1 to avoid first vertex input[0]
		matrix[input[0]][input[i]] = 1;
		matrix[input[i]][input[0]] = 1;
	}
	matrix[input[0]][0] = n;
	matrix[0][input[0]] = n;
}

/*
 * prints out matrix [rows][cols]
 */
void printMatrix(Matrix* matrix) {
 	int i, j;
 	for(i = 1; i < matrix->size + 1; i++) {
 		for(j = 1; j < matrix->size + 1; j++) {
 			if(matrix->matrix[i][j] == 0){
 				cout << "  ";
 			} else {
 				cout << matrix->matrix[i][j] << " ";
 			}
 		}
 		cout << "\n";
 	}
}

void printArray(int arr[], int n) {
 	int i;
 	for(i = 0; i < n; i++) {
 		cout << arr[i] << " ";
 	}
 	cout << "\n";
 }

/*
 * this fuction reads in the file and 
 * populates the matrix array within 
 * the Matrix struct.
 */
Matrix* populateMatrix(char* filename) {
 	Matrix* m = new Matrix;
 	FILE* file = fopen(filename, "r");
 	char buffer[256];
 	int numberBuffer[256];
 	int** matrix;
 	int i = 0, j = 0, number, atLine = 0, size = 0;
 	while((buffer[i] = fgetc(file)) && buffer[i] != EOF) {
		if(buffer[i] == ' ' || buffer[i] == '\n') { // must be the end of a number
			buffer[i+1] = '\0';
			number = atoi(buffer);
			numberBuffer[j] = number;
			j++;
			if(buffer[i] == '\n') { // end of set
				if(atLine == 0) { // the number of vertices given on this line
					size = numberBuffer[0];
					matrix = newMatrix(size);
				}
				else {
					updateMatrix(matrix, numberBuffer, j);
				}
				j = 0;
				atLine++;
			}
			i = 0;
		}
		else {
			i++;
		}
	}
	if(i > 0) { // there might still be one left!
		buffer[i+1] = '\0';
		number = atoi(buffer);
		numberBuffer[j] = number;
		j++;
		updateMatrix(matrix, numberBuffer, j);
	}
	fclose(file);
	m->matrix = matrix;
	m->size = size;
	return m;
}

/*
 * creating a new linked list struct of set size
 * and setting all fields to zero
 */
LinkedList* newList(int size) {
	LinkedList* list = new LinkedList;
	list->n = size;
	list->edges = 0;
	list->head = NULL;
	list->MSP = 0;
	list->vertices = new Vertex*[size+1]; // will be declared with updateList
	for(int i = 0; i < size+1; i++) {
		list->vertices[i] = NULL;
	}
	return list;
}

/*
 * add nodes onto linked list for Vertex connections
 * as well as sort the vertex linked list
 */
void updateList(LinkedList* list, int arr[], int n, int visitedArray[]) {
	Vertex* v = list->vertices[arr[0]];
	if(v == NULL) { // must be a new entry
		v = new Vertex;
		list->vertices[arr[0]] = v;
		v->id = arr[0];
		v->degree = 0;
		v->rDegree = 0;
		v->next = NULL;
		v->list = NULL;
	}

	// handle the connected list
	int i;
	Node* entry;
	for(i = 1; i < n; i++) {
		entry = new Node;
		entry->id = arr[i];
		entry->next = v->list; // pre-append
		v->list = entry;

		// handle relevant degree
		if(visitedArray[entry->id] != 1) {
			visitedArray[entry->id] = 1;
			v->rDegree += 1;
		}
	}
	v->degree += n-1;
}

void selectionSort(Vertex* arr[], int size) {
	int large = 1;
	for(int pass = 1; pass < size + 1; pass++) {
		large = pass;
		for(int i = pass + 1; i < size + 1; i++) {
			if(arr[i]->rDegree > arr[large]->rDegree) {
				large = i;
			}
		}
		Vertex* tmp = arr[pass];
		arr[pass] = arr[large];
		arr[large] = tmp;
	}
}

/*
 * sorts the vertices in the array
 * into a linked list of relevant degrees
 */
void sortList(LinkedList* list) {
	int i, size = list->n;
	Vertex** vertexArray = new Vertex*[size+1];
	int** visitedArray = new int*[size+1];
	for(i = 1; i < size+1; i++) { // copy array
		vertexArray[i] = list->vertices[i];
	}
	selectionSort(vertexArray, size);
	for(i = 1; i < size + 1; i++) {
		vertexArray[i]->next = vertexArray[i+1];
	}
	list->head = vertexArray[1];
}

/*
 * print out linked list structure
 * in both dimensions
 */
void printList(LinkedList* list) {
	int n = list->n;
	int i;
	if(list->head != NULL) {
		cout << "list head: " << list->head->id << "\n";
	}
	for(i = 1; i < n+1; i++) {
		cout << "| id: " << list->vertices[i]->id;
		if(list->vertices[i]->next == NULL) {
			cout << " --> X\n";
		}
		else {
			cout << " --> " << list->vertices[i]->next->id << "\n";
		}
		cout << "| degree: " << list->vertices[i]->degree << "\n";
		cout << "| rDegree: " << list->vertices[i]->rDegree << "\n";
		cout << "| connected to ";
		Node* explorer = list->vertices[i]->list;
		while(explorer != NULL) {
			cout << explorer->id << " -> ";
			explorer = explorer->next;
		}
		cout << "\n\n";
	}
}

/*
 * same as populateMatrix except it populates 
 * the linked list structure
 */
LinkedList* populateLinkedList(char* filename) {
	LinkedList* list;

	FILE* file = fopen(filename, "r");
	char buffer[256];
	int numberBuffer[256];
	int i = 0, j = 0, number, atLine = 0, size = 0;

	int* visitedArray;

	while((buffer[i] = fgetc(file)) && buffer[i] != EOF) {
		if(buffer[i] == ' ' || buffer[i] == '\n') { // must be the end of a number
			buffer[i+1] = '\0';
			number = atoi(buffer);
			numberBuffer[j] = number;
			j++;
			if(buffer[i] == '\n') { // end of set
				if(atLine == 0) { // the number of vertices given on this line
					size = numberBuffer[0];
					list = newList(size);
					visitedArray = new int[size+1];
					for(i = 0; i < size+1; i++) { // copy array
						visitedArray[i] = 0;
					}
				}
				else {
					updateList(list, numberBuffer, j, visitedArray);
				}
				j = 0;
				atLine++;
			}
			i = 0;
		}
		else {
			i++;
		}
	}
	if(i > 0) { // there might still be one left!
		buffer[i+1] = '\0';
		number = atoi(buffer);
		numberBuffer[j] = number;
		j++;
		updateList(list, numberBuffer, j, visitedArray);
	}
	fclose(file);
	sortList(list);
	list->edges /= 2; // removing the doubling effect

	return list;
}

bool isDominatingSet(LinkedList* list, int set[], int size, int visitedArray[], int* version) {
	*version += 1;
	int i, verticesLeft = list->n;
	Node* explorer = NULL;
	for(i = 0; i < size; i++) {
		if(verticesLeft == 0) {
			return true;
		}
		explorer = list->vertices[set[i]]->list;
		if(visitedArray[list->vertices[set[i]]->id] != *version) {
			visitedArray[list->vertices[set[i]]->id] = *version; // i've seen myself
			verticesLeft--;
		}
		while(explorer != NULL) {
			if(visitedArray[explorer->id] != *version) { // haven't seen it yet!
				visitedArray[explorer->id] = *version;
				verticesLeft--;
			}
			explorer = explorer->next;
		}
	}
	if(verticesLeft == 0) {
		return true;
	}
	return false;
}

void combinations2(LinkedList* list, int v[], int start, int n, int k, int maxk, int visitedArray[], int* iteration) {
	int i, j;

	/* k here counts through positions in the maxk-element v.
	 * if k > maxk, then the v is complete and we can use it.
	 */
	if(k > maxk) {
		if(isDominatingSet(list, v+1, maxk, visitedArray, iteration)) {
			list->MSP = n;
			printArray(v+1, maxk);
		}
		return;
	}

	for(i = start; i <= n; i++) {
		v[k] = i;
		combinations2(list, v, i+1, n, k+1, maxk, visitedArray, iteration);
	}
}

void findSets(LinkedList* list) {
	int i, j, size = list->n, setLength;
	unsigned long setSize = 1 << size; // 2^n up to 64 elements :(
	int* set = new int[size];

	int* visitedArray = new int[size+1];
	int iteration = 1;
	int smallestSize = -1; // -1 is a flag
	for(i = 0; i < size; i++) {
		visitedArray[i+1] = 0;
	}

	for(i = 0; i < setSize; i++) {
		setLength = 0;
		for(j = 0; j < size; j++) {
			if(i & (1 << j)) { // does it overlap?
				set[setLength] = list->vertices[j+1]->id;
				setLength++;
			}
		}
		if(isDominatingSet(list, set, setLength, visitedArray, &iteration)) {
			printArray(set, setLength);
		}
	}
}

void findSetsQuick(LinkedList* list) {
	Vertex* explorer = list->head; // starts with the highest degree vertex
	Node* explorer2;
	int i, size = list->n;
	int* visitedArray = new int[size+1];
	int* set = new int[size];
	int setSize = 0;
	int verticesLeft = list->n;
	for(i = 0; i < size+1; i++) {
		visitedArray[i+1] = 0;
	}

	while(explorer != NULL) {
		if(!visitedArray[explorer->id]) {
			visitedArray[explorer->id] = 1;
			verticesLeft--;
		}
		explorer2 = explorer->list;
		while(explorer2 != NULL) {
			if(!visitedArray[explorer2->id]) {
				visitedArray[explorer2->id] = 1;
				verticesLeft--;
			}
			explorer2 = explorer2->next;
		}
		set[setSize] = explorer->id;
		setSize++;
		explorer = explorer->next;
		if(verticesLeft == 0) {
			break;
		}
	}
	cout << "moment of truth:\n";
	printArray(set, setSize);
}

void listCooralate(LinkedList* list){
	int i;
	int* visitedArray = new int[list->n+1];
	int iteration = 1;
	int v[list->n+1];
	for(i = 0; i < list->n; i++) {
		visitedArray[i+1] = 0;
	}

	for(i = 1; i < list->n; i++) {
		combinations2(list, v, 1, list->n, 1, i, visitedArray, &iteration);
		if(list->MSP != 0) {
			break;
		}
	}
}

//used to initlize the arays to 0
void initlizeArray(int inArr[], int size){
	int i = 1;
	for(i; i <= size; i+= 4){
		inArr[i] = 0;
		inArr[i + 1] = 0;
		inArr[i + 2] = 0;
		inArr[i + 3] = 0;
	}

	if(i > size){
		for(i -= 4 ; i <= size; i++){
			inArr[i] = 0;
		}
	}	
}

//This section of code was taken then modified from combinations.cpp at
//https://wwsw.dropbox.com/sh/hst46kb07qqed4b/AADWCbE5L-w76oIjH3dVN_6qa/Graph/combinations.cpp?dl=0
void combinations (Matrix *&structMatrix, int** matrix, int v[], int checkNodes[], int start, int n, int k, int maxk) {
	int i, j;
    /* k here counts through positions in the maxk-element v.
     * if k > maxk, then the v is complete and we can use it.
     */
     if (k > maxk) {
     	int remember = 0;
 		//counter for how many are needed to be seen still
     	int countLeft = n;
     	initlizeArray(checkNodes, n);
        //run through the matrix looking for which nodes have been touched
     	for(i = 1; i <= maxk; i++){
     		//setting the varible to skip unneeded 0's
     		remember = matrix[v[i]][0];
     		for(j = 1; j <= n; j++){
    			// if the element at the v[i]th row and jth column == 1
    			// while it hasn't been visited yet
     			if((matrix[v[i]][j] == 1 || v[i] == j ) && (checkNodes[j] == 0)){
     				//then the node is covered
     				checkNodes[j] = 1;
     				countLeft--;
     				remember--;
     			}

     			if(remember == 0){
     				//all possible 1's have been found so end
     				break;
     			}
     		}
     	}
     	//looking to see if all nodes are covered
     	if(countLeft != 0){
     		return;
     	}

     	//printout the found set
     	for (i=1; i<=maxk; i++){
     		cout << v[i] << " ";
     	}
     	cout << endl;

     	//indicating that the smallest possible size for the set has been found
     	structMatrix->found = 1;
     	
     	return;
     }

    /* for this k'th element of the v, try all start..n
     * elements in that position
     */
     for (i=start; i<=n; i++) {

     	v[k] = i;
        /* recursively generate combinations of integers
         * from i+1..n
         */
         combinations (structMatrix, matrix, v, checkNodes, i+1, n, k+1, maxk);
     }
}//End of copied and modified code

int skippingMax(int** inMaxtrix, int size){
	//count variable
	int i = 1;
	//skipp size
	int skippSize = 0;
	int temp = 0;
	for(i; i <= size; i+= 4){
		temp += inMaxtrix[i][0];
		temp += inMaxtrix[i + 1][0];
		temp += inMaxtrix[i + 2][0];
		temp += inMaxtrix[i + 3][0];
		temp /= 4;
		skippSize += temp;
		temp = 0;
	}

	if(i > size){
		i -= 4;
		//getting the avrage of all the averages to this point
		skippSize /= i;
		//temp count to know how much to devide by
		int count = 0;
		for(i; i <= size; i++){
			count++;
			temp += inMaxtrix[i][0];
		}

		//getting the final avrages
		temp /= count;
		skippSize += temp;
		skippSize /= 2;

		if(skippSize > 5){
			return skippSize;
		}

		return 5;

	} else {
		//getting the avrage of all the averages to this point
		skippSize /= i;
	}

	if(skippSize > 5){
		return skippSize;
	}

	return 5;
}
	
//used to check for any remaining zeros in an array
int hasZeros(int inArr[], int size){
	//count variables
	int i = 1;
	//variable to store the value at the seperate array indexes(as an acumulator)
	int keepTrack = 0;

	for(i; i <= size; i+= 4){
		keepTrack += inArr[i];
		keepTrack += inArr[i + 1];
		keepTrack += inArr[i + 2];
		keepTrack += inArr[i + 3];
		if(keepTrack != 4){
			return 1;
		}

		keepTrack = 0;
	}

	if(i > size){
		for(i -= 4; i <= size; i++){
			if(inArr[i] == 0){
				return 1;
			}
		}
	}
	return 0;
}

void loadNoOverlap(int matrixSize, int skipVal, int** useMatrix, int onesArr[], int indexArray[],  int& onesLocation, int& index, int passIn){
	//normal counter
	int i;
	// overlap counter
	int overlap = 0;
	for(i = 1; i <= matrixSize; i++){
		if(useMatrix[index][i] & onesArr[i]){
 			//if overlap is found
			overlap++;
			if(overlap > skipVal){
 				//if too much overlap on this end
				index += passIn;
				return;
			}
		}
	}

	//if overlap is fine then store the index into the array
	indexArray[onesLocation] = index;
	onesLocation++;

	//if overlap is fine load in the 1's
	onesArr[index] = 1;

	for(i = 1; i <= matrixSize; i++){
		if(useMatrix[index][i] == 1){
			onesArr[i] = useMatrix[index][i];
		}
	}

	index += passIn;
}

//Matrix searching function
void matrixCooralate(Matrix* &matrix, clock_t start){

 	//used to load in the size variable
 	int matrixSize = matrix->size;

    //array used to check for completeness of nodes
 	int checkNodes[matrixSize];

 	//setting the fount value in the matrix struct to 0 as an initlization for use later
 	matrix->found = 0;

	//count variables
	//track is used to make sure to only printout no more than 1000 elements
 	int i, j, track;

 	//array to keep track of what is being use as combos
 	int combosList[matrixSize];

 	//to see if this set size is the smallest found
 	matrix->found = 0;

 	//if checks for more the use of more percise findings
 	if(matrixSize < 100){

 		//check time
 		double totalTime;
 		clock_t intermediate;

 		//Go through the generated matrix to find combonations that cover area.
		//Printing out as it finds combonations that cover all of the vertexes.
 		for(i = 1; i <= matrixSize; i++){
 			//start down the rabbit hole, recursive loop, for the ith size of the set
 			combinations(matrix, matrix->matrix, combosList, checkNodes, 1, matrixSize, 1, i);
 			if(matrix->found == 1){
 				return;
 			}
 			//used to gather time per stage mainly for debug 
 			// intermediate = clock();
 			// totalTime = double(intermediate - start) / CLOCKS_PER_SEC;
 			// printf("DONE WITH SET SIZE: %i TIME IS NOW:%.5fs\n", i, totalTime);
 		}

 	} else {

 		/*
		This method which is only used for large amount of verticies, in this case greater than 100, will run
		through the matrix row by row starting at the opposite ends, i.e. the first and last then the second and
		second to last ect. ect., ony copying in when there is less than a certain amount of over lap which is
		determined by the average coverage minus 2 for a greater value than 1, for incredably sparce/small graphs.
		The next step is to then store the indexes of the used rows into another arry which will be printed out
		once the array which stores the 1's is full.
 		*/

		//start timer
		clock_t check;
		double totalTime;

 		//store 1's and check for minimal overlap using this array
 		int onesArr[matrixSize];

 		//storing the array index;
 		int indexArray[matrixSize];
 		int indexArrayIndex = 0;

 		//pulling the matrix from memory
 		int** useMatrix = matrix->matrix;

 		//setting all values in the array to 0;
 		initlizeArray(onesArr, matrixSize);
 		initlizeArray(indexArray, matrixSize);

 		//using this to shrink the size of matrixSize to gauge the proper spots needed on the upper and lower bounds
 		int bottom = 1;
 		int top = matrixSize;

 		//max number over overlaps allowed before skipping
 		int skipVal = skippingMax(useMatrix, matrixSize);

 		printf("REMINDER THAT AT THIS SIZE ALL THIS FUNCTION DOES IS RETURN A DOMINATE SET\nI AM WELL AWARE THERE ARE SMALLER SETS THAN THE ONE THAT THIS WILL PRINTOUT\n");

 		//actual start checking for any 0's in the array
 		while(hasZeros(onesArr, matrixSize) != 0){

 			//run through the array looking for overlap then load if its fine

 			//bottom run
 			loadNoOverlap(matrixSize, skipVal, useMatrix, onesArr, indexArray, indexArrayIndex, bottom, 1);

 			//top run
 			loadNoOverlap(matrixSize, skipVal, useMatrix, onesArr, indexArray, indexArrayIndex, top, -1);

 			check = clock();
 			totalTime = double(check - start) / CLOCKS_PER_SEC;
 			if(top <= bottom){

 				printf("DONE WITH ITERATIONS TIME IS NOW:%.5fs\nNO SOLUTIONS WERE FOUND\n", totalTime);
 				break;

 			} // else {
 			// 	printf("DONE WITH ITERATION TIME IS NOW:%.5fs\nTOP IS: %i AND BOTTOM IS: %i\n",totalTime, top, bottom);
 			// }
 		}
 		//double check for actual final set
 		if(top > bottom){

 			//print out final set
 			while( indexArray[i] != 0){

 				cout << indexArray[i] << " ";

 				i++;
 			}
 			cout << endl;
 		}
 	}
}

int main(int argc, char* argv[]) {
	Matrix* adjacencyMatrix;
	LinkedList* list;

	cout << "+---------------------------------------------+\n";
	cout << "| Authors: Stephen Selke & Maxwell Petersen   |\n";
	cout << "| Emails: (sselke2||mpeter39)@uic.edu         |\n";
	cout << "| Program 3: Ice Cream (dominance problem)    |\n";
 	cout << "+---------------------------------------------+\n";
	cout << "| Tested on: 2.6GHz 8GB Macbook Pro           |\n";
	cout << "| Also on: 2.5GHz 16GB Lenovo G510 (Ubuntu)   |\n";
	cout << "+---------------------------------------------+\n";

	char filename[256];

	cout << "Please enter the filename: ";
	scanf("%s", filename);

	cout << "/\\/\\/\\/\\/\\ Adjacency Matrix done by Max: /\\/\\/\\/\\/\\\n";
	clock_t start = clock();

	adjacencyMatrix = populateMatrix(filename);
	matrixCooralate(adjacencyMatrix, start);

	clock_t end = clock();
 	double totalTime = double(end - start) / CLOCKS_PER_SEC;
 	printf("DONE WITH MATRIX\nTIME TAKEN:%.5fs\n\n",totalTime);


 	cout << "/\\/\\/\\ Adjacency Linked List done by Stephen: /\\/\\/\\\n";
 	start = clock();
	
	list = populateLinkedList(filename);
	listCooralate(list);
	
	end = clock();
 	totalTime = double(end - start) / CLOCKS_PER_SEC;
 	printf("DONE WITH LINKED LIST\nTIME TAKEN:%.5fs\n",totalTime);

}