#include "inst_none.h"
#include <iostream>
#include <cstdlib>
using namespace std;

const int listSize = 10000;
int l[listSize];
void XSort(int list[], int n);
void QSort(int list[], int lo, int hi);
int Partition(int list[], int lo, int hi);
int main()
{
	int i, tmp, i1, i2;
	// Generate a list with no repeated numbers
	for (i=0; i<listSize; i++) l[i] = i;
		// Scramble the numbers thoroughly
		for (i=0; i<listSize; i++) {
			i1 = rand() % listSize;
			INST_W(i1);
			i2 = rand() % listSize;
			INST_W(i2);
			INST_R(l[i1]);
			tmp = l[i1];
			INST_R(l[i2]);
			l[i1] = l[i2];
			INST_W(l[i1]);
			l[i2] = tmp;
			INST_W(l[i2]);
		}
		// Sort the list by exchange sort or QuickSort - comment out the
		// one you don't want to use
		XSort(l, listSize);
		// QSort(l, 0, listSize-1);
	return 0; // return success code
}
void XSort(int list[], int n)
// Exchange sort
{
	int min, tmp, i, j, min_j;
	// Scan the list from the left to the right
	for (i=0; i<n-1; i++) {
		// Remember the item at position i
		INST_R(list[i]);
		min = list[i];
		min_j = i;
		// Check the list to the right of position i for any smaller items
		for (j=i+1; j<n; j++) {
			INST_R(list[j]);
			if (list[j] < min) {
				// Remember where this smaller item is
				min = list[j];
				INST_R(list[j]);
				min_j = j;
			}
		}
		// Swap the item at position i with the smallest item found to the right
		INST_R(list[j]);
		tmp = list[i];
		INST_R(list[min_j]);
		list[i] = list[min_j];
		INST_W(list[i]);
		list[min_j] = tmp;
		INST_R(list[min_j]);
	}
}

void QSort(int list[], int lo, int hi)
// QuickSort - this simple version assumes no repeated items in the list
{
	int k;
	if (lo < hi) {
	// Partition the list into two sub-lists
		k = Partition(list, lo, hi);
		// Now every item left of position k is smaller than the item at k,
		// while every item right of position k is larger than the item at k
		QSort(list, lo, k-1); // sort the sublist to the left of k
		QSort(list, k+1, hi); // sort the sublist to the right of k
	}
}
int Partition(int list[], int lo, int hi)
// Partition function for QuickSort
{
	int x, tmp;
	// Pick an arbitrary key, say half way through the list
	INST_W(list[(lo+hi)/2]);
	x = list[(lo+hi)/2];
	// Now swap items until every item to the left of the key is smaller than
	// the key, and every item to the right of the key is larger than the key
	while (lo < hi) {
		// Scan from the right until we find an item smaller than the key
		while ( (lo < hi) && (x < list[hi]) ){
			INST_R(hi);
			hi--;
			INST_W(hi);
		}
		// Scan from the left until we find an item larger than the key
		while ( (lo < hi) && (x > list[lo]) ){
			INST_R(lo);
			lo++;
			INST_W(lo);
		}
		// Swap the two items we've discovered on the wrong side of the key
		INST_R(list[hi]);
		tmp = list[hi];
		INST_R(list[lo]);
		list[hi] = list[lo];
		INST_W(list[hi]);
		list[lo] = tmp;
		INST_W(list[lo]);
	}
	return lo; // this is where the key is now
}

