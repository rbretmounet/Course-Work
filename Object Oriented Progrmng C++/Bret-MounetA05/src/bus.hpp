#ifndef BUS_HPP_
#define BUS_HPP_

#include "mainthist.hpp"
using namespace std;

class Bus{
	private:
		//Variables
		int busID;
		char type;
		int capacity;
		int mileage;
		char status;
	public:
		//Variables;
		static int busCount;
		int active; //Ask about active counter.
		MaintHist maintenance[25];
		//constructor prototype
		Bus();

		//Copy constructor prototype
		Bus(Bus &);


		//setter prototypes
		void setBusStatus(char);
		void setBusID(int);
		void setType(char);
		void setCapacity(int);
		void setMileage(int);
		void setStatus(char);


		//getter prototypes
		int getBusID();
		char getType();
		int getCapacity();
		int getMileage();
		char getStatus();

		//Overload function prototypes
		bool operator== (Bus &);
		bool operator> (Bus &);
		void operator= (Bus &);
};


#endif
