/*******************************
 * pairs.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a program that takes as input a string consisting of lower-case and
 *          and capital letters and determines the last position that a "pair" occurs.
 *          A pair is defined to be a capital letter followed immediately by its lower-
 *          case form. Also once two letters pair up, they are removed from further
 *          consideration, similar to how pieces cancel out in Dr. Mario. For example,
 *          ABba would have 2 valid pairs. 
 ******************************/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int lastpair(string input)
{
    int last = -1;
    stack <char> capitals; // This stack stores the previous capital letters.

    /* Note '[' is a character inbetween the capital and lower-case letters.
       In ascii the integer forms of the capital letters come first.
     */
    if(input[0] > '[') return last; // The first letter was lower-case.

    for(int i=0; i<input.length(); i++)
    {
        if(input[i] < '[') // If we come across a capital, add it to the stack.
        {
            capitals.push(input[i]);
        }
        else // If we come across a lower-case letter, check the top of the stack.
        {
            if(capitals.empty()) break; // The stack was empty so we break.

            if(capitals.top() != input[i]-32) break; // Not a pair.
            else last = i; // Our letter does form a pair so update the last position.

            capitals.pop();
        }
    }
    return last;
}

int main()
{
    string input;
    int pos;

    cout << "\nThis is a program that takes as input a string consisting of lower-case and\n"
            "and capital letters and determines the last position that a \"pair\" occurs.\n"
            "A pair is defined to be a capital letter followed immediately by its lower-\n"
            "case form. Also once two letters pair up, they are removed from further\n"
            "consideration, similar to how pieces cancel out in Dr. Mario. For example,\n"
            "ABba would have 2 valid pairs.\n" << endl;

    cout << "Enter a string: ";
    cin >> input;
    pos = lastpair(input);

    if(pos == -1) cout << "No pairs occurred!" << endl;
    else cout << "The last pair occurred in position " << pos << "." << endl;

    return 0;
}
