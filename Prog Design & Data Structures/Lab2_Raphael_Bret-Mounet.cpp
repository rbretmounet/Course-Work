#include <iostream>
#include <stack>
#include <fstream>
#include <string>
using namespace std;

#define FILENAME "test.txt"

int main()
{
    ifstream f(FILENAME); // Specifies file.
    char letter; // Used to store letters from temp.
    stack<char> stack; // Stores chars on stack.
    string tmp; // Stores the line from text file.
    bool failed = false; // Used for when operation has failed.
    
    // Checks to make sure file loaded.
    if (!f.good())
    {
        // If not then display error and exit program.
        cout << "Invalid File." << endl;
        exit(-1);
    }

    // Gets the content of specified file
    while (getline(f, tmp))
    {
        // Checks to see if it is at the end of the file.
        if (f.eof())
        {
            // If true then exit.
            break;
        }

        // Loops to find the letter in the string that is taken from file.
        for (int i = tmp.size(); i > 0; i--)
        {
            // Checks to see if letter is detected.
            if (isalpha(tmp[i]))
            {
                // If true then store letter in char and break out of loop.
                letter = tmp[i]; 
                break;
            }
      
        }

        // Checks to see if string contains a 1 and that it isnt a -1
        if (tmp.find('1') != string::npos && tmp.find('-') == string::npos)
        {
            // If true then push letter to the stack
            stack.push(letter);
        }
        // Checks to see if string contains a 2
        else if (tmp.find('2') != string::npos)
        {
            // Checks to see if the top of the stack is matches the current letter.
            if (stack.top() == letter)
            {
                // If true then remove letter from top of stack and set failed to false;
                stack.pop();
                failed = false;
            }
            // Otherwise it has failed.
            else
            {
                failed = true;
            }
        }
        // Checks to see if string contains 0 or -1, the stack is empty and failed is set to false.
        else if (tmp.find('0') != string::npos && stack.empty() && failed == false|| tmp.find('-') != string::npos && stack.empty() && failed == false)
        {
            // If true then display valid.
            cout << "valid" << endl;
        }
        // If everything else is not true.
        else
        {
            // Clears the stack
            while (stack.size() > 0)
            {
                stack.pop();
            }
            cout << "not valid" << endl; // Displays not valid.
        }
    }
}

