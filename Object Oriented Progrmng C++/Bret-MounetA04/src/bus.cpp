#include "bus.hpp"
using namespace std;

//constructors
Bus::Bus(){
	busID = 0;
	capacity = 0;
	mileage = 0;
	type = ' ';
	status = ' ';
}

Bus::Bus(int i, char t, int c, int m , char s){
	busID = i;
	type = t;
	capacity = c;
	mileage = m;
	status = s;
}

//setter
void Bus::setBusStatus(char s){status = s;}

//getters
int Bus::getBusID(){return busID;}
char Bus::getType(){return type;}
int Bus::getCapacity(){return capacity;}
int Bus::getMileage(){return mileage;}
char Bus::getStatus(){return status;}
