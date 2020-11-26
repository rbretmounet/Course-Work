// Lab8_Raphael_Bret-Mounet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "myHeap.h"
#include <ctime>
using namespace std;

int main()
{
    srand(time(0)); // Creates new seed for random number generator.
    const int SIZE = 10; // Size of array
    int array[SIZE]; // Used to store random numbers

    // Console Output
    cout << "Existing array test" << endl;
    cout << "-------------------" << endl;
    cout << "Random array:" << endl;
    cout << "        ";

    // Creates a random number from specified number of times.
    for (int i = 0; i < SIZE; i++)
    {
        // Generates random number between 1-100.
        int randomNumber = rand() % 100 + 1;
        array[i] = randomNumber; // Adds random number to object.
        cout << array[i] << " ";
    }

    myHeap<int> heap = myHeap<int>(array, SIZE); // Creates new heap with given array.
    // Console Output
    cout << endl;
    cout << "Number of nodes (isEmpty() is FALSE):" << endl;
    cout << "        " << heap.getNumberOfNodes() << endl;
    cout << " 10 removes:" << endl;
    cout << "        ";
    // Shows the parent node of heap and then removes the node.
    for (int i = 0; i < SIZE; i++) {
        cout << heap.peekTop() << " ";
        heap.remove();
    }
    // Console Output
    cout << endl;
    cout << endl;


    myHeap<int> newHeap; // Creates a new heap without an empty array.

    // Console Output
    cout << "Starting with empty array test" << endl;
    cout << "------------------------------" << endl;
    cout << "Random array:" << endl;
    cout << "        ";

    // Creates a random number from specified number of times.
    for (int i = 0; i < SIZE; i++)
    {
        // Generates random number between 1-100.
        int randomNumber = rand() % 100 + 1;
        array[i] = randomNumber;// Adds random number to object.
        cout << randomNumber << " ";
    }

    // Console Output
    cout << endl;
    cout << "Number of nodes (isEmpty() is TRUE):" << endl;
    cout << "        " << newHeap.getNumberOfNodes() << endl;

    // Adds random numbers to heap.
    for (int i = 0; i < SIZE; i++)
    {
        newHeap.add(array[i]);
    }

    // Console Output
    cout << " 10 removes:" << endl;
    cout << "        ";

    // Shows the parent node of heap and then removes the node.
    for (int i = 0; i < 10; i++) {
        cout << newHeap.peekTop() << " ";
        newHeap.remove();
    }
 }
