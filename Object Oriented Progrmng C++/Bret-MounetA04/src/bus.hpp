#ifndef BUS_HPP_
#define BUS_HPP_

using namespace std;

class Bus{
	private:
		int busID;
		char type;
		int capacity;
		int mileage;
		char status;
	public:
		//constructor prototype
		Bus();
		Bus(int, char, int, int, char);

		//setter prototypes
		void setBusStatus(char);

		//getter prototypes
		int getBusID();
		char getType();
		int getCapacity();
		int getMileage();
		char getStatus();

};


#endif