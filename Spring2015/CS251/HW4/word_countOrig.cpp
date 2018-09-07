#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <dirent.h>
using namespace std;

int hashStephen(char word[], int n) {
	int length = n & 0x1F;
	int i = 0, add = 0;
	while(word[i] != '\0') {
		add += (i+1) * word[i];
		i++;
	}
	add = add & 0x7FFF;

	return add ^ (length << 15);
}

int hashStephen2(char word[], int n) {
	int i = 0, add = 0;
	while(word[i] != '\0') {
		add += (i+1) * word[i];
		i++;
	}
	double d = ((double) add / 23180.0) * 256000.0;
	return (int) d;
}

int hashF2(char word[], int n) {
	int i = 0, add = 0;
	while(word[i] != '\0') {
		add += ((i+1));
		i++;
	}
	return add % 20;
}

int hashMax(char word[], int n) {
	int i = 0, add = 1;
	while(word[i] != '\0') {
		add *= (n - i) * word[i];
		i++;
	}
	return add % 20;
}

void readFile(char* dir, char* fileName) {
	char cleanPath[256];
	cleanPath[0] = '.';
	cleanPath[1] = '/';
	cleanPath[2] = '\0';
	strcat(cleanPath, dir);
	strcat(cleanPath, "/");
	strcat(cleanPath, fileName);
	FILE* file = fopen(cleanPath, "r");
	char* str = new char[256];
	int i = 0, smallCount = 0;
	char c;
	int wordCount = 0, maxLength = 0;
	int bins[64];
	int maxHash = 0;
	for(i = 0; i < 64; i++) {
		bins[i] = 0;
	}
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
			cout << "string: '" << str << "'\n";

			// stuff
			int h = hashStephen2(str, smallCount);
			if(h > maxHash) {
				maxHash = h;
			}
			cout << "hash: " << h << "\n";
			while(h > 64000) {
				h -= 64000;
			}
			if(h < 0) {
				h *= -1;
			}
			bins[h / 1000] += 1;
			// stuff


			smallCount = 0;
			wordCount++;
		}
	}
	fclose(file);

	cout << "bins: \n";
	for(i = 0; i < 64; i++) {
		cout << ":   " << ((float) bins[i] / wordCount) * 100 << '%' << "   :" << bins[i] << "\n";
	}

	cout << "Max hash: " << maxHash << "\n";
	cout << "Total words: " << wordCount << "\n";
	cout << "maxLength: " << maxLength << "\n";
	return;
}

int main() {
	readFile("/", "will.txt");

	return 0;
}