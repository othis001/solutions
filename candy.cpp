/*******************************
 * candy.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a program that takes as input an array of scores
 *          where the ith score corresponds to the ith student sitting
 *          in a row. The teacher wants to give out candy to the students
 *          subject to 2 constraints.
 *          
 *          1) Every student gets at least one piece of candy.
 *          2) If a student scored higher than one of their neighbors,
 *             they must receive more candy than that neighbor.
 *
 *          This program will calculate the minimum amount of candy needed.
 ******************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void calculate(int *, int, int *);

int countcandy(vector<int> theinput)
{
    int size = theinput.size(), i, amount;

    /* Here we add students on the left and right sides with unbounded
       scores. This is done to simplify the code.
    */ 
    int *input = new int[size+2];
    input[0] = 1000000;
    for(i=0; i<size; i++)
    {
        input[i+1] = theinput[i];
    }
    input[size+1] = 1000000;

    /* Initalizes an array to keep track of how much candy each student has.
    */
    int *candy = new int[size+2];
    for(i=0; i<size+2; i++)
    {
        candy[i] = 1;
    }

    /* Now we call a recursive function to calculate how much candy each
       student needs.
    */
    for(i=1; i<=size; i++)
    {
        calculate(input, i, candy);
    }

    /* Finally we total up the candy needed.
    */
    amount = 0;
    for(i=1; i<=size; i++)
    {
        amount = amount + candy[i];
    }
    return amount;
}

/* This function calculates how much candy student i needs. */
void calculate(int *input, int i, int *candy)
{
    /* If our student's score is higher than their left neighbor.
    */
    if(input[i] > input[i-1]) 
    {                         
        if(candy[i-1] >= candy[i]) candy[i] = candy[i-1]+1;
    }

    /* If our student's score is higher than their right neighbor.
    */
    if(input[i] > input[i+1])
    {
        if(candy[i+1] >= candy[i])
        {
            candy[i] = candy[i+1]+1;

            /* If the left neighbor has a higher score than our student,
               we need to recalculate their score.
            */
            if(input[i-1] > input[i] && i>1) calculate(input, i-1, candy);
        }
    }
}

int main()
{
    int N, temp;
    vector<int> input;


    cout << "\nThis is a program that takes as input an array of scores\n"
            "where the ith score corresponds to the ith student sitting\n"
            "in a row. The teacher wants to give out candy to the students\n"
            "subject to 2 constraints.\n\n"
            "1) Every student gets at least one piece of candy.\n"
            "2) If a student scored higher than one of their neighbors,\n"
            "   they must receive more candy than that neighbor.\n\n"
            "This program will calculate the minimum amount of candy needed.\n" << endl;

    cout << "Enter the number of students: ";
    cin >> N;
    cout << "Enter their scores: ";
    for(int i=0; i< N; i++)
    {
        cin >> temp;
        input.push_back(temp);
    }

    cout << countcandy(input) << " candies are needed." << endl;
    return 0;
}
