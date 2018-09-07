/************************************************
|  Author: Maxwell Petersen                     |
|  Lab: Thursday 9 AM                           |
|  Program: #5, Trie again                      |
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

//structsures requred for the tree and the remberances of fielnames
struct leafNode{
    leafNode* up;
    char* word;
    int count;
    leafNode* down;
};

struct treeNode{
    treeNode* alphaArray[26];
    leafNode* endArray[26];
};

//titles say it all for the next two functions
void initilizeTreeNode(treeNode* newNode){
    for(int i = 0; i < 26; i++){
        newNode->alphaArray[i] = NULL;
        newNode->endArray[i] = NULL;
    }
}
void initilizeLeafNode(leafNode* newNode){
    newNode->up = NULL;
    newNode->count = 0;
    newNode->down = NULL;
}
//if the leaf location is NULL then the word isnt there
int leafSearch(treeNode* &currentNode, int alphaIndex, char* inWord, char* builtWord, int charCount){
    //adding in new leaf node if char string hasn't been found yet
    if(currentNode->endArray[alphaIndex] == NULL){
        return 0;
    //a word is found
    } else {
        if(strncmp(inWord, builtWord, charCount) == 0){
            return currentNode->endArray[alphaIndex]->count;
        } else {
            return 0;
        }
    }
}
//if the spot is NULL at any point the word isn't there
int branchSearch(treeNode* &currentNode, int alphaIndex){
    //if new element make new char array
    if(currentNode->alphaArray[alphaIndex] == NULL){
        return 0;
    //else just step into the next spot
    } else {
        currentNode = currentNode->alphaArray[alphaIndex];
        return 1;
    }
}
//function preforme the steppting through the tree as needed
void branchGrow(treeNode* &currentNode, int alphaIndex, int &count){
    //if new element make new char array
    if(currentNode->alphaArray[alphaIndex] == NULL){
        treeNode* newBranch = new treeNode;
        initilizeTreeNode(newBranch);
        currentNode->alphaArray[alphaIndex] = newBranch;
        currentNode = currentNode->alphaArray[alphaIndex];
        count++;
    //else just step into the next spot
    } else {
        currentNode = currentNode->alphaArray[alphaIndex];
    }
}
//add a new leaf or modify an existing one
void growLeaf(treeNode* &currentNode, leafNode* &currentLeaf, int alphaIndex, int &count, char word[32]){
    //adding in new leaf node if char string hasn't been found yet
    if(currentNode->endArray[alphaIndex] == NULL){
        leafNode* newLeaf = new leafNode;
        initilizeLeafNode(newLeaf);
        newLeaf->up = currentLeaf;
        newLeaf->word = word;
        newLeaf->count = 1;
        currentLeaf->down = newLeaf;
        currentNode->endArray[alphaIndex] = newLeaf;
        currentLeaf = currentLeaf->down;
    //append the found array with a new file name
    } else {
        return;
    }
}
/*
This function is the main attraction for the whole program.
While reading in the files from the selected directory given
by the user prompt, it builds a trie and forms new locations in
the tree as the data is needed.
*/
void readFile(FILE* inputFile){
    //initlizing the dummy node and the absolute root of the
    //tree
    treeNode* root = new treeNode;
    leafNode* currentLeaf = new leafNode;
    treeNode* currentNode = root;
    initilizeTreeNode(root);
    initilizeLeafNode(currentLeaf);
    int in = 0;
    int wordCount = 1;
    int charCount;
    int alphaIndex;
    char word[64];
    while(in != EOF){
        word[0] = '\0';
        charCount = 0;
        currentNode = root;
        do {
            in = fgetc(inputFile);
            if(in == EOF){
                break;
            }
            //checking for what the input is
            if(isspace(in) && charCount > 0){
                word[charCount + 1] = '\0';
                growLeaf(currentNode, currentLeaf,alphaIndex, wordCount, word);
            } else if(isspace(in)){
                break;
            } else if(in >= 'A' && in <= 'Z'){
                //storing the char and setting the new location array
                alphaIndex = (in - 'A');
                branchGrow(currentNode, alphaIndex, wordCount);
                word[charCount] = in - 0x20;
                charCount++;
            } else if(in >= 'a' && in <= 'z'){
                alphaIndex = (in - 'a');
                branchGrow(currentNode, alphaIndex, wordCount);
                word[charCount] = in;
                charCount++;   
            }      
        } while(!isspace(in));//end of word
    }
    fclose(inputFile);
    cout << "TOTAL AMOUNT OF WORDS FOUND: " << wordCount << endl;
    cout << "LOAD FINISHED\nEITHER ENTER 'x' OR WORD TO SEARCH FOR..." << endl;
    char inWord[64];
    char builtWord[64];
    int found = 1;
    // cin >> inWord;
    scanf("%s", inWord);
    while(strncmp(inWord, "x\0",2) != 0){
        charCount = 0;
        currentNode = root;
        while(inWord[charCount + 1] != '\0'){
            if(inWord[charCount] >= 'A' && inWord[charCount] <= 'Z'){
                //storing the char and setting the new location array
                alphaIndex = (inWord[charCount] - 'A');
                found = branchSearch(currentNode, alphaIndex);
                builtWord[charCount] = inWord[charCount];
            } else if(inWord[charCount] >= 'a' && inWord[charCount] <= 'z'){
                alphaIndex = inWord[charCount] - 'a';
                found = branchSearch(currentNode, alphaIndex);
                builtWord[charCount] = inWord[charCount];
            }
            if(found == 0){
                break;
            }
            charCount++;
        }
        if(inWord[charCount + 1] == '\0' && found != 0){
            if(inWord[charCount] >= 'A' && inWord[charCount] <= 'Z'){
                alphaIndex = (inWord[charCount] - 'A');
                builtWord[charCount] = inWord[charCount] + 0x20;
            } else if(in >= 'a' && in <= 'z'){
                alphaIndex = (inWord[charCount] - 'a');
                builtWord[charCount] = inWord[charCount];
            }
            builtWord[charCount + 1] = '\0';
            found = leafSearch(currentNode, alphaIndex, inWord, builtWord, charCount);
        }
        if(found == 0){
            cout << "'" << inWord << "'" << " NOT FOUND\nTRY AGAIN OR ENTER 'x' TO EXIT" << endl;
        } else {
            cout << "'" << inWord << "'" << " WAS FOUND\nTRY AGAIN OR ENTER 'x' TO EXIT" << endl;   
        }
        // cin >> inWord;
    scanf("%s", inWord);
        found = 1;
    }
}
int main(){
    //set up the input file and read it in
    cout << "+---------------------------------------------+" << endl;
    cout << "| Author:  Maxwell Petersen                   |" << endl;
    cout << "| Email: mpeter39@uic.edu                     |" << endl;
    cout << "| Program 5: Trie Again                       |" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << "| Tested on: 2.5GHz 16GB Lenovo G510 (Ubuntu) |" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << "LOADING PLEASE WAIT..." << endl;
    FILE* inputFile;
    inputFile = fopen("./will.txt", "r");
    assert(inputFile);
    readFile(inputFile);
    return(0);
}
