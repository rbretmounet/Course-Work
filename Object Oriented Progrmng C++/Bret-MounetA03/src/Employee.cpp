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
void Employee::payCalc(){

	if (hours > 40){
		regularPay = rate*40;
		overtimePay = (1.5*rate) * (hours-40);
	}else{
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
