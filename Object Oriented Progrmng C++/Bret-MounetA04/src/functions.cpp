#include "functions.hpp"
#include <iomanip>

// Function used to print busses
void printBusses(Bus *b[]){
	int i = 0;
	cout << "======================================================================" << endl;
	cout << "Bus ID     Bus Type     Bus Capacity      Mileage    Status" << endl;
	cout << "======================================================================" << endl;
	while (b[i] != nullptr)
	{
		cout << b[i]->getBusID() << right << setw(9)
		<< b[i]->getType() << right << setw(17)
		<< b[i]->getCapacity() << right << setw(17)
		<< b[i]->getMileage() << right << setw(9)
		<< b[i]->getStatus() << endl;
		i++;
	}
	cout << "---end of list---" << endl;
}

// Function used to search for specific bus
void searchBus(Bus *b[],string value){
	int i = 0;
	while (b[i] != nullptr)
	{
		if (b[i]->getBusID() == stoi(value))
		{
			cout << "======================================================================" << endl;
			cout << "Bus ID     Bus Type     Bus Capacity      Mileage    Status" << endl;
			cout << "======================================================================" << endl;
			cout << b[i]->getBusID() << right << setw(9)
			<< b[i]->getType() << right << setw(17)
			<< b[i]->getCapacity() << right << setw(17)
			<< b[i]->getMileage() << right << setw(9)
			<< b[i]->getStatus() << endl;
			cout << "---end of list---" << endl;
			return;
		}
		i++;
	}
	cout << "Not Found." << endl;
}

//Function used to change status of specific bus.
void changeStatus(Bus *b[], string value, char entry)
{
	int i = 0;
	while (b[i] != nullptr)
	{
		if (b[i]->getBusID() == stoi(value))
		{
			b[i]->setBusStatus(entry);
			cout << "Change successful" << endl;
			return;
		}
		i++;
	}
	cout << "Not Found." << endl;
}
