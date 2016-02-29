/*******************************
 * subseqFlip.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a program that takes a binary string as input and then
            flips all the bits in a substring to obtain a new binary string
            with the highest number of 1s.
 ******************************/

#include <iostream>
#include <string>

using namespace std;


string subseqFlip(string input)
{
    int i, size = input.size();

    /* Here we define an array of values to assign to the prefixes. A 0
       adds one to the value and a 1 decreases the value by one. Note the
       0th position in this array is the value of the empty prefix so
       the other positions are shifted right one.
    */
    int valueof[size + 1];
    valueof[0] = 0; int value = 0;
    for(i=0; i<size; i++)
    {
        if(input[i] == '0') value++;
        else value--;

        valueof[i + 1] = value;
    }
  
    /* Now we perform a simple search on this array to determine the max
       difference we can obtain between two elements where the first
       element is on the right. We store the positions of these elements
       in left and right. Note the value of this difference is precisely
       the value of the substring between left and right.
    */
    int min_pos = 0, max_pos = 0, left = 0, right = 0, maxdiff = 0;
    for(i=0; i<size + 1; i++)
    {
        if( valueof[i] - valueof[ min_pos ] >  maxdiff )
        {
             maxdiff = valueof[i] - valueof[ min_pos ];
             max_pos = i; 

             left = min_pos;
             right = max_pos;          
        }
        if(valueof[i] < valueof[ min_pos ])
        {
           min_pos = i;
        }
    }
    /* Now we go through the subsequence having the largest value that
       we have found and switch all its bits.
    */  
    string output;
    output = input;
    for(i=left; i<right; i++)
    {
        if(output[i] == '0') output[i] = '1';
        else output[i] = '0';
    }
    return output;
}

int main()
{
    string input;

    cout << "\nThis is a program that takes a binary string as input and then\n"
            "flips all the bits in a substring to obtain a new binary string\n"
            "with the highest number of 1s.\n" << endl;

    cout << "Enter a binary string: ";
    cin >> input;
    cout << "The new string is: " << subseqFlip(input) << endl;
    return 0;
}
