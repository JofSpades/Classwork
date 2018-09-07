#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAX 65500

#define SIZE_1 65066
#define SIZE_2 63997
#define SIZE_3 64001
#define SIZE_4 65066
#define SIZE_5 64285

struct Node {
	char word[64];
	Node* next;
};

struct LQTable {
	int n;
	char items[MAX][64];
	int collisions;
};

struct ChainTable {
	int n;
	Node* items[MAX];
	int collisions;
	int wordCount;
};

/*
 * This has was inspired by the article found at
 * http://www.cse.yorku.ca/~oz/hash.html
 */
int modifiedDanBernsteinHash(char str[]) {
	int hash = 1233; // 5381
	char c;
	while((c = *str++)) {
		hash = (hash * 33) + c;
	}
	return hash < 0 ? (hash - 1) * -1 : hash;
}

ChainTable* newChainTable(int n) {
	ChainTable* table = new ChainTable;
	table->n = n;
	table->wordCount = 0;
	for(int i = 0; i < n; i++) {
		table->items[i] = NULL;
	}
	table->collisions = 0;
	return table;
}

LQTable* newLQTable(int n) {
	LQTable* table = new LQTable;
	table->n = n;
	for(int i = 0; i < n; i++) {
		table->items[i][0] = '\0';
	}
	table->collisions = 0;
	return table;
}

bool sameWord(char str1[], char str2[]) {
	int i = 0;
	char c = str1[0];
	while(c != '\0') {
		c = str1[i];
		if(c != str2[i]) {
			return false;
		}
		i++;
	}
	if(str2[i] != '\0') {
		return false;
	}
	return true;
}

void linearCollisionHandle(char str[], LQTable* table, int smallCount){
	int h = modifiedDanBernsteinHash(str);
	int mod;
	if(h < 0) {
		h *= -1;
	}
	if(h > table->n){
		int multipl = h / table->n;
		multipl *= table->n;
		h -= multipl;
	}
	if(table->items[h][0] == '\0'){
		strcat(table->items[h], str);
	} else if(strncmp(table->items[h], str, smallCount) == 0){
		smallCount = 0;
	} else {
		int alreadyHere = 0;
		table->collisions++;
		if(h < table->n - 1){
			mod = h + 1;
		} else if(h == table->n - 1){
			mod = 0;
		}
		while(table->items[mod][0] != '\0'){
			if(strncmp(table->items[mod], str, smallCount) == 0){
				smallCount = 0;
				alreadyHere = 1;
				break;
			}
			table->collisions++;
			mod++;
			if(mod > table->n){
				mod = 0;
			}
		}
		if(alreadyHere == 1){
			smallCount = 0;
		} else {
			strcat(table->items[mod], str);
		}
	}
}

void quadraticCollisionHandle(char str[], LQTable* table, int smallCount){ 
	int h = modifiedDanBernsteinHash(str);
	int mod;
	if(h < 0) {
		h *= -1;
	}
	if(h > table->n){
		int multipl = h / table->n;
		multipl *= table->n;
		h -= multipl;
	}
	if(table->items[h][0] == '\0'){
		strcat(table->items[h], str);
	} else if(strncmp(table->items[h], str, smallCount) == 0){
		smallCount = 0;
	} else {
		int alreadyHere = 0;
		table->collisions++;
		if(h < table->n - 1){
			mod = h + 1;
		} else if(h == table->n - 1){
			mod = 0;
		}
		int count = 1;
		while(table->items[mod][0] != '\0'){
			if(strncmp(table->items[mod], str, smallCount) == 0){
				smallCount = 0;
				alreadyHere = 1;
				break;
			}
			table->collisions++;
			mod = ((count * count) + h);
			if(mod > table->n){
				mod -= table->n;
			}
			count++;
		}
		if(alreadyHere == 1){
			smallCount = 0;
		} else {
			strcat(table->items[mod], str);
		}
	}
}

