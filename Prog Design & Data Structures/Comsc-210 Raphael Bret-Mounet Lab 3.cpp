#include <iostream>
#include <cstdlib>
#include <queue>
#include <fstream>
#include <string>
#include <time.h> 
#include <iomanip>
using namespace std;

// Input parameters
#define SIMULATION_TIME     0
#define ARRIVAL_RATE        1
#define MIN_SERVICE_TIME    2
#define MAX_SERVICE_TIME    3
#define MAX_LINE_SIZE       4
#define TARGET_TIME         5
#define PARAMS_MAX          6

// Name of the input file
#define FILENAME            "sim.txt"

// Counters -- these are indexes into variable 'counters' below
#define CUSTOMERS_SERVICED  0
#define CUSTOMERS_LEAVING   1
#define AVERAGE_WAIT        2
#define AVERAGE_LINE        3
#define WITHIN_TARGET       4
#define COUNTERS_MAX        5

// Holds the current simulation parameters
double parameters[PARAMS_MAX];
double counters[COUNTERS_MAX];

// Return the service interval, between 'min'
// and 'max'.
int randomInt(int min, int max) {
    return (rand() % (max - min) + min);
}
// Returns TRUE if a customer arrived during this minute.
// We need to divide by RAND_MAX because rand() returns a
// number between 0 and RAND_MAX (which is defined by
// a system header).
bool randomChance(double prob) {
    double rv = rand() / (double(RAND_MAX) + 1);
    return (rv < prob);
}

// Read the next simulation from the file.  Return
// TRUE if one could be read, FALSE otherwise (eof).
bool readNextSim(fstream& f, double parameters[]) {
    for (int i = 0; i < PARAMS_MAX; i++) {
        string tmp;
        getline(f, tmp);
        if (f.eof())
            return false;
        // Read in the next parameter
        parameters[i] = atof(tmp.c_str());
    }
    //cout << "Test Case: " << endl;
    //for (int i = 0; i < PARAMS_MAX; i++) {
    //   cout << "\t Param #" << i << ": " << parameters[i] << endl;
    //}
    return true;
}

// Used to store customers time stamps of entering and leaving the line.
struct Customer 
{
    int timeEnteredLine;
    int timeLeftLine;
};

