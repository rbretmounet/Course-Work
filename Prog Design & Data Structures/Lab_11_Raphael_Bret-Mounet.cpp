#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <queue>
using namespace std;

//
// This file provides a starting point for Lab #11.  It reads the 
// input file (.csv), builds a graph from the adjacencies in the file,
// and will print the friends list for any node requested.
//
// The graph is a simple adjacency list format -- each node (struct Person) 
// contains a string vector of all of its friend nodes.
//

#define IS_QUIT(s) (s == "X" || s == "x")
#define FILENAME "facebook.csv"
using namespace std;

struct Person {
    vector<string> friends;
    bool visited = false;
};

void parse_line(const string& str,
    vector<string>& line) {
    istringstream istr(str);
    string tmp;
    while (getline(istr, tmp, ',')) {
        line.push_back(tmp);
    }
}

void breathFirstSearch(map<string, Person> people, string startingName,
    string endingName) {
    string currentName;
    Person tmpNode, nextNode;
    queue<string> q;
    q.push(startingName);

    // Loops through queue
    while (!q.empty())
    {
        currentName = q.front();
        q.pop();
        
        tmpNode = people[currentName];
        // Checks to see if there is a connection between starting name and ending name.
        if (currentName == endingName) {
            cout << "There IS a path between these two people." << endl << endl;
            return;
        }

        // Skips over person if already visited
        if (tmpNode.visited)
        {
            continue;
        }

        // Marks person as visited.
        tmpNode.visited = true;
        people[currentName] = tmpNode;

        // Loops through all the surrounding nodes.
        for (int i = 0; i < tmpNode.friends.size(); i++)
        {
            nextNode = people[tmpNode.friends[i]];
            
            if (nextNode.visited)
                continue;     
            q.push(tmpNode.friends[i]);
        }
    }
    
    cout << "There is NOT a path between these two people." << endl << endl;
    return;
}

int main() {
    ifstream inFile(FILENAME);
    vector<string> row;
    vector<string> names;
    map<string, Person> everyone;
    string inputLine;

    // Verify that the file open was OK
    if (!inFile.good()) {
        cerr << "Invalid file." << endl;
        return (-1);
    }

    // Read the header line of the file (first line, contains column labels).
    // We save this line (names) so we can lookup the string names in the
    // below loop.
    getline(inFile, inputLine);
    parse_line(inputLine, names);

    // Reach each subsequent entry
    while (getline(inFile, inputLine)) {
        if (inFile.eof())
            break;
        vector<string> row;
        Person p;
        parse_line(inputLine, row);
        // Start at 1 (0th field is the string name)
        for (size_t i = 1; i < row.size(); i++) {
            int adj_status = atoi(row[i].c_str());
            // A '1' indicates an adjacency, so skip if we get a '0'
            // If there is an adjacency to this person, push the string name
            // of that person on the adjacency list.
            if (adj_status == 1)
                p.friends.push_back(names[i]);
        }
        // Add this (new) person to the map.
        // In this map, the key is the string name of the person, and
        // the value is their Person structure (adjacency list).
        everyone.insert(make_pair(row[0], p));
    }

    for (;;) {

        // User Prompt
        cout << "Enter the starting name (X to quit): ";
        getline(cin, inputLine);
        cout << endl;
        if (IS_QUIT(inputLine))
            break;
        string start = inputLine;

        // User Prompt
        cout << "Enter the ending name (X to quit): ";
        getline(cin, inputLine);
        if (IS_QUIT(inputLine))
            break;
        string end = inputLine;

        breathFirstSearch(everyone, start, end); //Used to search for path between two people.
    }
    cout << "Exiting..." << endl;
    return (0);
}
