//============================================================================
// Name        : Bret-MounetA02.cpp
// Author      : Raphael Bret-Mounet
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<fstream>
#include<cstring>
#include <string>

using namespace std;

int SIZE = 100;

struct StudentADT
{
	string firstName;
	string lastName;
	string studentID;
	char campusCode;
	char middleIntial;
	int age;
};

//Function Prototypes
void displayStudents(StudentADT *structs[]);
int ageCalc(StudentADT *structs[],StudentADT *&oldestAge);


int main() {
	ifstream inFile;
	inFile.open("/Users/raphaelbret-mounet/Documents/GitHub/Course-Work/Object Oriented Progrmng C++/Bret-MounetA02/src/a2data.input",ios::in);
	if (!inFile.is_open())
	{
		cout << "ERROR: File did load." << endl;
		exit(1);
	}
	int objects = 0;
	StudentADT * studentStructs[SIZE];
	for(int i = 0; i<SIZE; i++)
	{
		studentStructs[i] = nullptr;
	}
	while(!inFile.eof())
	{
		char studentData[53];
		char fName[11];
		char lName[21];
		char sID[9];
		char age[3];
		string s_ID;

		inFile.read(studentData,52);

		if (inFile.eof())
		{
			break;
		}

		studentData[52]= '\0';
		fName[10] = '\0';
		lName[20] = '\0';
		sID[8] = '\0';
		age[2] = '\0';

		for (int i = 0; i<10; i++)
		{
			fName[i] = studentData[i];
		}

		int b = 20;
		for (int i = 0; i<20; i++)
		{
			lName[i] = studentData[b];

			b++;
		}

		b = 41;
		for (int i = 0; i<8; i++)
		{
			sID[i] = studentData[b];
			b++;
		}

		b = 49;
		for (int i = 0; i<3; i++)
		{
			age[i] = studentData[b];
			b++;
		}

		studentStructs[objects] = new StudentADT;
		studentStructs[objects]->firstName = fName;
		studentStructs[objects]->middleIntial = studentData[10];
		studentStructs[objects]->campusCode = studentData[40];
		studentStructs[objects]->lastName = lName;
		studentStructs[objects]->studentID = sID;
		studentStructs[objects]->age = atoi(age);
		objects++;

	}
	inFile.close();
	StudentADT *oldestAge;
	displayStudents(studentStructs);
	cout << "Average Age of Students: " << ageCalc(studentStructs,oldestAge) << endl;
	cout << "Oldest Student: " << oldestAge->firstName.substr(0,6) << oldestAge->lastName << endl;
	return 0;
}

void displayStudents(StudentADT *structs[]){
	int i = 0;
	cout << "Last Name           MI        First Name  Campus Code    Sequence    Age" << endl;
	cout << "========================================================================" << endl;
	while (structs[i] != nullptr)
	{
		cout << structs[i]->lastName << structs[i]->middleIntial << "         "<< structs[i]->firstName << "     " << structs[i]->campusCode << "           "  << structs[i]->studentID << "    " << structs[i]->age << endl;
		i++;
	}

}

int ageCalc(StudentADT *structs[], StudentADT * &oldestAge){
	int i = 0;
	int totalAge = 0;
	oldestAge = structs[0];

	while (structs[i] != nullptr)
	{
		totalAge += structs[i]->age;
		if(structs[i]->age > oldestAge->age)
		{
			oldestAge = structs[i];
		}
		i++;
	}


	int averageAge = totalAge/(i);

	return averageAge;

}
