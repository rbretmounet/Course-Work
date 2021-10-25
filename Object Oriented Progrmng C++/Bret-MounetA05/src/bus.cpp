#include "bus.hpp"
using namespace std;

//constructors
Bus::Bus(){
	busID = 0;
	capacity = 0;
	mileage = 0;
	type = ' ';
	status = ' ';
	active = 0;
}

//Copy constructor
Bus::Bus(Bus &rhs)
{
	type = rhs.type;
	capacity = rhs.type;
	status = 'n';
	busID = 0;
	mileage = 0;
	rhs.setStatus('r');
	active = 0;
}


//Overload Functions
bool Bus::operator== (Bus &rhs){
	if (this->active == rhs.active)
	{
		return true;
	}

	return false;
}

bool Bus::operator> (Bus &rhs)
{
	if (this->active > rhs.active)
	{
		return true;
	}
	return false;

}


void Bus::operator= (Bus &rhs){
	this->type = rhs.type;
	this->capacity = rhs.capacity;
	this->status = 'n';
	rhs.status = 'r';
	return;
}

//setters
void Bus::setBusStatus(char s){status = s;}
void Bus::setBusID(int i){busID = i;}
void Bus::setType(char t){type = t;}
void Bus::setCapacity(int c){capacity = c;}
void Bus::setMileage(int m ){mileage = m;}
void Bus::setStatus(char s){status = s;}

//getters
int Bus::getBusID(){return busID;}
char Bus::getType(){return type;}
int Bus::getCapacity(){return capacity;}
int Bus::getMileage(){return mileage;}
char Bus::getStatus(){return status;}
