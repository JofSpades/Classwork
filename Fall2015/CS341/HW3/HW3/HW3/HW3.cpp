//
// C++ program to analyze Chicago crime data
//
// Maxwell Petersen
// U. of Illinois, Chicago
// CS341, FAll 2015
// Homework 3
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

//needed classes
class IUCRCode{
	string codeID, primaryDes, secondaryDes;
	int crimeCount;
public:
	IUCRCode(){
		codeID = "";
		primaryDes = "";
		secondaryDes = "";
		crimeCount = 0;
	}
	IUCRCode(string inCodeID, string inPrimaryDes, string inSecondaryDes, int inCrimeCount){
		codeID = inCodeID;
		primaryDes = inPrimaryDes;
		secondaryDes = inSecondaryDes;
		crimeCount = inCrimeCount;
	}
	void addOne(){
		crimeCount++;
	}
	void setCrimeCount(int newCount){
		crimeCount = newCount;
	}
	int getCrimeCount(){
		return crimeCount;
	}
	string getCodeID(){
		return codeID;
	}
	string getPrimary(){
		return primaryDes;
	}
	string getSecondary(){
		return secondaryDes;
	}
};
class Community{
	int number;
	string name;
public:
	Community(){
		number = 0;
		name = "";
	}
	Community(int inNumber, string inName){
		number = inNumber;
		name = inName;
	}
	int getNumber(){
		return number;
	}
	string getName(){
		return name;
	}
};
class Crime{
	string code;
	int community, year;
public:
	Crime(){
		code = "";
		community = 0;
		year = 0;
	}
	Crime(string inCode, int inCommunity, int inYear){
		code = inCode;
		community = inCommunity;
		year = inYear;
	}
	string getCode(){
		return code;
	}
	int getCommunity(){
		return community;
	}
	int getYear(){
		return year;
	}
};
//Parsing functions
IUCRCode parseIUCRCode(string line){
	// Variables
	string codeID, primaryDes, secondaryDes;

	//Open the string
	istringstream instring(line);

	//parsing with error check
	try{
		std::getline(instring, codeID, ',');
	}
	catch(...) {
		codeID = "";
	}
	try{
		std::getline(instring, primaryDes, ',');
	}
	catch (...) {
		primaryDes = "";
	}try{
		std::getline(instring, secondaryDes, ',');
	}
	catch (...) {
		secondaryDes = "";
	}

	// object creation
	return IUCRCode(codeID, primaryDes, secondaryDes, 0);
}
Community parseCommunityData(string line){
	// Variables
	int number;
	string name, sNumber;

	//Open the string
	istringstream instring(line);

	//parsing with error check
	try{
		std::getline(instring, sNumber, ',');
		number = std::stoi(sNumber);
	}
	catch (...) {
		number = 0;
	}
	try{
		std::getline(instring, name, ',');
	}
	catch (...) {
		name = "";
	}

	// object creation
	return Community(number, name);
}
Crime parseCrimeData(string line){
	// Variables
	string date, code, sArrest, sDomestic, sBeat, sDistrect, sWard, sCommunity, sYear;
	int community, year;

	// String open
	istringstream instring(line);

	//Error checking/parsing
	std::getline(instring, date, ',');
	try{
		std::getline(instring, code, ',');
	}
	catch (...) {
		code = "";
	}
	std::getline(instring, sArrest, ',');
	std::getline(instring, sDomestic, ',');
	std::getline(instring, sBeat, ','); 
	std::getline(instring, sDistrect, ',');
	std::getline(instring, sWard, ',');
	try {
		std::getline(instring, sCommunity, ',');
		community = stoi(sCommunity);
	}
	catch (...){
		community = 0;
	}
	try{
		std::getline(instring, sYear, ',');
		year = stoi(sYear);
	}
	catch (...){
		year = 0;
	}

	// Object creation
	return Crime(code, community, year);
}

//function to count up the amount of crimes per code
void crimeCounting(std::vector<Crime> &crimes, std::vector<IUCRCode> &codes){
	for (IUCRCode &codeIter : codes){
		for (Crime &crimeIter : crimes){
			if (crimeIter.getCode() == codeIter.getCodeID()){
				codeIter.addOne();
			}
		}
	}
}

