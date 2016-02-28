/*******************************
 * robot.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a program that if given directions for a robot
 *          that it will repeatedly follow, will determine whether 
 *          the robot will remain in a bounded area for all time.
 ******************************/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int i,N;

    cout << "Input number of moves: ";
    cin >> N;

    cout << "Now input the sequence of moves. Moves allowed are: \n"
            "1) step (moves the robot forward 1 unit) \n"
            "2) turn (turns the robot 90 degrees counterclockwise." << endl;

    int dir = 0, x = 0, y = 0; // dir is the direction and (x,y) is the position.

    string word;
    for(i=0; i<N; i++) // Here we determine where the robot will be after 1 sequence of moves.
    {
        cin >> word;
        if(word == "turn")
        {
            dir = (dir+1) % 4;
        }
        else if(word == "step")
        {
            if(dir == 0) x++;
            else if(dir == 1) y++;
            else if(dir == 2) x--;
            else if(dir == 3) y--;
        }
    }
    /* If you do the math, you will see that if the robot returned to its starting position and/or it
       is facing a different direction, it will remain bounded. Otherwise it will be unbounded.
    */

    if(x == 0 && y == 0) cout << "The robot will remain in a bounded area." << endl;
    else
    {
        if(dir == 0) cout << "The robot will NOT remain in a bounded area." << endl;
        else cout << "The robot will remain in a bounded area." << endl;
    }
 
    return 0;
}

