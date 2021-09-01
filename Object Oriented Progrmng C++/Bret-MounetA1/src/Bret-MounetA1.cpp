//============================================================================
// Name        : Bret-MounetA1.cpp
// Author      : Raphael Bret-Mounet
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;

}

void random(int size, int *&array){
	for (int i = 0; i < size; i++){
		array[i] = rand() % 100 + 1;
	}
}

void dynAlloc(int size, int * &array){
	array = new int[size];
	for (int i=0; i<size; i++) {
	    array[i] = 0;
	}
}

void displayArray(int size, int *array){
	for (int i = 0; i<size; i++){
			cout << array[i] << endl;
		}
}

int bubbleSort(int size, int *unsortedArray, int * sortedArray){
	for (int i = 0; i < size; i++){
		sortedArray[i] = unsortedArray[i];
	}
	int count = 0;
	for (int i = 0; i<size-1; i++){
		for (int j = 0; j< size-i-1;j++)
		{
  			if (sortedArray[j] > sortedArray[j+1]){
				swap(&sortedArray[j], &sortedArray[j+1]);
				count++;
			}
		}
	}
	return count;
}

int selectionSort(int size, int * unsortedArray, int * sortedArray){
	for (int i = 0; i < size; i++){
			sortedArray[i] = unsortedArray[i];
		}
		int count = 0;
		for (int i = 0; i < size-1; i++)
		    {
		        int min_idx = i;
		        for (int j = i+1; j < size; j++)
		        if (sortedArray[j] < sortedArray[min_idx]){
		        	min_idx = j;
		        }


		        swap(&sortedArray[min_idx], &sortedArray[i]);
		        count++;
		    }
		return count;
}
int linearSearch(int * array, int size, int value, int &count){
	for (int i = 0; i < size; i++){
		count++;
		if (array[i] == value){
			return i;
		}
	}
	return -1;
}

int binarySearch(int * array, int size, int value, int &count){
	int left = 0;
	int right = size-1;
	while (left <= right) {
		int m = left + (right - left) / 2;
		count++;

	    if (array[m] == value){
	        return m;
	    }

	    if (array[m] < value){
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
	int *arrayPointer1 = NULL;
	int *arrayPointer2 = NULL;
	int input = 0;

	dynAlloc(100,arrayPointer1);
	dynAlloc(100,arrayPointer2);

	random(100, arrayPointer1);
	cout << "Unsorted Array:" << endl;
	displayArray(100,arrayPointer1);

	int iterationCount = bubbleSort(100,arrayPointer1,arrayPointer2);
	cout << "Sorted Array:" << endl;
	displayArray(100,arrayPointer2);

	cout << "Count: " << iterationCount << endl;

	iterationCount = selectionSort(100,arrayPointer1,arrayPointer2);
	cout << "Sorted Array:" << endl;
	displayArray(100,arrayPointer2);

	delete [] arrayPointer1;
	arrayPointer1 = NULL;

	cout << "Count: " << iterationCount << endl;

	while (input != -1){
		int count = 0;
		int result = -1;
		cout << "Enter an Integer to Linearly Search For (-1 to Exit):";
		cin >> input;
		if (input == -1)
		{
			cout << "Program Terminated."<<endl;
			break;
		}

		result = linearSearch(arrayPointer2, 100,input,count);

		if (result == -1){
			cout << "Integer not found!"<< endl;
			cout << "Number of Iterations: " << count << endl;
		}else
		{
			cout << "Integer found!"<< endl;
			cout << "Number of Iterations: " << count << endl;
		}

		cout << "Enter an Integer to Binary Search For (-1 to Exit):";
		cin >> input;
		if (input == -1)
		{
			cout << "Program Terminated."<<endl;
			break;
		}

		count = 0;
		result = binarySearch(arrayPointer2, 100,input,count);

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

	return 0;
}
