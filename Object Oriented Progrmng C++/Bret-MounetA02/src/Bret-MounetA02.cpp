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

//Global Variable for array size.
int SIZE = 100;

//Struct used to store student data.
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
	//Declares ifstream variable
	ifstream inFile;

	//Opens a2data.input file
	inFile.open("src/a2data.input",ios::in);

	//Checks to make sure file opened properly otherwise error pops up.
	if (!inFile.is_open())
	{
		cout << "ERROR: File did load." << endl;
		exit(1);
	}

	//Initializes counter for struct objetcts.
	int objects = 0;

	//Pointer array used to store student structs.
	StudentADT * studentStructs[SIZE];

	//Initializes pointer array with nullptr.
	for(int i = 0; i<SIZE; i++)
	{
		studentStructs[i] = nullptr;
	}

	//Loops until gets to the end of the file.
	while(!inFile.eof())
	{
		//Variables used to store student data from file.
		char studentData[53];
		char fName[11];
		char lName[21];
		char sID[9];
		char age[3];
		string s_ID;

		//Reads content of file and stores in c-string studentData.
		inFile.read(studentData,52);

		//checks if end of file is reached.
		if (inFile.eof())
		{
			break;
		}

		//Sets end of c-strings to null.
		studentData[52]= '\0';
		fName[10] = '\0';
		lName[20] = '\0';
		sID[8] = '\0';
		age[2] = '\0';

		//Takes specific part of line that contains the first name and puts it into c-string.
		for (int i = 0; i<10; i++)
		{
			fName[i] = studentData[i];
		}

		//Used to start at the 21st character in the student line.
		int b = 20;

		//Takes specific part of line that contains the last name and puts it into c-string.
		for (int i = 0; i<20; i++)
		{
			lName[i] = studentData[b];

			b++;
		}

		//Used to start at the 41st character in the student line.
		b = 41;

		//Takes specific part of line that contains the student id and puts it into c-string.
		for (int i = 0; i<8; i++)
		{
			sID[i] = studentData[b];
			b++;
		}

		//Used to start at the 49th character in the student line.
		b = 49;

		//Takes specific part of line that contains the student age and puts it into c-string.
		for (int i = 0; i<3; i++)
		{
			age[i] = studentData[b];
			b++;
		}

		//Creates new student struct object in pointer array.
		studentStructs[objects] = new StudentADT;

		//Sets firstName in struct to to first name from file.
		studentStructs[objects]->firstName = fName;

		//Sets middleInitial in struct to to middle initial from file.
		studentStructs[objects]->middleIntial = studentData[10];

		//Sets campusCode in struct to to campus code from file.
		studentStructs[objects]->campusCode = studentData[40];

		//Sets lastName in struct to to last name from file.
		studentStructs[objects]->lastName = lName;

		//Sets studentID in struct to to student ID from file.
		studentStructs[objects]->studentID = sID;

		//Sets age in struct to to student's age from file.
		studentStructs[objects]->age = atoi(age);

		//Increment objects counter to get to next student.
		objects++;

	}
	//Close file.
	inFile.close();

	//Initialize pointer to point to student struct with the oldest age.
	StudentADT *oldestAge;

	//Display student data.
	displayStudents(studentStructs);

	//Display oldest student's name and average student age.
	cout << "Average Age of Students: " << ageCalc(studentStructs,oldestAge) << endl;
	cout << "Oldest Student: " << oldestAge->firstName.substr(0,6) << oldestAge->lastName << endl;

	//Delete pointers and pointer array.
	delete oldestAge;
	oldestAge = NULL;

	for(int i=0; i<SIZE; i++)
	{
		delete studentStructs[i];
		studentStructs[i]= NULL;
	}


	return 0;
}

//Fuction used to display all students info.
void displayStudents(StudentADT *structs[]){
	//counter used to iterate through student objects.
	int i = 0;

	//Header for displaying student info.
	cout << "Last Name           MI        First Name  Campus Code    Sequence    Age" << endl;
	cout << "========================================================================" << endl;

	//Loops until it reaches an empty array element.
	while (structs[i] != nullptr)
	{
		//Prints out all the students info.
		cout << structs[i]->lastName << structs[i]->middleIntial << "         "<< structs[i]->firstName << "     " << structs[i]->campusCode << "           "  << structs[i]->studentID << "    " << structs[i]->age << endl;
		i++;
	}

}

//Function used for to calculate the students average age and find the oldest student.
int ageCalc(StudentADT *structs[], StudentADT * &oldestAge){

	//Counter used to iterate through student objects.
	int i = 0;

	//Used to keep totalAge of students.
	int totalAge = 0;

	//Sets oldesAge to the first student.
	oldestAge = structs[0];

	//Loops until it reaches empty array element.
	while (structs[i] != nullptr)
	{
		//Adds students age to totalAge.
		totalAge += structs[i]->age;

		//Compares current age to oldest age and if greater sets that student to oldestAge.
		if(structs[i]->age > oldestAge->age)
		{
			oldestAge = structs[i];
		}

		//Increment to next object.
		i++;
	}

	//Takes average of students.
	int averageAge = totalAge/(i);

	return averageAge;

}
