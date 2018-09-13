#include <iostream>
#include <iomanip>
using namespace std;

// Function prototypes
void getJudgeData(double[]);
void calcScore(double[]);
double findLowest(double[]);
double findHighest(double[]);
void swap (double[], double[]);
int SIZE = 4;

int main()
{
    double judgeScores[SIZE]; //Array used to store judges scores.

	getJudgeData(judgeScores); //Prompts user with score input and stores in array.
    findLowest(judgeScores); //Searches for lowest score in array and stores value in array position 0.
    findHighest(judgeScores); //Searches for highest score in array and stores value in array position 1.
    calcScore(judgeScores); //Calculate average of scores.

    cout << "Press enter to continue ..." << endl;
    cin.get();
    return 0;
}

void getJudgeData(double score[]) // Gets judges scores with an array assigning judgeScores[0]-judgeScores[4] with values inputed.
{
    for (int i = 0; i <= SIZE; i++)
    {
        cout << "Enter a judge's score: " << endl;
        cin >> score[i];

        if (score[i] < 0.0 || score[i] > 10.0) // Checks if scores are less than 0.0 or more that 10.0 if so then it prompts user to input number again.
        {
            cout << "The score must be between 0.0 and 10.0: " << endl;
            i--;
        }
    }
}

void calcScore(double score[]) // Calculates the average of the scores, minus the lowest and the highest scores, inputed in function getJudgeData.
{
    int judgeAmount = SIZE-1;
    double average = 0;
    for (int i = 2; i <= SIZE; i++)
    {
        average = average + score[i]; // Adds all scores together minus the lowest and highest scores
    }
    average = average / judgeAmount; // Divides total by array size - lowest and highest score.

    cout << "after dropping the highest and the lowest score, the average score was " << average << endl;
}

double findLowest(double score[]) // Uses a bubblesort to compare the values and finds the lowest value.
{
    for (int i = 0; i <= SIZE; i++)
    {
        if (score[i] < score[0]) // Compares value stored in array score[] to the first value in the array if lower switches that value to the first value.
        {
           swap(score[i],score[0]); // Sets the first value to the lowest score.
        }

    }
}

double findHighest(double score[]) // Uses a bubblesort to compare the values and finds the highest value.
{
    for (int i = 0; i <= SIZE; i++)
    {
        if (score[i] > score[1]) // Compares value stored in array score[] to the second value in the array if higher switches that value to the second value.
            {
                swap(score[i],score[1] ); // Sets the second value to the highest score.

            }

    }

}
void swap(double array1[], double array2[]) // Swaps the array values.
{
    int x;
    double temp;
    temp = array2[x]; // Sets the second value to the highest score.
    array2[x] = array1[x];
    array1[x] = temp;
}
