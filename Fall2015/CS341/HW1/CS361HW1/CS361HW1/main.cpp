#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
	vector<string> V;

	cout << "Part 1: V" << endl;
	cout << sizeof(V) << endl;
	cout << V.size() << endl;
	cout << V.capacity() << endl;

	vector<int> V2;

	cout << "Part2: V2" << endl;
	cout << sizeof(V2) << endl;
	cout << V2.size() << endl;
	cout << V2.capacity() << endl;

	V.push_back("Hello");
	V.push_back(" ");
	V.push_back("World");
	V.push_back("!");
	V.push_back("...");

	cout << "Part 3: V (String)" << endl;
	cout << sizeof(V) << endl;
	cout << V.size() << endl;
	cout << V.capacity() << endl;

	V2.push_back(1);
	V2.push_back(2);
	V2.push_back(3);
	V2.push_back(4);
	V2.push_back(5);

	cout << "Part 4: V2 (Int)" << endl;
	cout << sizeof(V2) << endl;
	cout << V2.size() << endl;
	cout << V2.capacity() << endl;

	return 0;

}