/*******************************
 * polish.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a simple program that implements a reverse polish calculator.
 ******************************/

#include <stack>
#include <string>
#include <limits>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

void rpn_calculate(vector < string > tokens)
{
    stack<int> thestack;
    int a, b, c;

    for(int i=0; i< tokens.size(); i++)
    { 
      /* When we encounter an operator, we perform it to the two top elements of the
         stack, pop them, and add the result to the stack.
      */   
      if(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")
      {
          if(thestack.size() < 2) // There must be at least 2 elements in the stack.
          { 
              cout << "ERROR!" << endl;
              return;
          }

          a = thestack.top();
          thestack.pop();
          b = thestack.top();
          thestack.pop();

          if(tokens[i] == "+") c = a + b;
          else if(tokens[i] == "-") c = a - b;
          else if(tokens[i] == "*") c = a * b;
          else if(tokens[i] == "/") c = a / b;

          thestack.push(c);
      }
      else
          thestack.push( atoi( tokens[i].c_str() ) ); // Add the number to the stack.      
    }


    if(thestack.size() != 1) // If the stack still has more than one element, error.
    {
        cout << "ERROR!" << endl;
        return;
    }

    cout << thestack.top() << endl;
}

int main() 
{
    int size;

    cout << "\nThis is a simple program that implements a reverse polish calculator.\n" << endl;

    cout << "Enter the number of terms in the input: ";
    cin >> size;

    cout << "Enter a rp expression: ";
    cin.ignore (numeric_limits<streamsize>::max(), '\n'); // Flushes stdin
 
    vector<string> tokens;
    string temp;
    for(int i=0; i < size; i++)
    {
        cin >> temp;
        tokens.push_back(temp);
    }
    
    rpn_calculate(tokens);
    
    return 0;
}
