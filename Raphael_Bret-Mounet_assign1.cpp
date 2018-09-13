#include <iostream>
#include <string>
using namespace std;

void userInput(string&, string&, string&, double&, double&, double&);
void findPlaces(string&, string&, string&, double&, double&, double&);

int main() {
    double runnerTime1, runnerTime2, runnerTime3;
    string runnerName1, runnerName2, runnerName3;

    cout << "Enter the names of the three runners and their finishing times" << endl;
    cout << "I will tell who came first, second, and third." << endl;

    userInput(runnerName1, runnerName2, runnerName3, runnerTime1, runnerTime2, runnerTime3);

    cout << "Name of Runner 1: " << runnerName1 << endl;
    cout << "Runner 1's finishing time: " << runnerTime1 << endl;
    cout << endl;

    cout << "Name of Runner 2: " << runnerName2 << endl;
    cout << "Runner 2's finishing time: " << runnerTime2 << endl;
    cout << endl;

    cout << "Name of Runner 3: " << runnerName3 << endl;
    cout << "Runner 3's finishing time: " << runnerTime3 << endl;
    cout << endl;

    findPlaces(runnerName1, runnerName2, runnerName3, runnerTime1, runnerTime2, runnerTime3);

    return 0;
}

//Gets runner names and times.
void userInput(string&name1, string&name2, string&name3, double&time1, double&time2, double&time3)
{
    cout << "Please Input Name of Runner 1: " << endl;
    cin >> name1;
    cout << "Please Input Finishing Time of Runner 1: " << endl;
    cin >> time1;
    cout << "Please Input Name of Runner 2: " << endl;
    cin >> name2;
    cout << "Please Input Finishing Time of Runner 2: " << endl;
    cin >> time2;
    cout << "Please Input Name of Runner 3: " << endl;
    cin >> name3;
    cout << "Please Input Finishing Time of Runner 3: " << endl;
    cin >> time3;
}

//Finds out who finished first, third, and last place.
void findPlaces(string&name1, string&name2, string&name3, double&time1, double&time2, double&time3)
{
    //Checks if runner number 1 came in first.
    if(time1 < time2 && time1 < time3)
    {
        //Checks if runner number 2 cam in second.
        if(time2 < time3)
        {
            cout << name1 << " came in first with a score of " << time1 << endl;
            cout << name2 << " came in second with a score of " << time2 << endl;
            cout << name3 << " came in third with a score of " << time3 << endl;
        }
        else
        {
            cout << name1 << " came in first with a score of " << time1 << endl;
            cout << name3 << " came in second with a score of " << time3 << endl;
            cout << name2 << " came in third with a score of " << time2 << endl;
        }
    }
    //Checks if runner number 2 came in first.
    if(time2 < time1 && time2 < time3)
    {
        //Checks if runner number 1 came in second.
        if(time1 < time3)
        {
            cout << name2 << " came in first with a score of " << time2 << endl;
            cout << name1 << " came in second with a score of " << time1 << endl;
            cout << name3 << " came in third with a score of " << time3 << endl;
        }
        else
        {
            cout << name2 << " came in first with a score of " << time2 << endl;
            cout << name3 << " came in second with a score of " << time3 << endl;
            cout << name1 << " came in third with a score of " << time1 << endl;
        }
    }
    //Checks if runner number 3 came in first.
    if(time3 < time1 && time3 < time2)
    {
        //Checks if runner number 2 came in first.
        if(time2 < time1)
        {
            cout << name3 << " came in first with a score of " << time3 << endl;
            cout << name2 << " came in second with a score of " << time2 << endl;
            cout << name1 << " came in third with a score of " << time1 << endl;
        }
        else
        {
            cout << name3 << " came in first with a score of " << time3 << endl;
            cout << name1 << " came in second with a score of " << time1 << endl;
            cout << name2 << " came in third with a score of " << time2 << endl;
        }
    }
}
