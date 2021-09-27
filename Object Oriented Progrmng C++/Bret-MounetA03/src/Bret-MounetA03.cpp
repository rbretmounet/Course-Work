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

int SIZE = 100;


int main() {
	string input = " ";
	int counter = 0;

	Employee * employees[SIZE];

	for(int i = 0; i<SIZE; i++)
	{
		employees[i] = nullptr;
	}

	while (input != "STOP")
	{
		employees[counter] = new Employee;

		cout << "Enter employee name: " << endl;
		getline (cin,input);

		if (input == "STOP")
		{
			break;
		}

		employees[counter]->setName(input);

		cout << "Enter hours worked: " << endl;
		getline (cin,input);


		if (input == "STOP")
		{
			break;
		}


		employees[counter]->setHours(stof(input));

		cout << "Enter pay rate: " << endl;
		getline (cin,input);

		if (input == "STOP")
		{
			break;
		}

		employees[counter]->setRate(stof(input));

		cout << "Hours = " << employees[counter]->getHours() << ", rate = " << employees[counter]->getRate() << endl;
		employees[counter]->payCalc();

		cout << setprecision (2) << fixed << "Regular pay = " << employees[counter]->getRegularPay() << ", overtime pay = " << employees[counter]->getOvertimePay() << ", total pay = " << employees[counter]->getTotalPay() << endl;
		cout << "--------------------" << endl;

		counter++;

	}
	cout << "--------------------" << endl;
	cout << "We processed " << counter << " employees:" << endl;
	float totalPayRoll = 0;
	for (int i = 0; i < counter; i++)
	{
		cout << employees[i]->getName() << endl;
		totalPayRoll += employees[i]->getTotalPay();
	}
	cout << setprecision (2) << fixed << "Total payroll - $" << totalPayRoll << endl;
	cout << "Program ending";

	return 0;
}


