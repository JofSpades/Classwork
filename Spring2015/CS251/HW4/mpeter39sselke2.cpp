/************************************************
|  Author: Maxwell Petersen/ Stephen Selke      |
|  Lab: Thursday 9 AM/ Thursday 8 AM            |
|  Program: #4, Hashing                         |
************************************************/

#include <dirent.h>
#include <iostream>
#include <cassert>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
#define TABLE1 = 60001
#define TABLE2 = 61991
#define TABLE3 = 62989
#define TABLE4 = 63997
#define TABLE5 = 64001
int hashFunction(char inWord[], int length){
    length = length & 0x1f;
    int i;
    for(i = 0; i < length; i++){
        hash += (((length - i)*10) * (inWord[i] % 20));
    }
    return hash;
}
/*
This function is the main attraction for the whole program.
While reading in the files from the selected directory given
by the user prompt, it builds a trie and forms new locations in
the tree as the data is needed.
*/
void readFile(FILE* inputFile){
    //the use of the clock is to display total time based on cycles
    clock_t start = clock();
    int in = 0;
    int wordCount = 0;
    int charCount;
    int wordHash = 0;
    char word[64];
    while(in != EOF){
        word[0] = '\0';
        charCount = 0;
        do {
            in = fgetc(inputFile);
            if(in == EOF){
                break;
            }
            //checking for what the input is
            if(isspace(in)){
                word[charCount + 1] = '\0';
            } else if(in >= 'A' && in <= 'Z'){
                in += 0x20;
                word[charCount] = in;
                charCount++;
            } else if(in >= 'a' && in <= 'z'){
                word[charCount] = in;
                charCount++;   
            }      
        } while(!isspace(in));//end of word
        wordHash = hashFunction(word, charCount);

    }
    fclose(inputFile);
    clock_t end = clock();
    double totalTime = double(end - start) / CLOCKS_PER_SEC;
    printf("DONE\nTIME TAKEN:%.6f\n",totalTime);
}
int main(){
    //set up the input file and read it in
    FILE* inputFile;
    inputFile = fopen("./will.txt", "r");
    assert(inputFile);
    printf("LOADING PLEASE WAIT...\n");
    readFile(inputFile);
    return(0);
}