void addToChainTable(char str[], ChainTable* table) {
	int hash = /*hashStephen(str);*/ modifiedDanBernsteinHash(str);
	if(hash > table->n) {
		int multipl = hash / table->n;
		multipl *= table->n;
		hash -= multipl;
	}

	if(table->items[hash] == NULL) {
		Node* n = new Node;
		strcpy(n->word, str);
		n->next = NULL;
		table->items[hash] = n;
		table->wordCount++;
	}
	else {
		Node* n = table->items[hash];
		Node* tmp;
		while(n != NULL && !sameWord(str, n->word)) {
			tmp = n;
			n = n->next;
			table->collisions++;
		}
		if(n == NULL) {
			n = new Node;
			strcpy(n->word, str);
			n->next = NULL;
			tmp->next = n;
			table->wordCount++;
		}
	}
}

void printResult(int size, ChainTable* c, LQTable* l, LQTable* q) {
	cout << "Table size : " << size << "\n";
	cout << "   Chain: " << c->collisions << "\n";
	cout << "   Linear: " << l->collisions << "\n";
	cout << "   Quadratic: " << q->collisions << "\n\n";
}

void readFile() {
	
	FILE* file = fopen("will.txt", "r");
	char* str = new char[256];
	int i = 0, smallCount = 0;
	char c;
	int wordCount = 0, maxLength = 0;

	ChainTable* chain1 = newChainTable(SIZE_1);
	ChainTable* chain2 = newChainTable(SIZE_2);
	ChainTable* chain3 = newChainTable(SIZE_3);
	ChainTable* chain4 = newChainTable(SIZE_4);
	ChainTable* chain5 = newChainTable(SIZE_5);

	LQTable* linear1 = newLQTable(SIZE_1);
	LQTable* linear2 = newLQTable(SIZE_2);
	LQTable* linear3 = newLQTable(SIZE_3);
	LQTable* linear4 = newLQTable(SIZE_4);
	LQTable* linear5 = newLQTable(SIZE_5);

	LQTable* quadratic1 = newLQTable(SIZE_1);
	LQTable* quadratic2 = newLQTable(SIZE_2);
	LQTable* quadratic3 = newLQTable(SIZE_3);
	LQTable* quadratic4 = newLQTable(SIZE_4);
	LQTable* quadratic5 = newLQTable(SIZE_5);

	while((c = fgetc(file)) != EOF) {
		if(c >= 'A' && c <= 'Z') {
			*(str + smallCount) = (c - 'A') + 'a';
			smallCount++;
		}
		else if(c >= 'a' && c <= 'z') {
			*(str + smallCount) = c;
			smallCount++;
		}
		if((c == ' ' || c == '\n' || c == '\t') && smallCount > 0) {
			*(str + smallCount) = '\0';


			// call functions
			addToChainTable(str, chain1);
			linearCollisionHandle(str, linear1, smallCount);
			quadraticCollisionHandle(str, quadratic1, smallCount);

			addToChainTable(str, chain2);
			linearCollisionHandle(str, linear2, smallCount);
			quadraticCollisionHandle(str, quadratic2, smallCount);

			addToChainTable(str, chain3);
			linearCollisionHandle(str, linear3, smallCount);
			quadraticCollisionHandle(str, quadratic3, smallCount);

			addToChainTable(str, chain4);
			linearCollisionHandle(str, linear4, smallCount);
			quadraticCollisionHandle(str, quadratic4, smallCount);

			addToChainTable(str, chain5);
			linearCollisionHandle(str, linear5, smallCount);
			quadraticCollisionHandle(str, quadratic5, smallCount);

			smallCount = 0;
			wordCount++;
		}
	}
	fclose(file);

	printResult(SIZE_1, chain1, linear1, quadratic1);
	printResult(SIZE_2, chain2, linear2, quadratic2);
	printResult(SIZE_3, chain3, linear3, quadratic3);
	printResult(SIZE_4, chain4, linear4, quadratic4);
	printResult(SIZE_5, chain5, linear5, quadratic5);
	return;
}

int main() {
	cout << "+---------------------------------------------+\n";
	cout << "| Authors: Stephen Selke & Maxwell Petersen   |\n";
	cout << "| Emails: (sselke2||mpeter39)@uic.edu         |\n";
	cout << "| Program 4: Hashing                          |\n";
	cout << "+---------------------------------------------+\n";
	cout << "| Tested on: 2.6GHz 8GB Macbook Pro           |\n";
	cout << "| Also on: 2.5GHz 16GB Lenovo G510 (Ubuntu)   |\n";
	cout << "+---------------------------------------------+\n";

	readFile();

	return 0;
}