//printing function for the top crimes in IUCR vector
void printTopIUCR(std::vector<IUCRCode> iucrCodes, int top){
	int i = 1;
	for (IUCRCode &iter : iucrCodes){
		std::cout << i << ".\t" << iter.getCodeID() << "\t" << iter.getCrimeCount() << "\t" << iter.getPrimary() << " (" << iter.getSecondary() << ")" << endl;
		i++;
		if (i > top){
			break;
		}
	}
}

// function to print out the data on individual communities from a presorted dataset
void printOutCommunityData(int communityNumber, int totalCrimes, std::vector<Crime> &crimes, std::vector<Community> &communities, std::vector<IUCRCode> &codes){
	// Variables
	int homicideCount = 0;
	float crimeCount = 0.0;
	float percentCrimeVsTotal;

	// counting the total and homicides
	for (Crime &crimeIter : crimes){
		if (crimeIter.getCommunity() == communityNumber){
			crimeCount++;
			if (crimeIter.getCode() >= "0110" && crimeIter.getCode() <= "0142"){
				homicideCount++;
			}
		} 
	}

	//recounting for the spcific community
	for (IUCRCode &codeIter : codes){
		codeIter.setCrimeCount(0);
		for (Crime &crimeIter : crimes){
			if ((crimeIter.getCode() == codeIter.getCodeID()) && (crimeIter.getCommunity() == communityNumber)){
				codeIter.addOne();
			}
		}
	}

	//corting IUCR codes by the new count
	std::sort(codes.begin(), codes.end(), [](IUCRCode a, IUCRCode b){
		return a.getCrimeCount() > b.getCrimeCount();
	});

	//generating the pertage vs total amount of crimes
	percentCrimeVsTotal = (crimeCount / float(totalCrimes)) * 100;

	//finding the name of the selected community
	std::vector<Community>::iterator selectedCommunity = std::find_if(communities.begin(), communities.end(), [=](Community a){
		return a.getNumber() == communityNumber;
	});

	// printout of community
	std::cout << ">> " << selectedCommunity->getName() << " <<" << endl;
	std::cout << ">> Total:\t" << crimeCount << endl;
	std::cout << ">> Percentage:\t" << percentCrimeVsTotal << "%" << endl;
	std::cout << ">> Homicides:\t" << homicideCount << endl;
	std::cout << ">> Top 5 Crimes <<\nRank\tIUCR\tNumber\tDescription" << endl;
	printTopIUCR(codes, 5);
	std::cout << endl;
}

//function to print out the data of a selected IUCR code
void printOutIUCRData(std::vector<IUCRCode>::iterator selectedCodeLocation, string selectedIUCRCode, std::vector<Crime> crimes, int totalCrimes){
	// variables
	int currentYear = 0;
	int crimeCountPerYear;
	int crimeCountPerYearArray[20][2];
	int i, j;
	double crimeCount = 0.0;
	double crimeCountPercentage;

	// Find the amount of years and what they are after sorting by year from most recent to oldest and getting the crime count for the specified IUCR
	std::sort(crimes.begin(), crimes.end(), [](Crime a, Crime b){
		return a.getYear() > b.getYear();
	});
	i = 0;
	for (Crime &iter : crimes){
		if (currentYear != iter.getYear()){
			currentYear = iter.getYear();
			crimeCountPerYearArray[i][0];
			i++;
		}
		if (iter.getCode() == selectedIUCRCode){
			crimeCount++;
		}
	}

	// counting the amount per year
	for (j = 0; j <= i; j++){
		crimeCountPerYear = 0;
		for (Crime &crimeIter : crimes){
			if (crimeCountPerYearArray[j][0] == crimeIter.getYear()){
				crimeCountPerYear++;
			}
			crimeCountPerYearArray[j][1] = crimeCountPerYear;
		}
	}
	crimeCountPercentage = (crimeCount / double(totalCrimes)) * 100.0;
	std::cout << ">> " << selectedCodeLocation->getPrimary() << " (" << selectedCodeLocation->getSecondary() << ")" << endl;
	std::cout << ">> Total:\t" << crimeCount << endl;
	std::cout << ">> Percentage:\t" << crimeCountPercentage << "%" << endl;
	std::cout << ">> By Year:" << endl;
	for (j = 0; j <= i; j++){
		cout << "\t" << crimeCountPerYearArray[j][0] << ": " << crimeCountPerYearArray[j][1] << endl;
	}
}

