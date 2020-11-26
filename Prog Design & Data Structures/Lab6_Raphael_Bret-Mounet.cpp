// Lab6_Raphael_Bret-Mounet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SortableBag.h"
#include <vector>
#include <ctime>

using namespace std;
void randomIntegers(SortableBag<int>&,int); // Function used to genereate random numbers and fill the object.
void printNumbers(vector<int>&); // Function used to print out numbers inside of vector.
bool sorted(vector<int>&); // Function used to check if vector is sorted in ascending order.


int main()
{
    SortableBag<int> numbers; // Creates an object for sortablebag
    srand(time(0)); // Creates new seed for random number generator.

    randomIntegers(numbers,50); // Generates random numbers.

    vector<int> Numbers = numbers.toVector(); // Grabs unsorted numbers

    cout << "Requesting sort..." << endl;
    numbers.bucketSort(); // Sorts random numbers in ascending order.

    bool isSorted = sorted(Numbers); // Checks to see if vector is not sorted.

    // If vector is not sorted then print unsorted numbers.
    if (!isSorted)
    {
        printNumbers(Numbers); // prints numbers out to console
    }

    Numbers = numbers.toVector(); // Stores sorted numbers inside of vector.
    isSorted = sorted(Numbers); // Checks to see if vector is sorted.

    // If vector is sorted then print sorted numbers.
    if (isSorted)
    {
        cout << "Here's the new bag..." << endl;
        printNumbers(Numbers); // prints numbers out to console
    }

    return 0;
}

// Function used to genereate random numbers and fill the object.
void randomIntegers(SortableBag<int>& randomNumbers, int n) {

    
    // Creates a random number 100 times.
    for (int i = 0; i < n; i++)
    {
        // Generates random number between 1-100.
        int randomNumber = rand() % 100 + 1;
        randomNumbers.add(randomNumber); // Adds random number to object.
    }

    return;
}

// Function used to print out numbers inside of vector.
void printNumbers(vector<int>& numbers)
{
    for (int i = 0; i < numbers.size(); i++)
    {
        cout << numbers[i] << " ";
    }
    cout << endl;
    cout << endl;
    return;
}

// Function used to check if vector is sorted in ascending order.
bool sorted(vector<int>& numbers)
{
    // Iterates through the vector.
    for (int i = 0; i < numbers.size() - 1; i++)
    {
        // If number on left is greater than the right number
        if (numbers[i] > numbers[i + 1])
        {
            // Than return false.
            return false;
        }
    }

    // Otherwise return true.
    return true;
}

