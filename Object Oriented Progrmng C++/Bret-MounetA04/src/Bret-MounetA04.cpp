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
	//Pointer array of busses.
	Bus * busses[SIZE];

	//Initialize employee arrays
	for(int i = 0; i<SIZE; i++)
	{
		busses[i] = nullptr;
	}

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
		busses[counter] = new Bus(stoi(line.substr(0,5)), line[5] , stoi(line.substr(6,3)), stoi(line.substr(9,8)), line[16]);

		counter++;

	}

	//String used for user input.
	string input = " ";

	//Loops until used exits.
	while(input != "X")
	{
		//User prompt
		cout << "Enter transaction code (D=display, L=list a bus, C=change, X=exit)" << endl;
		getline(cin,input);

		//If user input is D then print busses.
		if (input == "D")
		{
			printBusses(busses);
		}

		//If user input is L then search for specified bus
		if (input.substr(0,1) == "L")
		{
			searchBus(busses,input.substr(2,5));
		}

		//If user input is C then change the status of specified bus
		if (input.substr(0,1) == "C")
		{
			changeStatus(busses,input.substr(2,5),input[8]);
		}

		//If user input is X then exit program.
		if (input == "X")
		{
			cout << "Thank you and have a nice day!" << endl;
			break;
		}
	}

	//Delete pointer array.
	for(int i=0; i<SIZE; i++)
	{
		delete busses[i];
		busses[i]= NULL;
	}

	return 0;
}
