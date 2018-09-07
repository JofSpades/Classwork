/*************************************************
 |  Author: Maxwell Petersen                     |
 |  Lab: Thursday 9 AM                           |
 |  Program: #2, Like What                       |
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
    char* filename[100];
    int fileCount;
    leafNode* down;

};

struct treeNode{

    treeNode* alphaArray[36];
    leafNode* endArray[36];

};

//titles say it all for the next two functions
void initilizeTreeNode(treeNode* newNode){

    for(int i = 0; i < 36; i++){

        newNode->alphaArray[i] = NULL;
        newNode->endArray[i] = NULL;

    }

}
void initilizeLeafNode(leafNode* newNode){

    newNode->up = NULL;
    newNode->down = NULL;
    for(int i = 0; i < 100; i++){
        newNode->filename[i] = NULL;
    }
}
//function preforme the steppting through the tree as needed
void branchGrow(treeNode* &worm, int alphaIndex){
    //if new element make new char array
    if(worm->alphaArray[alphaIndex] == NULL){

        treeNode* newBranch = new treeNode;
        initilizeTreeNode(newBranch);
        worm->alphaArray[alphaIndex] = newBranch;
        worm = worm->alphaArray[alphaIndex];
    //else just step into the next spot
    } else {

        worm = worm->alphaArray[alphaIndex];

    }
}

//add a new leaf or modify an existing one
void growLeaf(treeNode* &worm, leafNode* &deadLeaf, int countFile, int alphaIndex, char* fName){

    //adding in new leaf node if char string hasn't been found yet
    if(worm->endArray[alphaIndex] == NULL){

        leafNode* newLeaf = new leafNode;
        initilizeLeafNode(newLeaf);
        newLeaf->up = deadLeaf;
        deadLeaf->down = newLeaf;
        newLeaf->filename[countFile] = fName;
        worm->endArray[alphaIndex] = newLeaf;
        newLeaf->fileCount = 1;
        deadLeaf = deadLeaf->down;
        //printf("new %s at: %lx\n", deadLeaf->filename[countFile], worm);

    //append the found array with a new file name
    } else {

        worm->endArray[alphaIndex]->filename[countFile] = fName;
        worm->endArray[alphaIndex]->fileCount++;
        //printf("old %s at: %lx\n", worm->endArray[alphaIndex]->filename[countFile],worm);

    }

}

//this function preforms all of the sorting of the information
//and displaying of the 5 most alike files
int yardWork(leafNode* &leaf, int inCount, char* inFile[1500], int compAmount){

    int count = 0;
    int cntMatrix[inCount][inCount];
    int topComp[compAmount][3];

    //initlizing the top related array
    for(int i = 0; i < compAmount; i++){

        topComp[i][0] = 0;

    }

    leafNode* boot = leaf;

    //cleaning out all of the nodes that are non useful for
    //the comparison
    while(boot != NULL){

        if(boot->fileCount < 2){

            leafNode* temp = boot;

            boot = temp->up;

            if(temp->up != NULL){

                temp->up->down = temp->down;

            }
            if(temp->down != NULL){

                temp->down->up = temp->up;

            }

            free(temp);

        } else {

            boot = boot->up;
        }

    }

    for(int i = 0; i < inCount; i++){

        for(int j = 0; j < inCount; j++){

            cntMatrix[i][j] = 0;
            boot = leaf;

            if(i != j){

                while(boot != NULL){

                    count++;

                    if((boot->filename[i] != NULL) && (boot->filename[j] != NULL)){

                        cntMatrix[i][j]++;
                        boot->filename[i] = NULL;
                        boot->filename[j] = NULL;

                    }

                    boot = boot->up;

                }//end while(boot != NULL)

                //cout << cntMatrix[i][j] << "\n";
                for(int k = 0; k < compAmount; k++){

                    if((cntMatrix[i][j] > topComp[k][0]) && k == 0){

                        topComp[k][0] = cntMatrix[i][j];
                        topComp[k][1] = i;
                        topComp[k][2] = j;
                        break;

                    } else if((cntMatrix[i][j] > topComp[k][0]) && k > 0){

                        topComp[k][0] = cntMatrix[i][j];
                        topComp[k][1] = i;
                        topComp[k][2] = j;
                        break;

                    }

                }

            }//end if(i != j)

        }

    }//end for(int i = 0; i < inCount; i++)

    int compCount = compAmount;

    for(int i = 0; i < compAmount; i++){

        if(topComp[i][0] != 0){

            printf("%d. %s has %d relations with, %s\n", i+1, inFile[topComp[i][1]], topComp[i][0], inFile[topComp[i][2]]);

            compCount--;

        }
        
    }

    if(compCount != 0){
        printf("NOT ENGOUGH DATA FOUND TO MAKE %d CORRALATIONS...\n", compCount);
    }

    cout << "Number of comparisons: " << count << "\n";

}

/*
This function is the main attraction for the whole program.
While reading in the files from the selected directory given
by the user prompt, it builds a trie and forms new locations in
the tree as the data is needed.
*/
void readDirectory(DIR *inDirectory, dirent *aFile, char* rFile, int charsize, int compAmount){
    //the use of the clock is to display total time based on
    //cycles
    clock_t start = clock();

    //initlizing the dummy node and the absolute root of the
    //tree
    treeNode* root = new treeNode;
    leafNode* deadLeaf = new leafNode;

    initilizeTreeNode(root);
    initilizeLeafNode(deadLeaf);

    FILE* inputFile;

    int countFile = 0;
    char* listOfFiles[1500];
    int in = 0;
    int count = 0;
    int alphaIndex;
    char inFileName[128];
printf("found\n");
fflush(stdout);
    if (inDirectory != NULL){
        aFile = readdir(inDirectory);
        if(aFile != NULL){

            printf("%s\n", aFile->d_name);
            fflush(stdout);
        }
        else {
            cout << "***NULL***\n" << endl;
        }
        
        while (aFile != NULL && aFile->d_name[0] != '.'){
        //while ((aFile = readdir(inDirectory)) != NULL){ 

            if(aFile->d_name[0] != '.'){
                //setup directory and file for reading
                sprintf(inFileName, "%s/%s",rFile,aFile->d_name);
                listOfFiles[countFile] = aFile->d_name;
                //printf("%s\n", aFile->d_name);

                inputFile = fopen(inFileName, "r");
                assert(inputFile);

                in = 0;
                fpos_t pos;

                do {

                    treeNode* worm = root;

                    //printf("root addr: %lx\n", root);

                    count = 0;

                    while(count < charsize){

                        in = fgetc(inputFile);

                        if(in == EOF){
                            break;
                        }

                        //used to grab the position at the position that it can move back to to
                        //step through the file
                        if(count == 1){

                            fgetpos(inputFile,&pos);

                        }
                        
                        //checking for what the input is
                        if(in >= 'A' && in <= 'Z'){

                            //storing the char and setting the new location array
                            
                            alphaIndex = (in - 'A');
                            branchGrow(worm, alphaIndex);
                            //if last element of char string add another leaf/apend a current one
                            if(count == compAmount - 1){

                                growLeaf(worm, deadLeaf, countFile, alphaIndex, aFile->d_name);

                            }
                            count++;

                        } else if(in >= 'a' && in <= 'z'){

                            
                            alphaIndex = in - 'a';
                            branchGrow(worm, alphaIndex);
                            if(count == compAmount - 1){

                                growLeaf(worm, deadLeaf, countFile, alphaIndex, aFile->d_name);

                            }
                            count++;

                        } else if (in >= '0' && in <= '9'){

                            
                            alphaIndex = in - 22;
                            branchGrow(worm, alphaIndex);
                            if(count == compAmount - 1){

                                growLeaf(worm, deadLeaf, countFile, alphaIndex, aFile->d_name);

                            }
                            count++;

                        }

                        //printf("worm addr: %lx\n", worm);
                        
                    }//end while(count < compAmount)

                    //allows for the continual reading of needed chars then shifting back needed - 1 chars
                    fsetpos(inputFile,&pos);

                    //delete(worm);

                } while(in != EOF);//end of the file 
                printf("%s\n", inFileName);
                fclose(inputFile);
                countFile++;
                //printOut(root);
                cout<<"\n";

            }//end if(aFile->d_name[0] != '.')

        }

        closedir(inDirectory);

    }

    printf("FOUND %d FILES IN '%s'\n", countFile, rFile);
    printf("LOAD FINISHED PROCESSING NOW PLEASE WAIT...\n");
    yardWork(deadLeaf, countFile, listOfFiles, compAmount);

    //printOut(root, 0);

    clock_t end = clock();
    double totalTime = double(end - start) / CLOCKS_PER_SEC;

    printf("DONE\nTIME TAKEN:%.2f\n",totalTime);

}

int main(){

    printf("********************************************************\n| Author: Maxwell Petersen\t\t\t       |\n| Lab: Thursday 9 AM\t\t\t\t       |\n| Program: #2, Likeness of files in directory\t       |\n| System: SublimeText/g++ 2.5 GHz Intel i5 Lenovo-G510 |\n********************************************************\n");

    DIR           *theDirectory;
    struct dirent *aFile;

    int charsize = 0;
    int compAmount = 0;
    char incommand[16];
    char dirName[64];
    cout << "Enter filename char string length and number of comparisons:\n./";
    scanf("%s %d %d", incommand, &charsize, &compAmount);

    theDirectory = opendir(incommand);  // customize this to change relative directory
    printf("LOADING PLEASE WAIT...\n");
    readDirectory(theDirectory, aFile, incommand, charsize, compAmount);
    return(0);
}
