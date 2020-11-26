// Lab7_Raphael_Bret-Mounet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <string>
#include <fstream>
#include <iomanip> 
using namespace std;

#define FILENAME "customers.csv"

void parse_line(const string& str, vector<string>& row) {
    istringstream istr(str);
    string tmp;
    while (getline(istr, tmp, ',')) {
        row.push_back(tmp);
    }
}

int main()
{
    map<string, string> customerInfo; // Used to store costumer info.
    map<string, string>::iterator min, max; // Used to iterate through map.
    ifstream inFile(FILENAME); // specifies file to be used.
    string inputLine; // Used to store line from csv file.
    string minInput; // Used to store user input for min key.
    string maxInput; // Used to store user input for max key.


    int i = 0;

    // Itterates through each row of the csv.
    while (getline(inFile, inputLine)) {
        vector<string> row; // Used to store info from that row.
        parse_line(inputLine, row); // Function used to add info to row.

        // Checks to see if it is past the first row.
        if (i > 0){
            // If true than store customer id and monthly charges to map.
            customerInfo.insert(make_pair(row[0], row[18]));
        }
        i++;
    }

    // Loops until user enter x to exit the program.
    while (true) {
        cout << "Enter the lower and upper values of the range (X to quit):" << endl;
        cin >> maxInput;

        // Checks to see if input is an X
        if (maxInput == "X" || maxInput == "x") {
            // If true then exit program
            cout << "Exiting..." << endl;
            break;
        }

        cin >> minInput;

        // Checks to see if one of the inputs is X
        if (minInput == "X" || maxInput == "X" || minInput == "x" || maxInput == "x")
        {
            // If true then exit program
            cout << "Exiting..." << endl;
            break;
        }

        // Checks to make sure that the lower bound is greater then the upper bound
        if (minInput > maxInput) {
            // If true than swap them.
            swap(minInput, maxInput);
        }

        min = customerInfo.lower_bound(minInput); // Sets the lower itterator to the specified key.
        max = customerInfo.upper_bound(maxInput); // Sets the upper itterator to the specified key.

        cout << "The customers in this range are:" << endl;

        // Itterates through customer info.
        for (; min != max; ++min)
        {
            double monthlyCharge = 0;
            stringstream charge(min->second); 
            charge >> monthlyCharge; // Converts string to double so you can set precision.

            cout << "	" << min->first << ": $" << setprecision(2) << fixed << monthlyCharge << endl;
        }
    }
   
}

