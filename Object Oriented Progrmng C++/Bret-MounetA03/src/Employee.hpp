#ifndef EMPLOYEE_HPP_
#define EMPLOYEE_HPP_

#include <string>
using namespace std;

class Employee{
	public:
		// Member function prototypes
		void payCalc();

		//Getter prototypes
		string getName();
		float getHours();
		float getRate();
		float getRegularPay();
		float getOvertimePay();
		float getTotalPay();

		//Setter prototypes
		void setName(string n);
		void setHours(float h);
		void setRate(float r);



	private:
		string name;
		float hours;
		float rate;
		float regularPay;
		float overtimePay;
		float totalPay;
};

#endif
