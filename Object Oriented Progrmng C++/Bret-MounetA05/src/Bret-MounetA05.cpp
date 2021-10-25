//============================================================================
// Name        : Bret-MounetA04.cpp
// Author      : Raphael Bret-Mounet
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "bus.hpp"
#include "functions.hpp"
#include <string>

using namespace std;

int SIZE = 50;
int Bus::busCount = 0;

int main() {

	//Declares ifstream variable
	ifstream inFile;

	//Opens a4dataF21.txt file
	inFile.open("src/a4dataF21.txt",ios::in);

	//Checks to make sure file opened properly otherwise error pops up.
	if (!inFile.is_open())
	{
		cout << "ERROR: File did load." << endl;
		exit(1);
	}
	//Static array of busses.
	Bus busses[SIZE];

	// String variable used to store file input.
	string line = " ";

	//counter used to iterate through busses.
	int counter = 0;

	//Loops until gets to the end of the file.
	while(!inFile.eof())
	{
		//Gets file input.
		getline(inFile,line);

		//Check if at end of file.
		if (inFile.eof()){
			break;
		}

		//Checks to see if amount of objects has reached the max.
		if (counter >= SIZE){
			cout << "Reached maximum number of busses" << endl;
			break;
		}

		//Creates new bus object with file info

		busses[counter].setBusID(stoi(line.substr(0,5)));
		busses[counter].setType(line[5]);
		busses[counter].setCapacity(stoi(line.substr(6,3)));
		busses[counter].setMileage(stoi(line.substr(9,8)));
		busses[counter].setStatus(line[16]);

		Bus::busCount++;

		counter++;

	}

	//print buses.
	printBusses(busses);

	//String used for user input.
	string input = " ";

	//Loops until used exits.
	while(input != "X")
	{
		//User prompt
		cout << "Enter transaction code (D=display, L=list a bus and maintenance history, C=compare two buses, M=add maintenance record, O=copy buses, X=exit)" << endl;
		getline(cin,input);

		//If user input is M then prompt user for adding maintenance record.
		if(input == "M"){
			addMaintenanceRecord(busses);
		}

		//If user input is D then print busses.
		if (input == "D")
		{
			printBusses(busses);
		}

		//If user input is L then print specified bus' maintenance history.
		if(input == "L")
		{
			displayMaintHist(busses);
		}

		////If user input is O then copy specified bus id to new bus.
		if(input == "O")
		{
			copyBus(busses);
		}

		//If user input is C then compare two specified buses.
		if (input == "C")
		{
			compareBusses(busses);
		}

		//If user input is X then exit program.
		if (input == "X")
		{
			cout << "Thank you and have a nice day!" << endl;
			break;
		}
	}


	return 0;
}
