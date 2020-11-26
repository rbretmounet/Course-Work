// Lab1-Raphael_Bret-Mounet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

void hailstoneSequence(int n, int t); // Used to display and compute hailstone sequence.

int main()
{
    int number; // Used to store the number
    int terms; // Used to store the limit of terms.


    // Prompt user to input number.
    cout << "Number: ";
    cin >> number;

    // Error checking for numbers. Number must be 1 or greater.
    while (number < 1) {
        // Prompts user that number is not valid and to input a new one.
        cout << "Invalid number, please try again." << endl;
        cout << "Number: ";
        cin >> number;
    }

    // Prompt user to input terms.
    cout << "Limit of terms: ";
    cin >> terms;

    // Error checking for terms. Term must be 1 or greater.
    while (terms < 1)
    {
        // Prompts user that term is not valid and to input a new one.
        cout << "Invalid term, please try again." << endl;
        cout << "Limit of terms:";
        cin >> terms;
    }

    hailstoneSequence(number, terms); // Used to display and compute hailstone sequence.

    return 0;
}

// Used to display and compute hailstone sequence.
void hailstoneSequence(int n, int t)
{
    // Checks if sequence is at the end
    if (n == 1)
    {
        // If true than display number and return to main.
        cout << n << endl;
        return;
    }
    // Checks to see if it has reached the end of terms
    else if (t == 0)
    {
        // If true than display message and return to main.
        cout << "Sequence was aborted early." << endl;
        return;
    }
    // Checks to see if number is even.
    else if (n % 2 == 0)
    {
        // If true then display number and divide number by 2.
        cout << n << endl;
        n = n / 2;
    }
    // Checks to see if number is odd.
    else
    {
        // If true then display number and multiply number and add 1. 
        cout << n << endl;
        n = (3*n)+ 1;
    }

    hailstoneSequence(n, t-1); // Loops back to function and takes one away from terms.
        
}
