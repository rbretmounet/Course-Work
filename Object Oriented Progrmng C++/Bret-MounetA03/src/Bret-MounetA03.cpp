//============================================================================
// Name        : Bret-MounetA03.cpp
// Author      : Raphael Bret-Mounet
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Employee.hpp"
#include <string>
#include <iomanip>

using namespace std;

//Global size
int SIZE = 100;


int main() {
	//Used to get user input.
	string input = " ";

	//Counter used to iterate through employees.
	int counter = 0;

	//Pointer array of employees.
	Employee * employees[SIZE];

	//Initialize employee arrays
	for(int i = 0; i<SIZE; i++)
	{
		employees[i] = nullptr;
	}

	//Loops until user enters stop.
	while (input != "STOP")
	{
		//Create a new class object for employee.
		employees[counter] = new Employee;

		//User prompt.
		cout << "Enter employee name: " << endl;
		getline (cin,input);

		//Check if user entered stop
		if (input == "STOP")
		{
			break;
		}

		//Set input to name class.
		employees[counter]->setName(input);

		//User prompt.
		cout << "Enter hours worked: " << endl;
		getline (cin,input);

		//Check if user entered stop
		if (input == "STOP")
		{
			break;
		}

		//Set input to hours.
		employees[counter]->setHours(stof(input));

		//User prompt.
		cout << "Enter pay rate: " << endl;
		getline (cin,input);

		//Check if user entered stop
		if (input == "STOP")
		{
			break;
		}

		//Set input to rate
		employees[counter]->setRate(stof(input));

		//User Prompt.
		cout << "Hours = " << employees[counter]->getHours() << ", rate = " << employees[counter]->getRate() << endl;
		employees[counter]->payCalc();

		cout << setprecision (2) << fixed << "Regular pay = " << employees[counter]->getRegularPay() << ", overtime pay = " << employees[counter]->getOvertimePay() << ", total pay = " << employees[counter]->getTotalPay() << endl;
		cout << "--------------------" << endl;

		//Iterate counter for next employee
		counter++;

	}

	//Outputs processed employees
	cout << "--------------------" << endl;
	cout << "We processed " << counter << " employees:" << endl;

	//Used to hold totalPayRoll.
	float totalPayRoll = 0;

	// Loops through each employee and adds their total pay together.
	for (int i = 0; i < counter; i++)
	{
		cout << employees[i]->getName() << endl;
		totalPayRoll += employees[i]->getTotalPay();
	}

	//Prints out the total pay of all the employees.
	cout << setprecision (2) << fixed << "Total payroll - $" << totalPayRoll << endl;
	cout << "Program ending";

	//Delete pointer array.
	for(int i=0; i<SIZE; i++)
	{
		delete employees[i];
		employees[i]= NULL;
	}

	return 0;
}


