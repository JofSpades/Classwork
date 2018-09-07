//
// C++ program to compute student exam averages.
//
// Maxwell Petersen
// U. of Illinois, Chicago
// CS341, FAll 2015
// Homework 2
//

#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Student{
public:

	Student(string, int, double, double, double);

	int getUIN(void){
		return uin;
	}

	string getNetID(void){
		return netid;
	}

	double getAverage(){
		return averageScore;
	}

	double getScore1(){
		return score1;
	}

	double getScore2(){
		return score2;
	}

	double getScore3(){
		return score3;
	}

	void averaging(double inScore1, double inScore2, double inScore3){
		double total = inScore1 + inScore2 + inScore3;
		averageScore = (total / 3);
	}

private:
	string netid;
	double score1, score2, score3, averageScore;
	int uin;
};

Student::Student(string inNetID, int inUIN, double inScore1, double inScore2, double inScore3){
	netid = inNetID;
	uin = inUIN;
	score1 = inScore1;
	score2 = inScore2;
	score3 = inScore3;
	averaging(inScore1, inScore2, inScore3);
}

void sortFunction(vector<Student>& inVec){
	sort(inVec.begin(), inVec.end(), [=](Student a, Student b){return (a.getAverage() > b.getAverage());
});
	cout << "By exam average:" << endl;
	for(Student& examSorrt: inVec){
		cout << "\t" << examSort.getNetID() << ": avg = " << examSort.getAverage() << " based on exams: " << examSort.getScore1() << ", " << examSort.getScore2() << ", " << examSort.getScore3() << endl;
	}

	sort(inVec.begin(), inVec.end(), [=](Student a, Student b){return (a.getNetID() < b.getNetID());});
	cout << "By NetID:" << endl;
	for(Student& examSort: inVec){
		cout << "\t" << examSort.getNetID() << ": avg = " << examSort.getAverage() << " based on exams: " << examSort.getScore1() << ", " << examSort.getScore2() << ", " << examSort.getScore3() << endl;
	}

	sort(inVec.begin(), inVec.end(), [=](Student a, Student b){return (a.getUIN() < b.getUIN());});
	cout << "By UIN:" << endl;
	for(Student& examSort: inVec){
		cout << "\t" << examSort.getUIN() << ": avg = " << examSort.getAverage() << " based on exams: " << examSort.getScore1() << ", " << examSort.getScore2() << ", " << examSort.getScore3() << endl;
	}
}

int main (int argv, char** argc){
	ifstream file("students.txt");
	istream_iterator<string>  start(file), end;
	vector<Student> students;
	vector<string> data(start, end);
	int count = 0;
	int UIN;
	string NetID;
	double scores[3];

	for(string& in : data){
		if(count == 0){
			NetID = in;
		} else if(count == 1){
			UIN = atoi(in.c_str());
		} else if(count == 2){
			scores[0] = atof(in.c_str());
		} else if(count == 3){
			scores[1] = atof(in.c_str());
		} else if(count == 4){
			scores[2] = atof(in.c_str());
			Student newStudent(NetID, UIN, scores[0], scores[1], scores[2]);
			students.push_back(newStudent);
			count = -1;
		}
		count++;
	}

	sortFunction(students);

	return 0;
}