// main
int _tmain(int argc, _TCHAR* argv[]){
	// Misc Variables
	string line, dummyLine, selectedIUCRCode;
	string crimeFileName = "Crimes.csv";
	int i = 1;
	int communityNumber;

	// Crime Variables
	std::vector<Crime> crimes;
	int countOfCrimes = 0;

	// IUCR Variables
	std::vector<IUCRCode> iucrCodes;
	std::vector<IUCRCode>::iterator selectedCodeLocation;
	int countOfIUCR = 0;

	//Community Variables
	std::vector<Community> communityCodes;
	int countOfCommunities = 0;

	// open files
	ifstream iucrFile("IUCR-codes.csv");
	ifstream crimeFile(crimeFileName);
	ifstream communityFile("Communities.csv");

	//Reading of Data
	std::cout << ">> Reading crime data '" << crimeFileName << "'... ";
	std::getline(crimeFile, dummyLine);
	while (std::getline(crimeFile, line)){
		crimes.push_back(parseCrimeData(line));
		countOfCrimes++;
	}
	std::cout << "[" << countOfCrimes << "]" << endl;
	std::cout << ">> Reading IUCR codes 'IUCR-codes.csv'... ";
	std::getline(iucrFile, dummyLine);
	while (std::getline(iucrFile, line)){
		iucrCodes.push_back(parseIUCRCode(line));
		countOfIUCR++;
	}
	std::cout << "[" << countOfIUCR << "]" << endl;
	std::cout << ">> Reading communities file 'Communities.csv'... ";
	std::getline(communityFile, dummyLine);
	while (std::getline(communityFile, line)){
		communityCodes.push_back(parseCommunityData(line));
		countOfCommunities++;
	}
	std::cout << "[" << countOfCommunities << "]\n" << endl;

	// Sorting IUCR data by code ID to keep the data constiant style with the crime IUCR code
	std::sort(iucrCodes.begin(), iucrCodes.end(), [](IUCRCode a, IUCRCode b){
		return a.getCodeID() < b.getCodeID();
	});

	// Sorting crime data to make the IUCR code counting faster
	std::sort(crimes.begin(), crimes.end(), [](Crime a, Crime b){
		return a.getCode() < b.getCode();
	});
	crimeCounting(crimes, iucrCodes);

	// Sorting IUCR vector by number of crimes per code in order from larges to smallest
	std::sort(iucrCodes.begin(), iucrCodes.end(), [](IUCRCode a, IUCRCode b){
		return a.getCrimeCount() > b.getCrimeCount();
	});
	std::cout << ">> Top-10 Crimes <<" << endl;
	std::cout << "Rank\tIUCR\tNumber\tDescription" << endl;
	printTopIUCR(iucrCodes, 10);
	std::cout << endl << endl << ">> By Community <<\n" << endl;

	// Sorting the crimes vector by community in order from 1...77
	std::sort(crimes.begin(), crimes.end(), [](Crime a, Crime b){
		return a.getCommunity() < b.getCommunity();
	});

	// search by Community number
	std::cout << "Please enter a comunity number [1..77], 0 to stop: ";
	std::cin >> communityNumber;
	while (communityNumber != 0){
		if (communityNumber < 0 || communityNumber > 77){
			std::cout << "** Invalid community number, please try again...\n" << endl;
		}
		else {
			printOutCommunityData(communityNumber, countOfCrimes, crimes, communityCodes, iucrCodes);
		}
		std::cout << "Please enter a comunity number [1..77], 0 to stop: ";
		std::cin >> communityNumber;
	}

	// search by IUCR code
	std::cout << "\n\n>> By IUCR Crime Code <<\n" << endl;
	std::cout << "Please enter an IUCR code [e.g 0110 or 031A], 0000 to stop: ";
	std::cin >> selectedIUCRCode;
	while (selectedIUCRCode != "0000"){
		selectedCodeLocation = std::find_if(iucrCodes.begin(), iucrCodes.end(), [=](IUCRCode a){
			return a.getCodeID() == selectedIUCRCode;
		});
		if (selectedCodeLocation == iucrCodes.end()){
			std::cout << "** Invalid IUCR code please try again...\n" << endl;
		}
		else {
			printOutIUCRData(selectedCodeLocation, selectedIUCRCode, crimes, countOfCrimes);
		}
		std::cout << "Please enter an IUCR code [e.g 0110 or 031A], 0000 to stop: ";
		std::cin >> selectedIUCRCode;
	}
	std::cout << "\n\n>> DONE! << \n" << endl;
	return 0;
}

