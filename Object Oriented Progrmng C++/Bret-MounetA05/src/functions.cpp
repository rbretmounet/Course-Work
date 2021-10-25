#include "functions.hpp"
#include <iomanip>

// Function used to print busses
void printBusses(Bus b[]){
	cout << "======================================================================" << endl;
	cout << "Bus ID     Bus Type     Bus Capacity      Mileage    Status" << endl;
	cout << "======================================================================" << endl;
	for (int i = 0; i < Bus::busCount; i++)
	{
		cout << b[i].getBusID() << right << setw(9)
		<< b[i].getType() << right << setw(17)
		<< b[i].getCapacity() << right << setw(17)
		<< b[i].getMileage() << right << setw(9)
		<< b[i].getStatus() << endl;
	}
	cout << "---end of list---" << endl;
}

//function used to add maintenance record to bus class object.
void addMaintenanceRecord(Bus b[])
{
	string busID = " ";
	string date = " ";
	string type = " ";
	string mechanic = " ";

	cout << "Enter Bus ID:" << endl;
	getline(cin,busID);

	cout << "Enter maintenance date:" << endl;
	getline(cin,date);

	cout << "Enter maintenance type:" << endl;
	getline(cin,type);

	cout << "Enter maintenance mechanic:" << endl;
	getline(cin,mechanic);

	for (int i = 0; i < Bus::busCount; i++)
	{
		if (b[i].getBusID() == stoi(busID))
		{
			b[i].maintenance[b[i].active].maintDate = date;
			b[i].maintenance[b[i].active].maintMechanic = mechanic;
			b[i].maintenance[b[i].active].maintType = type;
			b[i].active++;
			cout << "Maintenance element added to bus " << busID << endl;
			return;
		}
	}
	cout << "Bus Not Found." << endl;
	return;

}

//Function used to display the maintenance history of specified bus.
void displayMaintHist(Bus b[])
{
	string busID = " ";
	cout << "Enter Bus ID:" << endl;
	getline(cin,busID);

	for (int i = 0; i < Bus::busCount; i++)
	{
		if (b[i].getBusID() == stoi(busID))
		{
			if (b[i].active == 0)
			{
				cout << "No maintenance history for bus " << busID << endl;
				return;
			}

			cout << "type " << b[i].getType() << " capacity " << b[i].getCapacity() << " mileage " << b[i].getMileage() << endl;
			cout << "Start of maintenance history " << endl;
			for (int c = 0; c < b[i].active; c++){
				cout << "history element " << c << " - " << b[i].maintenance[c].maintDate
						<< ", " << b[i].maintenance[c].maintType <<", "  << b[i].maintenance[c].maintMechanic << endl;
			}
			cout << "End of history for bus " << busID << endl;

			return;
		}
	}
	cout << "Bus Not Found." << endl;
	return;

}

//Function used to compare two specified buses.
void compareBusses(Bus b[])
{
	int firstActive = 0;
	int secondActive = 0;
	string firstBusID = " ";
	string secondBusID = " ";

	cout << "Enter bus ID for the first bus" << endl;
	getline(cin,firstBusID);

	cout << "Enter bus ID for the second bus " << endl;
	getline(cin,secondBusID);

	for (int i = 0; i < Bus::busCount; i++)
	{
		if (b[i].getBusID() == stoi(firstBusID))
		{
			firstActive = i;

		}
		else if (b[i].getBusID() == stoi(secondBusID))
		{
			secondActive = i;

		}
	}
	if(b[firstActive] == b[secondActive]){
		cout << "The buses have the same amount of maintenance history" << endl;
		return;
	}
	if(b[firstActive] > b[secondActive]){
		cout << "Bus " << firstBusID << " has more maintenance history than bus " << secondBusID << endl;
		return;
	}
	else
	{
		cout << "Bus " << firstBusID << " has less maintenance history than bus " << secondBusID << endl;
	}

}

//Function used to copy old bus to new one.
void copyBus(Bus b[])
{
	string oldBus = " ";
	string newBus = " ";

	cout << "Enter Old Bus ID:" << endl;
	getline(cin,oldBus);
	cout << "Enter New Bus ID:" << endl;
	getline(cin,newBus);

	for (int i = 0; i < Bus::busCount; i++)
	{
		if (b[i].getBusID() == stoi(oldBus))
		{

			b[Bus::busCount] = b[i];
			b[Bus::busCount].setBusID(stoi(newBus));
			Bus::busCount++;

			return;
		}
	}

	cout << "Old Bus not found." << endl;
	return;

}

