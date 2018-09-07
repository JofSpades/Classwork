/*
Lab 9: Graph Representation
03/12/2015
 
Task 1: Able to read from the file.
Task 2.1: Finish the code to read from the file and put it in an adjacency matrix.
Task 2.2: Given two city IDs, CityID_1 and CityID_2, find the weight between these two cites using adjacency matrix created in Task 2.1.
Task 3: Finish the code to read from the file and put it in an adjacency list.
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Node {
    string cityName; // the name of each City
    int index; // if there was an int at each vertex
    int weight; // the weight of the current edge
    Node *pNext; // pointer to next vertex also reachable
};


//Task2.1 finish the code to read from the file and put it in an adjacency Matrix.
void ReadDataFileToAdjacencyMatrix(string filename, int ** &adjacencyMatrix, int &N)
{

    ifstream myfile(filename.c_str());
    /* the following code can help you allocate the matrix dynamically when N equals the number of cities.*/
     
    adjacencyMatrix= new int *[N];
    for (int i=0; i< N ;i++) {
        adjacencyMatrix [i] = new int[N];
    }

    int M;
    string * cityName;
    if(myfile.is_open()) {
        //read the number of cites
        myfile>>M;
        int value;
        for(int i=0;i<M;i++) {
            for(int j=0;j < M; j++) {
                myfile>>value;
                adjacencyMatrix[i][j] = value;
            }
        }
    } else {
        cout << "open file error!"<<endl;
    }
    
    // Your code here...
}

//Task2.2 Given two city IDs, CityID_1 and CityID_2, find the weight between these two cites using adjacency matrix created in Task 2.1.
int FindWeight(int **adjacentMatrix, int CityID_1, int CityID_2)
{
    int weight = 0;
    if(adjacentMatrix[CityID_1][CityID_2] != 0){

        weight++;

    }
    if(adjacentMatrix[CityID_2][CityID_1] != 0){

        weight++;
        
    }
    return weight;
}


//Task3 finish the code to read from the file and put it in an adjacency list.
void ReadDataFileToAdjacencyList(string filename, Node ** &successor, int &N)
{
    // Your code here...
    
}

void OutputAdjacentMatrix(int **adjacentMatrix, int N)
{
    cout << "The Adjacent Matrix of the graph is: " << endl;
    for(int i = 0;i < N; i++) {
        for(int j = 0;j < N; j++) {
            cout << adjacentMatrix[i][j] << " ";
        }
        cout<<endl;
    }
}

void OutputAdjacencyList(Node **successor, int N)
{
    cout <<"Adjacency List for the current graph" <<endl;
    for(int i=0;i<N;i++)
    {
        cout<<"Connected nodes's name and weight for the current node " << successor[i]->cityName<<endl;
        Node* current=successor[i]->pNext;
        
        while(current!=NULL) {
            cout << current->cityName <<" " <<current->weight <<" ; ";
            current=current ->pNext;
        }
        cout<<endl;
        
    }
}

//this function reads and displays the data file.
int ReadDataFromFile(string filename)
{
    ifstream myfile(filename.c_str());
    
    int N;
    string * cityName;
    if(myfile.is_open()) {
        //read the number of cites
        myfile>>N;
        cout<<"Graph of "<<N<<" cities."<<endl;
        cout<<"CityID\t";
        //print out city id
        for(int i=1;i<=N;i++)
            cout<<i<<"\t";
        cout<<endl<<"\t\t";
        //print a line of ====
        for(int i=0;i<N*4;i++)
            cout<<"=";
        cout<<endl;
        //print the content of matrix
        int value;
        for(int i=0;i<N;i++) {
            cout<<(i+1)<<"\t||\t";
            for(int j=0;j < N; j++) {
                myfile>>value;
                cout<<value<<"\t";
            }
            cout<<endl;
        }
        return N;
    } else {
        cout << "open file error!"<<endl;
    }
}




int main(int argc, const char * argv[])
{
    //Task1 Change the following file name and path so you can read your data file.
    string filename="./data.txt";
    int ** adjacencyMatrix;
    int N=0;//Total number of cities
    Node **successor=NULL;
    
    N = ReadDataFromFile(filename);
    
    ReadDataFileToAdjacencyMatrix(filename, adjacencyMatrix, N);
    
    OutputAdjacentMatrix(adjacencyMatrix,N);

    int weight = 0;
    
    for(int i = 0; i < N; i++){

        for(int j = 0; j < N; j++){

            weight = FindWeight(adjacencyMatrix, i, j);

            cout << i << ":" << j << " Weight: " << weight << endl;

        }

    }
    
    //  ReadDataFileToAdjacencyList(filename, successor, N);
    
    // OutputAdjacencyList(successor, N);
    
    return 0;
}

