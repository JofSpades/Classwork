#include "inst_legible.h"
#include <iostream>
#include <cstdlib>
using namespace std;

const int maxNumber = 10000;
const int listSize = 100000;
const int numBins = 10;
int l[listSize];
int spacer[10000000]; // separates the addresses of b and l
int b[numBins];
int main()
{
	int i, j, binWidth;
// Generate a list of random integers between 0 and maxNumber-1
	for (i=0; i < listSize; i++) l[i] = rand() % maxNumber;
// Reset the bin counts to zero
		for (i=0; i < numBins; i++) b[i] = 0;
// Work out the width of each bin - must be an integer
if (maxNumber % numBins) return 1; // return error code
else binWidth = maxNumber / numBins;
// Run through the list and bin each item
for (i=0; i<listSize; i++) {
	INST_R(l[i]);
	j = l[i]/binWidth;
	INST_R(b[j]);
	b[j]++;
	INST_W(b[j]);
}
// Display the final contents of each bin
for (i=0; i < numBins; i++)
	cerr << "Bin " << i << " contains " << b[i] << " numbers" << endl;
return 0; // return success code
}