int main()
{
    fstream f(FILENAME);

    // Seed the random number generator here
    srand(time(0));

    // Checks if file was read properly.
    if (!f.good()) {
        cout << "Invalid file." << endl;
        return -1;
    }

    // This loop reads each simulation (a set of parameters) from the input
    // file.
    while (readNextSim(f, parameters)) {
        // Run the next simulation
        queue<int> line;

        // Sets all the variables in counters to 0
        for (int i = 0; i < COUNTERS_MAX; i++)
            counters[i] = 0;

        // The current time in this individual simulation.
        int simTime = 0;

        // Used to tell whether a customer is at a the cashier or not.
        bool atCashier = false;

        // Used to keep track of how long a customer will be at the register.
        int serviceTime = 0;

        // Used to keep track of what costumers are in the line.
        int customers = 0;

        // Stores the timestamps of when the customer enters and leaves the line.
        vector<Customer> customerInfo;
        
        // While loop used for simulation.
        while (simTime++ < parameters[SIMULATION_TIME]) {
            
            // Checks to see if serviceTime has reached 0
            if (serviceTime == 0) {
                // If true then generate a new service time between defined min and max times.
                serviceTime = randomInt(parameters[MIN_SERVICE_TIME], parameters[MAX_SERVICE_TIME]);
            }

            // Used to simulate randomness of a customer.
            bool customerArrived = randomChance(parameters[ARRIVAL_RATE]);

            // Keeps track of the line size.
            counters[AVERAGE_LINE] += line.size();

            // Checks to see if a customer has arrived.
            if (customerArrived)
            {
                // If true then create a new vector element with a customer struct and increment counter.
                customerInfo.push_back(Customer());
                customers++;
            }
 
            // Checks to see if a customer has a arrived when the line is empty and no one is at the register
            if (!atCashier && line.empty() && customerArrived)
            {
                // If true then put customer at register.
                atCashier = true;
            }
            // Checks is someone is at register.
            else if (atCashier)
            {
                // If true then checks too see how much time is left at the register.
                if (serviceTime > 0)
                {
                    // Decrement timer.
                    serviceTime--;

                    // Checks to see if a customer arrived while register is busy.
                    if (customerArrived)
                    {
                        // If true than checks to see if their is room in line.
                        if (line.size() < parameters[MAX_LINE_SIZE])
                        {
                            // Stores timestamp of customer when they enter the line and puts them in queue.
                            customerInfo[customers-1].timeEnteredLine = simTime;
                            line.push(customers);
                        }
                        // If line is full then customer leaves.
                        else
                        {
                            counters[CUSTOMERS_LEAVING]++;
                        }
                    }
                    // Checks to see if service time is at 0
                    if (serviceTime == 0) {
                        // If true then check is line has people.
                        if (line.size() > 0)
                        {
                            // If true then get customers id from the front of the line.
                            int customerLeaving = line.front();
                            // Gets time stamp of customer as they leave the line.
                            customerInfo[customerLeaving-1].timeLeftLine = simTime;
                            // Removes customer from the line.
                            line.pop();

                            // Puts customer at register.
                            atCashier = true;
                        }
                        // If no one is in line than register is empty.
                        else
                        {
                            atCashier = false;
                        }
                        // Add customer to number of customers serviced.
                        counters[CUSTOMERS_SERVICED]++;
                    }
                }
                
            }
            // Checks to see if there are still customers inline when simulation ends.
            if (simTime >= parameters[SIMULATION_TIME] && !line.empty()) {
                // If true then check if the line has people in it. 
                while (!line.empty())
                {
                    // Clears the line and sets time stamps since customers never left.
                    int customerLeaving = line.front();
                    customerInfo[customerLeaving - 1].timeEnteredLine = 0;
                    customerInfo[customerLeaving - 1].timeLeftLine = 0;
                    line.pop();
                }
            }
        }

        // Checks to see if any customers showed up to the register.
        if (!customerInfo.empty()) 
        {
            // If true then run a loop for calculating average time and the amount of customers within target time.
            for (int i = 0; i < (customerInfo.size() - 1); i++)
            {
                int waitTime = customerInfo[i].timeLeftLine - customerInfo[i].timeEnteredLine;
                if (waitTime <= parameters[TARGET_TIME])
                {
                    counters[WITHIN_TARGET]++;
                }
                counters[AVERAGE_WAIT] += waitTime;
            }
        }
        
        // Math for calculating the averages and percent.
        counters[AVERAGE_LINE] = counters[AVERAGE_LINE] / simTime;
        counters[AVERAGE_WAIT] = counters[AVERAGE_WAIT] / customerInfo.size();
        counters[WITHIN_TARGET] = (counters[WITHIN_TARGET]/ counters[CUSTOMERS_SERVICED])*100;
        
        // Console output for results.
        cout << "Simulation Results" << endl;
        cout << "------------------" << endl;
        cout << "Overall simulation time:          " << parameters[SIMULATION_TIME] << endl;
        cout << "Arrival rate:                      " << parameters[ARRIVAL_RATE] << endl;
        cout << "Minimum service time:                " << parameters[MIN_SERVICE_TIME] << endl;
        cout << "Maximum service time:               " << parameters[MAX_SERVICE_TIME] << endl;
        cout << "Target waiting time:                " << parameters[TARGET_TIME] << endl;
        cout << endl;
        
        cout << "Customers serviced:                " << counters[CUSTOMERS_SERVICED] << endl;
        cout << "Customers leaving:                  " << counters[CUSTOMERS_LEAVING] << endl;
        cout << "Average time spent in line:      " << fixed << setprecision(2) << counters[AVERAGE_WAIT] << endl;
        cout << "Average line length:              " << fixed  << setprecision(2) << counters[AVERAGE_LINE] << endl;
        cout << "Pct. served within target:       " << fixed << setprecision(2) << counters[WITHIN_TARGET] << endl;
        cout << endl;

    }

    return 0;
}
