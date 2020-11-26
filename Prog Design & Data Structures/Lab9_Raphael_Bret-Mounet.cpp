#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

//
// This is a starter file to help frame your ideas around
// Lab #9.  The reading of each line in the file is completed
// for you.
//

const string FILENAME = "ft_chicago.csv";  // Input file (CSV)
const int NFIELDS = 3;                     // Number of fields in
                                           // each line of the input file

// This holds a single food truck entry.  Each line in the file should
// correspond to one of these.
typedef struct _foodtruck {
    string business_name;
    string zip;
    string license_type;
    _foodtruck* next;
} foodtruck;




// Starting size, adjust as needed -- should be prime.
// This strikes a good balance without having too many empty buckets.
const int HASH_SIZE = 53;

// Hash table for all of the food trucks -- static so it's zeroed
static foodtruck* truckHash[HASH_SIZE];

// Reads a single truck, filling in the
// fields (name, etc.) passed by the caller.
void readSingleTruck(const string& str,
    foodtruck* newFT) {
    istringstream istr(str);
    string fields[NFIELDS];
    string tmp;
    int i = 0;

    while (getline(istr, tmp, ',') && i < NFIELDS) {
        fields[i++] = tmp;
    }

    // Fill in the newly allocated entry.
    // A pointer to it was passed to us.
    newFT->business_name = fields[0];
    newFT->zip = fields[1];
    newFT->license_type = fields[2];
}

// Generate a hash key, given a string (this would come from the
// string the user typed to find).  your hash function goes here.
unsigned int genHashKey(string key) {
    unsigned int hashval = 0; 

    for (int i = 0; i < key.size(); i++)
        hashval = (int)key[i] + 31 * hashval;

    return (hashval % HASH_SIZE);
}

// Insert a new truck into the hash table
void truckInsert(foodtruck* newFT) {
    int key = genHashKey(newFT->business_name); // generates hash key for hash table.

    newFT->next = 0; // Assigns next pointer to beginning of struct.

    struct _foodtruck* entry; // creates a new struct for hash bucket.
    entry = truckHash[key]; // assignes entry to specified hash bucket.

    // Checks to see if entry is empty.
    if (!entry) {
        // If true then assign hask bucket to new entry and return.
        truckHash[key] = newFT;
        return;
    }
    // else finds the last entry.
    while (entry->next) {
        entry = entry->next;
    }

    // Makes entry point to the new food truck.
    entry->next = newFT;
    return;
}

// This function accepts a string name and a reference
// to an empty foodtruck.
//
// Upon return,
// - 'foundFT' will be filled-in with what was found.
// - The function will return 'true' if something was found, 'false' otherwise.
//
bool truckFind(const string& name, foodtruck& foundFT, int& ncmp) {
    int key = genHashKey(name); // generates hash key for hash table.

    struct _foodtruck* entry; // creates a new struct for hash bucket.
    entry = truckHash[key]; // assignes entry to specified hash bucket.

    // Looks through the all the entries
    while (entry) {
        // Checks to see if entry key matches the specified business name.
        if (entry->business_name == name) {
            // If true then store all the infor into a temp struct and return true.
            foundFT.business_name = entry->business_name;
            foundFT.license_type = entry->license_type;
            foundFT.zip = entry->zip;
            return (true);
        }
        // Points to the next entry.
        entry = entry->next;
        ncmp++;
    }

    return (false);
}

int main() {
    ifstream inFile(FILENAME);
    string inputLine, inputStr;
    int linesRead = 0;

    // Discard the first header line
    getline(inFile, inputLine);

    // Read in each food truck entry
    while (getline(inFile, inputLine)) {

        // Dynamically allocate a new struct
        foodtruck* ftptr = new foodtruck;

        // Read the next line from the file,
        // filling in the new truck
        // just allocated.
        readSingleTruck(inputLine, ftptr);

        // Hash it and insert into the table where needed.
        truckInsert(ftptr);

        // Keep a counter of read lines.
        linesRead++;

        // (for debugging)
        // Output the number of lines read every so often.
        // if (linesRead % 25 == 0)
        //    cout << "Inserted " << linesRead << " entries"
        //         << endl;
    }

    // Handle errors and/or summarize the read
    if (linesRead == 0) {
        cerr << "Read failed." << endl;
        return (-1);
    }
    else {
        cout << "Read " << linesRead << " food trucks." << endl;
        cout << fixed << setprecision(2) << endl;
    }

    // (example) Forever loop until the user requests an exit
    for (;;) {
        string businessName; // Used to store user input
        
        // User Prompt:
        cout << "Enter a business name (<return> to quit): ";
        getline(cin, businessName);
        
        // Checks to see if user hit return key.
        if (businessName == "") {
            // If true exit the program.
            cout << "Exiting...";
            break;
        }

        foodtruck foundFT; // Used to retrieve business info.
        int numberOfComparisons = 0; // Used to keep track of total comparisons.

        // Checks to see if food truck is found.
        if (truckFind(businessName, foundFT, numberOfComparisons))
        {
            // If true then output results.
            cout << "Comparisons: " << numberOfComparisons << endl;
            cout << "Business name: " << foundFT.business_name << endl;
            cout << "ZIP: " << foundFT.zip << endl;
            cout << "License type: " << foundFT.license_type << endl;
        }
        // Otherwise food truck is not in data base.
        else
        {
            cout << "Not found in the database." << endl;
            cout << "Comparisons: " << numberOfComparisons << endl;
        }
        cout << endl;
        

    }
    return (0);
}
