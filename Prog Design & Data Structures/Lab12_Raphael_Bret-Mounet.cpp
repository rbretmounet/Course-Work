#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <queue>
#include <stack>
using namespace std;

#define IS_QUIT(s) (s == "X" || s == "x")
#define FILENAME "fb_weighted.csv"
using namespace std;

// A node in the Facebook graph
struct Person {
    int best_weight;        // The sum of the weights along the best path
    string best_parent;     // The parent node for the best path
    vector<string> friends; // String names of the friend edges
    vector<int> weights;    // Weights for each friend edge
};
struct PersonCandidate {
    string name;
    int weight;
    string parent;
    bool operator < (const PersonCandidate &rhs) const {
        return weight > rhs.weight;
    }
};

void parse_line(const string& str,
    vector<string>& line) {
    istringstream istr(str);
    string tmp;
    while (getline(istr, tmp, ',')) {
        line.push_back(tmp);
    }
}

void addToTent(priority_queue<PersonCandidate> &pq, Person p, string parent)
{
    PersonCandidate candidate; 
    for (int i = 0; i < p.friends.size(); i++)
    {
        candidate.name = p.friends[i];
        candidate.weight = p.weights[i] + p.best_weight;
        candidate.parent = parent;

        pq.push(candidate);
    }
}
// Output the shortest path
// - everyone:  reference variable to the graph
// - starting:  string name of the starting person
// - ending: string name of the ending person
bool dijkstra(map<string, Person>& everyone,
    string starting, string ending) {

  
    priority_queue<PersonCandidate> pq;

    Person& p = everyone[starting];
    p.best_weight = 0;
    p.best_parent = "";

    addToTent(pq, p, starting);
  
    while (!pq.empty()) 
    {
        PersonCandidate pc = pq.top();
        pq.pop();

        Person& p = everyone[pc.name];
        
        if (p.best_weight != -1)
        {
            continue;
        }

        p.best_weight = pc.weight;
        p.best_parent = pc.parent;

        if (pc.name == ending)
        {
            return(true);
        }

        addToTent(pq, p, pc.name);
    }
    // Complete this function -- run the Dijkstra algorithm.
    // Here are the things you'll need:
    // - Some way to track tentative "candidate" nodes (priority queue?)
    // - Process each node just like you did in the MST calculation, except
    //   consider the total path length (cost to this node + cost of edge)
    // - Update the best cost/best parent in the graph when found.
    // - Stop the algorithm when the end node is reached.

    return (false);
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
    // We save this line (names) so we can lookup the string names when
    // needed.
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
            if (adj_status > 0) {
                p.friends.push_back(names[i]);
                p.weights.push_back(adj_status);
            }

            // Initialize the other fields
            p.best_weight = -1;
            p.best_parent = "";
        }
        // Add this (new) person to the map.
        // In this map, the key is the string name of the person, and
        // the value is their Person structure (adjacency list).
        everyone.insert(make_pair(row[0], p));
    }

    // The main loop of the program
    for (;;) {
        // Use this code to explore the graph and weights if needed.  It is
        // left commented out here.
        
        //cout << endl << "Enter the name and I'll tell you their friends: ";
        //getline(cin, inputLine);
        //if (IS_QUIT(inputLine))
        //    break;

        //// Look up the adjacency list of this person in the map
        //if (everyone.count(inputLine) == 0) {
        //    cout << "That person is not in the map." << endl;
        //    continue;
        //}
        //Person this_person = everyone[inputLine];

        //// Output all their friends
        //cout << inputLine << " is friends with: " << endl;
        //for (size_t i = 0; i < this_person.friends.size(); i++) {
        //    cout << "\t" << this_person.friends[i] << " (weight "
        //         << this_person.weights[i] << ")" << endl;
        //}
        //
        
        string to, from;
        stack<string> path;
        cout << endl << "Enter the starting name (X to quit): ";
        getline(cin, from);
        if (IS_QUIT(from))
            break;

        cout << endl << "Enter the ending name (X to quit): ";
        getline(cin, to);
        if (IS_QUIT(to))
            break;

        if (everyone.count(from) == 0 || everyone.count(to) == 0) {
            cout << "One or more people is not in the map." << endl;
            continue;
        }

        // Run the calculation
        if (dijkstra(everyone, from, to)) {
            cout << "The best path between these two people is: " << endl;
            // Construct the path from the parents stored
            // Output the path in reverse
            Person p = everyone[to];
            int cost = p.best_weight;
            string currentPerson;
            stack<string> path;
            path.push(to);
            
            while (from != currentPerson) {
                currentPerson = p.best_parent;
                p = everyone[currentPerson];
                path.push(currentPerson); 

            }
            while (!path.empty())
            {
                cout << "	" << path.top() << endl;
                path.pop();
            }
            cout << "The cost of this path is: " << cost << endl;
        }
        else {
            cout << "There is NOT a path between these two people." << endl;
        }

        // Clean up all the state
        for (auto i = everyone.begin(); i != everyone.end(); i++) {
            Person& p = i->second;
            p.best_weight = -1;
            p.best_parent = "";
        }
    }
    cout << "Exiting..." << endl;
}
