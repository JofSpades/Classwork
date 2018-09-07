#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
using namespace std;

const char inFileName[] = "test.txt";  // input file name, at top for convenience
 
int main()
{
    FILE *inFile;           // Input file
    // The following correspond to fields found in the datafile
    int seed;         // The word
    int size;               // The year word was used
    int chain;          // How many times word was used
    int linear;   // How many unique texts that word was used in
    int quad;

    int smallest[5] = {100000,100000,100000,100000,100000};
    int seedSize[5] = {0,0,0,0,0};
    int sizeamount[5] = {0,0,0,0,0};
    
    inFile = fopen( inFileName, "r");   // Open for reading, hence the "r"
    assert( inFile);                    // make sure file open was OK
     
//  fscanf( inFile, " %s", word);  printf("%s\n", word);  
//  fscanf( inFile, "\t%d", &year);  printf("%d\n", year);  
     
    while( fscanf( inFile, "%d %d %d %d %d", &seed, &size, &chain, &linear, &quad) != EOF) {
          for(int i = 0; i < 5; i++){
          	if(chain < smallest[i] && i == 0){
          		smallest[i] = chain;
          		seedSize[i] = seed;
				sizeamount[i] = size;
				continue;
          	}
          	if(linear < smallest[i] && i == 0){
          		smallest[i] = linear;
          		seedSize[i] = seed;
				sizeamount[i] = size;
				continue;
          	}
          	if(quad < smallest[i] && i == 0){
          		smallest[i] = quad;
          		seedSize[i] = seed;
				sizeamount[i] = size; 
				continue;         		
          	}
          	if(chain < smallest[i] && i < 0){
          		smallest[i] = chain;
          		seedSize[i] = seed;
				sizeamount[i] = size;
				continue;
          	}
          	if(linear < smallest[i] && i < 0){
          		smallest[i] = linear;
          		seedSize[i] = seed;
				sizeamount[i] = size;
				continue;
          	}
          	if(quad < smallest[i] && i < 0){
          		smallest[i] = quad;
          		seedSize[i] = seed;
				sizeamount[i] = size; 
				continue;         		
          	}
          }
    }
    for(int i = 0; i < 5; i++){
    	cout << " : " << smallest[i] << " : " << seedSize[i] << " : " << sizeamount[i] << endl;
    }
    fclose( inFile);
 
    return 0;   // Keep C++ happy
}