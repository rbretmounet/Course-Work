// Lab0-Part3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main()
{
    int randomInts[100] = { };

    for (int i = 0; i < 100; i++)
    {
        int randomNumber = (rand()% 100) + 1;
        randomInts[i] = randomNumber;
    }

    int odds[100] = {};
    int evens[100] = {};

    for (int b = 0; b < 100; b++) 
    {
        if (randomInts[b] % 2 != 0)
        {
            odds[b] = randomInts[b];
        }
        else
        {
            evens[b] = randomInts[b];
        }      
    }

    cout << "Odds: ";
    for (int c = 0; c < 100; c++)
    {
        if (odds[c] != 0) 
        {
            cout << odds[c] << " ";
        }
        
    }

    cout << endl;
    cout << "Evens: ";
    for (int d = 0; d < 100; d++)
    {
        if (evens[d] != 0)
        {
            cout << evens[d] << " ";
        }
    }

}

