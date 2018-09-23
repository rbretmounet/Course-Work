#include <iostream>
#include <iomanip>
using namespace std;

void inputAnswers(char[]); // Gets student's answers on the exam.
void checkAnswers(char[],char[],int[],int &, int &); // Checks the answers to see which ones are incorrect and correct.
void results(int[],int &, int &); // Checks if student passed the exam and says how many the student got incorrect and correct and the questions # incorrect.
void arrayAssign(int[]); // Assigns the wrong array to 0 so result function can display only the questions wrong.
const int SIZE = 20; // The amount of questions on the exam.

int main() {

    int correctAnswers, incorrectAnswers; // Stores the number of correct and incorrect answers.
    char userAnswers[SIZE]; // Array used to keep student's answers.
    char answers[SIZE] = {'A','D','B','B','C','B','A','B','C','D',
                          'A','C','D','B','D','C','C','A','D','B'}; // Array used to compare student's answers to correct answers.
    int wrongAnswers[SIZE]; // Used to store the incorrect question's number.

    arrayAssign(wrongAnswers);
    inputAnswers(userAnswers);
    checkAnswers(userAnswers, answers, wrongAnswers, correctAnswers, incorrectAnswers);
    results(wrongAnswers, correctAnswers, incorrectAnswers);


    return 0;
}
void inputAnswers(char userInput[]) //  Gets student's answers on the exam.
{
    for(int i = 0; i < SIZE; i++) // Asks user to input student's answers and stores answers into userAnswers.
    {
        char input;
        cout << "Please enter answer to question #" << i+1 << endl;
        cin >> userInput[i];
        input = userInput[i];
        input = toupper(input); // Assigns lowercase letters to uppercase letters.
        if(input != 'A' && input != 'B' && input != 'C' && input != 'D') // Checks to see if input is A,B,C,or D.
        {
            cout << "Please input only A,B,C, or D" << endl; // Prompts the user to input A,B,C, or D.
            i--; // Moves array position back to the question that was inputed incorrectly.
        }
    }
}

void checkAnswers(char userInput[], char answers[], int wrongA[], int &correct, int &wrong) // Checks the answers to see which ones are incorrect and correct.
{
    correct = 0;
    wrong = 0;
    for(int i = 0; i < SIZE; i++) // Checks student's answers with answer key.
    {
        if(answers[i] == userInput[i]) // Changes the amount of correct when student's answer is correct.
        {
            correct = correct + 1;
        }
        else if(answers[i] != userInput[i]) // Changes the amount of incorrect when student's answer is incorrect.
        {
            wrong = wrong + 1;
            wrongA[i] = i+1; // Assigns the question number to wrongAnswers.
        }
    }
}

void results(int wrongA[], int &correct, int &wrong) // Checks if student passed the exam and says how many the student got incorrect and correct and the questions # incorrect.
{
    if(correct >= 15) // When student gets 15 questions right then the student passes.
    {
        cout << "The student passed the exam." << endl;
    }
    else
    {
        cout << "The student failed the exam." << endl;
    }
    cout << endl;
    cout << "Correct Answers: " << correct << endl;
    cout << "Incorrect Answers: " << wrong << endl;
    cout << endl;
    cout << "Questions that were answered incorrectly: " << endl;
    for(int i = 0; i < SIZE; i++) // Displays only the array values that are = to the question number
    {
        if(wrongA[i] != 0)
        {
            cout << wrongA[i] << endl;
        }
    }
}
void arrayAssign(int array[]) // Assigns the wrong array to 0 so result function can display only the questions wrong.
{
    for(int i = 0; i < SIZE; i++)
    {
        array[i] = 0;
    }
}
