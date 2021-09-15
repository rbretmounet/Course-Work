//============================================================================
// Name        : Bret-MounetA1.cpp
// Author      : Raphael Bret-Mounet
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

//Swaps two values
void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

// Generates random numbers and populates array
void random(int size, int *&array){
	//Loops through each array index and assigns random number from 1-100
	for (int i = 0; i < size; i++)
	{
		array[i] = rand() % 100 + 1;
	}
}

// Creates new array and assigns to the array pointer
void dynAlloc(int size, int * &array){
	array = new int[size];
}

// Displays array
void displayArray(int size, int *array){
	for (int i = 0; i<size; i++)
	{
		cout << array[i] << endl;
	}
}

// Sorts the array using bubble sort.
int bubbleSort(int size, int *unsortedArray, int * sortedArray){
	//Copies unsorted array to second array.
	for (int i = 0; i < size; i++){
		sortedArray[i] = unsortedArray[i];
	}
	//Intialize count
	int count = 0;
	
	//Outside loop for 
	for (int i = 0; i < size-1; i++){
		for (int j = 0; j < size-i-1;j++)
		{
  			if (sortedArray[j] > sortedArray[j+1])
			{
				swap(&sortedArray[j], &sortedArray[j+1]);
				count++;
			}
		}
	}
	return count;
}

// Sorts the array using selection sort.
int selectionSort(int size, int * unsortedArray, int * sortedArray){
	for (int i = 0; i < size; i++){
			sortedArray[i] = unsortedArray[i];
		}
		int count = 0;
		for (int i = 0; i < size-1; i++)
		    {
		        int min = i;
		        for (int j = i+1; j < size; j++)
		        if (sortedArray[j] < sortedArray[min])
		        {
		        	min = j;
		        }


		        swap(&sortedArray[min], &sortedArray[i]);
		        count++;
		    }
		return count;
}

//Searches the array for specified value using linear search.
int linearSearch(int * array, int size, int value, int &count){
	for (int i = 0; i < size; i++)
	{
		count++;
		if (array[i] == value)
		{
			return i;
		}
	}
	return -1;
}

//Searches the array using binary search.
int binarySearch(int * array, int size, int value, int &count){
	int left = 0;
	int right = size-1;
	while (left <= right) {
		int m = left + (right - left) / 2;
		count++;

	    if (array[m] == value)
	    {
	        return m;
	    }

	    if (array[m] < value)
	    {
	    	left = m + 1;
	    }
	    else
	    {
	        right = m - 1;
	    }
	}
	return -1;
}

int main() {
	//intialize variables
	int *arrayPointer1 = NULL;
	int *arrayPointer2 = NULL;
	int input = 0;
	
	//Create arrays and assign to pointers.
	dynAlloc(100,arrayPointer1);
	dynAlloc(100,arrayPointer2);
	
	//Populates array with random numbers
	random(100, arrayPointer1);

	//Displays array values.
	cout << "Unsorted Array:" << endl;
	displayArray(100,arrayPointer1);

	//Sorts array with bubble sort
	int iterationCount = bubbleSort(100,arrayPointer1,arrayPointer2);

	//Displays sorted array values
	cout << "Sorted Array:" << endl;
	displayArray(100,arrayPointer2);

	cout << "Count: " << iterationCount << endl;
	
	//Sorts array with selection sort
	iterationCount = selectionSort(100,arrayPointer1,arrayPointer2);

	//Displays sorted array values
	cout << "Sorted Array:" << endl;
	displayArray(100,arrayPointer2);
	
	//Deletes content of pointer and points to null.
	delete [] arrayPointer1;
	arrayPointer1 = NULL;

	cout << "Count: " << iterationCount << endl;
	
	//loop for searching sorted array.
	while (input != -1)
	{	
		//Intialize variables
		int count = 0;
		int result = -1;
		
		//User prompt
		cout << "Enter an Integer to Linearly Search For (-1 to Exit):";
		cin >> input;

		//Checks to see if user exits.
		if (input == -1)
		{
			cout << "Program Terminated."<<endl;
			break;
		}
		
		//Returns results of search
		result = linearSearch(arrayPointer2, 100,input,count);
		
		//Checks if integer was found or not
		if (result == -1){
			cout << "Integer not found!"<< endl;
			cout << "Number of Iterations: " << count << endl;
		}else
		{
			cout << "Integer found!"<< endl;
			cout << "Number of Iterations: " << count << endl;
		}
		
		//User prompt
		cout << "Enter an Integer to Binary Search For (-1 to Exit):";
		cin >> input;

		//Checks if user trys to exit
		if (input == -1)
		{
			cout << "Program Terminated."<<endl;
			break;
		}

		//Resets count and gets result from binary search.
		count = 0;
		result = binarySearch(arrayPointer2, 100,input,count);

		//Checks if interger was found or not
		if (result == -1)
		{
			cout << "Integer not found!"<< endl;
			cout << "Number of Iterations: " << count << endl;
		}else
		{
			cout << "Integer found!"<< endl;
			cout << "Number of Iterations: " << count << endl;
		}
	}

	//Deletes content of pointer and points to null.
	delete [] arrayPointer2;
	arrayPointer2 = NULL;
	return 0;
}
