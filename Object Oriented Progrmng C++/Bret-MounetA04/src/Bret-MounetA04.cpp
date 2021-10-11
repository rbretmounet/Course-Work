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
#include <cstring>
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

	string line;
	char ID[6];
	char type[2];
	char cap[4];
	char mile[8];
	char status[2];

	ID[5]= '\0';
	type[1] = '\0';
	cap[3] = '\0';
	mile[7] = '\0';
	status[1] = '\0';

	//Loops until gets to the end of the file.
	while(!inFile.eof())
	{
		getline(inFile,line);
		strcpy(ID, line.c_str());

		cout << ID << endl;



	}

	//Pointer array of busses.
	Bus * busses[SIZE];

	//Initialize employee arrays
	for(int i = 0; i<SIZE; i++)
	{
		busses[i] = nullptr;
	}


	return 0;
}
