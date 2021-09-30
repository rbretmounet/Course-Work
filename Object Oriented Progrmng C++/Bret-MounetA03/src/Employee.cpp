#include "Employee.hpp"
using namespace std;

//Constructor
Employee::Employee(){
	rate = 0;
	hours = 0;
	regularPay = 0;
	overtimePay = 0;
	totalPay = 0;
}

// Function used to calculate the employee's pay
void Employee::payCalc(){\
	//Checks to see if the employee has more than 40 hours
	if (hours > 40){
		//If true that calculate regular pay up to 40 hours and overtime pay after 40 hours.
		regularPay = rate*40;
		overtimePay = (1.5*rate) * (hours-40);
	}else{
		//Otherwise no overtime pay and only regular pay
		regularPay = rate*hours;
		overtimePay = 0;
	}
	totalPay = overtimePay + regularPay;

}
//Getters
string Employee::getName() {return name;}
float Employee::getHours() {return hours;}
float Employee::getRate() {return rate;}
float Employee::getRegularPay() {return regularPay;}
float Employee::getOvertimePay() {return overtimePay;}
float Employee::getTotalPay() {return totalPay;}

//Setters
void Employee::setName(string n){name = n;}
void Employee::setHours(float h){hours = h;}
void Employee::setRate(float r){rate = r;}
